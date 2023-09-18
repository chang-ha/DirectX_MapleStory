#include "PreCompile.h"
#include "HowlingGale_Actor.h"
#include "Player.h"
#include "ContentLevel.h"
#include "ContentMap.h"

#define UP_PIXEL_LIMIT 4
#define DOWN_PIXEL_LIMIT 4

HowlingGale_Actor* HowlingGale_Actor::MainHowlingGale = nullptr;

HowlingGale_Actor::HowlingGale_Actor()
{
	
}

HowlingGale_Actor::~HowlingGale_Actor()
{

}

void HowlingGale_Actor::ChangeState(HowlingGaleState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case HowlingGaleState::Ready:
			ReadyEnd();
			break;
		case HowlingGaleState::Attack:
			AttackEnd();
			break;
		case HowlingGaleState::Death:
			DeathEnd();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값을 끝내려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case HowlingGaleState::Ready:
			ReadyStart();
			break;
		case HowlingGaleState::Attack:
			AttackStart();
			break;
		case HowlingGaleState::Death:
			DeathStart();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 변경하려고 했습니다.");
			break;
		}
	}

	State = _State;
}

void HowlingGale_Actor::LevelStart(GameEngineLevel* _PrevLevel)
{
	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
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
	ReadyStart();

	// Renderer Event 1stack
	MainSpriteRenderer->SetEndEvent("Ready", [&](GameEngineRenderer* _Renderer)
		{
			ChangeState(HowlingGaleState::Attack);
		}
	);

	MainSpriteRenderer->SetEndEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			Death();
			MainHowlingGale = nullptr;
		}
	);
}

void HowlingGale_Actor::Update(float _Delta)
{
	BlockOutMap();
	StateUpdate(_Delta);
}

void HowlingGale_Actor::StateUpdate(float _Delta)
{
	switch (State)
	{
	case HowlingGaleState::Ready:
		return ReadyUpdate(_Delta);
	case HowlingGaleState::Attack:
		return AttackUpdate(_Delta);
	case HowlingGaleState::Death:
		return DeathUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void HowlingGale_Actor::BlockOutMap()
{
	float4 CurPos = Transform.GetWorldPosition();
	if (0 > CurPos.X - Scale.hX())
	{
		Transform.SetLocalPosition(float4{ Scale.hX(), CurPos.Y });
	}
	else if (CurMapScale.X <= CurPos.X + Scale.hX())
	{
		Transform.SetLocalPosition(float4{ CurMapScale.X - Scale.hX(), CurPos.Y });
	}

	// Need Test More
	CurPos.Y *= -1.0f;
	if (0 > CurPos.Y - Scale.hY())
	{
		Transform.SetLocalPosition(float4{ CurPos.X, -Scale.hY() });
	}
	else if (CurMapScale.Y <= CurPos.Y + Scale.hY())
	{
		Transform.SetLocalPosition(float4{ CurPos.X, CurMapScale.Y - Scale.hY() }); 
	}
}

void HowlingGale_Actor::ReadyStart()
{

}

void HowlingGale_Actor::AttackStart()
{
	MainSpriteRenderer->ChangeAnimation("Attack");
	Dir = Player::MainPlayer->GetDir();
}

void HowlingGale_Actor::DeathStart()
{
	MainSpriteRenderer->ChangeAnimation("Death");
}

void HowlingGale_Actor::ReadyEnd()
{

}

void HowlingGale_Actor::AttackEnd()
{

}

void HowlingGale_Actor::DeathEnd()
{

}

void HowlingGale_Actor::ReadyUpdate(float _Delta)
{

}

void HowlingGale_Actor::AttackUpdate(float _Delta)
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

void HowlingGale_Actor::DeathUpdate(float _Delta)
{

}