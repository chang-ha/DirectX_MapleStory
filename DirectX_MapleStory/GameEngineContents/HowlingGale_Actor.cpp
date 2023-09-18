#include "PreCompile.h"
#include "HowlingGale_Actor.h"
#include "Player.h"
#include "ContentLevel.h"
#include "ContentMap.h"
#include "SkillManager.h"

#define HIT_TIME 0.5f

HowlingGale_Actor* HowlingGale_Actor::MainHowlingGale = nullptr;

HowlingGale_Actor::HowlingGale_Actor()
{
	
}

HowlingGale_Actor::~HowlingGale_Actor()
{

}

void HowlingGale_Actor::LevelStart(GameEngineLevel* _PrevLevel)
{
}

void HowlingGale_Actor::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != MainHowlingGale)
	{
		Death();
		MainHowlingGale = nullptr;
	}
}

void HowlingGale_Actor::Start()
{
	MainHowlingGale = this;

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PlayBelow);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->CreateAnimation("Ready", "Ready_Stack1");
	MainSpriteRenderer->CreateAnimation("Attack", "Attack_Stack1");
	MainSpriteRenderer->CreateAnimation("Death", "Death_Stack1");
	MainSpriteRenderer->ChangeAnimation("Ready");
	MainSpriteRenderer->SetPivotValue(float4(0.5f, 0.965f));

	// Renderer Event 1stack
	MainSpriteRenderer->SetEndEvent("Ready", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->ChangeAnimation("Attack");
		}
	);

	MainSpriteRenderer->SetEndEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			IsUpdate = false;
			Death();
			MainHowlingGale = nullptr;
		}
	);

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Ready_Stack1");
	Scale = Sprite->GetSpriteData(0).GetScale();

	SkillCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
	SkillCollision->Transform.SetLocalScale(Scale);
}

void HowlingGale_Actor::Update(float _Delta)
{
	if (false == IsUpdate)
	{
		return;
	}

	LiveTime -= _Delta;
	if (0.0f >= LiveTime && false == MainSpriteRenderer->IsCurAnimation("Death"))
	{
		MainSpriteRenderer->ChangeAnimation("Death");
	}

	if (true == IsGround && 0.0f < GravityForce)
	{
		GravityReset();
	}

	ContentActor::Update(_Delta);
	BlockOutMap();
	MoveUpdate(_Delta);
	if (true == SkillCollision->Collision(CollisionOrder::Monster))
	{
		Speed = 100.0f;
	}
	else
	{
		Speed = 200.0f;
	}

	SkillCollision->Collision(CollisionOrder::Monster, [&](std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup)
		{
			for (size_t i = 0; i < _CollisionGroup.size(); i++)
			{
				std::shared_ptr<GameEngineCollision> _Other = _CollisionGroup[i];
				if (false == CollisionTime.contains(_Other))
				{
					CollisionTime[_Other] = 0.0f;
				}

				CollisionTime[_Other] -= _Delta;
				if (0.0f >= CollisionTime[_Other])
				{
					float4 OtherPos = _Other->GetParentObject()->Transform.GetWorldPosition();
					SkillManager::PlayerSkillManager->HitPrint("HowlingGale_Hit", 3, _Other->GetParentObject());
					CollisionTime[_Other] = HIT_TIME;
				}
			}
		}
	);
}

void HowlingGale_Actor::BlockOutMap()
{
	float4 CurPos = Transform.GetWorldPosition();
	if (0 > CurPos.X - Scale.hX())
	{
		Transform.SetLocalPosition(float4{ Scale.hX(), CurPos.Y });
		Dir = ActorDir::Right;
	}
	else if (CurMapScale.X <= CurPos.X + Scale.hX())
	{
		Transform.SetLocalPosition(float4{ CurMapScale.X - Scale.hX(), CurPos.Y });
		Dir = ActorDir::Left;
	}

	//// Need Test More
	//CurPos.Y *= -1.0f;
	//if (0 > CurPos.Y - Scale.hY())
	//{
	//	Transform.SetLocalPosition(float4{ CurPos.X, -Scale.hY() });
	//}
	//else if (CurMapScale.Y <= CurPos.Y + Scale.hY())
	//{
	//	Transform.SetLocalPosition(float4{ CurPos.X, CurMapScale.Y - Scale.hY() }); 
	//}
}

void HowlingGale_Actor::MoveUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 MoveDir = float4::ZERO;
	GameEngineColor CheckColor = GROUND_COLOR;

	switch (Dir)
	{
	case ActorDir::Right:
		MoveDir = float4::RIGHT;
		break;
	case ActorDir::Left:
		MoveDir = float4::LEFT;
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
	MovePos += MoveDir * _Delta * Speed;

	// 올라가는 경사면
	CheckColor = CheckGroundColor(MovePos + float4::UP);
	if ((GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
	{
		float UpYPivot = 1.0f;
		GameEngineColor PivotColor = GROUND_COLOR;
		while (UP_PIXEL_LIMIT >= UpYPivot && (GROUND_COLOR == PivotColor || FLOOR_COLOR == PivotColor))
		{
			++UpYPivot;
			PivotColor = CheckGroundColor(MovePos + float4(0, UpYPivot));
		}

		while (UP_PIXEL_LIMIT >= UpYPivot && (GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
		{
			MovePos += float4::UP;
			CheckColor = CheckGroundColor(MovePos + float4::UP);
		}
	}

	// 내려가는 경사면
	CheckColor = CheckGroundColor(MovePos);
	if ((GROUND_COLOR != CheckColor && FLOOR_COLOR != CheckColor))
	{
		float DownYPivot = 0.0f;
		GameEngineColor PivotColor = LADDER_COLOR;
		while (-DOWN_PIXEL_LIMIT < DownYPivot && (GROUND_COLOR != PivotColor && FLOOR_COLOR != PivotColor))
		{
			--DownYPivot;
			PivotColor = CheckGroundColor(MovePos + float4(0, DownYPivot));
		}

		while (-DOWN_PIXEL_LIMIT < DownYPivot && (GROUND_COLOR != CheckColor && FLOOR_COLOR != CheckColor))
		{
			MovePos += float4::DOWN;
			CheckColor = CheckGroundColor(MovePos);
		}
	}
	Transform.AddLocalPosition(MovePos);
}