#include "PreCompile.h"
#include "HowlingGale_Actor.h"

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

void HowlingGale_Actor::ReadyStart()
{
	}
void HowlingGale_Actor::AttackStart()
{
	MainSpriteRenderer->ChangeAnimation("Attack");
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
	}
void HowlingGale_Actor::DeathUpdate(float _Delta)
{
}