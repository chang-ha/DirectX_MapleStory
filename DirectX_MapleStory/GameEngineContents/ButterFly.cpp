#include "PreCompile.h"
#include "ButterFly.h"

ButterFly::ButterFly()
{

}

ButterFly::~ButterFly()
{

}

void ButterFly::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void ButterFly::Start()
{
	if (nullptr == FlyRenderer)
	{
		FlyRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	}
	FlyRenderer->AutoSpriteSizeOn();
	FlyRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::monster });

	if (nullptr == GameEngineSprite::Find(""))
	{

	}
}

void ButterFly::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void ButterFly::Release()
{
	if (nullptr != FlyRenderer)
	{
		FlyRenderer->Death();
		FlyRenderer = nullptr;
	}
}

void ButterFly::Init(int _Phase)
{

}


void ButterFly::ChangeState(ButterFlyState _State)
{
	if (_State != State)
	{
		// State Start
		switch (_State)
		{
		case ButterFlyState::Ready:
			ReadyStart();
			break;
		case ButterFlyState::Move:
			MoveStart();
			break;
		case ButterFlyState::Attack:
			AttackStart();
			break;
		case ButterFlyState::Death:
			DeathStart();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값을 시작하려고 했습니다.");
			break;
		}
	}

	State = _State;
}

void ButterFly::StateUpdate(float _Delta)
{
	switch (State)
	{
	case ButterFlyState::Ready:
		return ReadyUpdate(_Delta);
	case ButterFlyState::Move:
		return MoveUpdate(_Delta);
	case ButterFlyState::Attack:
		return AttackUpdate(_Delta);
	case ButterFlyState::Death:
		return DeathUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void ButterFly::ReadyStart()
{

}

void ButterFly::MoveStart()
{

}

void ButterFly::AttackStart()
{

}

void ButterFly::DeathStart()
{

}

void ButterFly::ReadyUpdate(float _Delta)
{

}

void ButterFly::MoveUpdate(float _Delta)
{

}

void ButterFly::AttackUpdate(float _Delta)
{

}

void ButterFly::DeathUpdate(float _Delta)
{

}