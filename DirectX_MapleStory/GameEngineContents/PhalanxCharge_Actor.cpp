#include "PreCompile.h"
#include "PhalanxCharge_Actor.h"
#include "HitRenderManager.h"
#include "BaseWindActor.h"

PhalanxCharge_Actor* PhalanxCharge_Actor::Main_PhalanxCharge = nullptr;

#define SPEED 150.0f

PhalanxCharge_Actor::PhalanxCharge_Actor()
{
	
}

PhalanxCharge_Actor::~PhalanxCharge_Actor()
{

}

void PhalanxCharge_Actor::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseSkillActor::LevelStart(_PrevLevel);
}

void PhalanxCharge_Actor::LevelEnd(GameEngineLevel* _NextLevel)
{
	BaseSkillActor::LevelEnd(_NextLevel);
	Main_PhalanxCharge = nullptr;
}

void PhalanxCharge_Actor::Start()
{
	GameEngineInput::AddInputObject(this);

	Main_PhalanxCharge = this;

	BaseSkillActor::Start();
	MainSpriteRenderer->CreateAnimation("Ready", "PhalanxCharge_Ready", 0.06f);
	MainSpriteRenderer->CreateAnimation("Attack", "PhalanxCharge_Attack", 0.09f);
	MainSpriteRenderer->CreateAnimation("Attack_Loop", "PhalanxCharge_Attack", 0.09f, 7, 18);
	MainSpriteRenderer->CreateAnimation("Death", "PhalanxCharge_Death", 0.02f);
	MainSpriteRenderer->ChangeAnimation("Ready");
	MainSpriteRenderer->SetPivotValue({0.5f, 0.82f});
	MainSpriteRenderer->AutoSpriteSizeOn();
	Speed = SPEED;

	IsUpdate = false;
	LiveTime = 20.0f;
	SkillCollision->Off();

	MainSpriteRenderer->SetEndEvent("Ready", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->ChangeAnimation("Attack");
			IsUpdate = true;
			SkillCollision->On();
		}
	);

	MainSpriteRenderer->SetEndEvent("Attack", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->ChangeAnimation("Attack_Loop");
		}
	);

	MainSpriteRenderer->SetStartEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->SetPivotValue({ 0.5f, 0.77f });
		}
	);

	MainSpriteRenderer->SetEndEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			Main_PhalanxCharge = nullptr;
			Death();
		}
	);

	Scale = {280, 100};
	SkillCollision->Transform.SetLocalScale(Scale);
	SkillCollision->Transform.SetLocalPosition({0, 50});

}

void PhalanxCharge_Actor::Update(float _Delta)
{
	LiveTime -= _Delta;
	SoundLoopTime -= _Delta;

	if (0.0f >= LiveTime || 70 <= HitCount)
	{
		MainSpriteRenderer->ChangeAnimation("Death");
	}

	if (0.0f >= SoundLoopTime)
	{
		PhalanPlayer = GameEngineSound::SoundPlay("PhalanxCharge_Loop.mp3");
		PhalanPlayer.SetVolume(GlobalValue::SkillVolume);
		SoundLoopTime = SOUNDLOOP_DELAY;
	}

	if (true == IsGround && 0.0f > MoveVectorForce.Y)
	{
		GravityReset();
		MoveVectorForceYReset();
	}

	BaseSkillActor::Update(_Delta);
	CollisionTimeUpdate(_Delta);

	if (SPEED == Speed && true == SkillCollision->Collision(CollisionOrder::Monster))
	{
		Speed = SPEED / 2;
	}
	else if (SPEED / 2 == Speed && false == SkillCollision->Collision(CollisionOrder::Monster))
	{
		Speed = SPEED;
	}

	SkillCollision->Collision(CollisionOrder::Monster, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			for (size_t i = 0; i < _CollisionGroup.size(); i++)
			{
				std::shared_ptr<GameEngineCollision> _Other = std::dynamic_pointer_cast<GameEngineCollision>(_CollisionGroup[i]->shared_from_this());
				if (false == CollisionTime.contains(_Other))
				{
					CollisionTime[_Other] = 0.0f;
				}

				if (0.0f >= CollisionTime[_Other])
				{
					HitCount += 1;
					HitRenderManager::MainHitRenderManager->HitPrint("PhalanxCharge_Hit", 1, _Other->GetParentObject());
					CollisionTime[_Other] = HIT_TIME;
				}
			}
		}
	);

	if (true == GameEngineInput::IsDown('E', this) && (true == MainSpriteRenderer->IsCurAnimation("Attack") || true == MainSpriteRenderer->IsCurAnimation("Attack_Loop")))
	{
		SwitchDir();
	}
}

void PhalanxCharge_Actor::SwitchDir()
{
	switch (Dir)
	{
	case ActorDir::Right:
		SetDir(ActorDir::Left);
		break;
	case ActorDir::Left:
		SetDir(ActorDir::Right);
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void PhalanxCharge_Actor::CollisionTimeUpdate(float _Delta)
{
	for (std::pair<const std::shared_ptr<GameEngineCollision>, float>& _Pair : CollisionTime)
	{
		_Pair.second -= _Delta;
	}
}
