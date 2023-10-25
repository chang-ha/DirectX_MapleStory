#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "ButterFly.h"
#include "ButterFly_Ball.h"

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

	std::shared_ptr<GameEngineCollision> Test = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
}

void ButterFly::Update(float _Delta)
{
	GameEngineInput::AddInputObject(this);
	StateUpdate(_Delta);

	if (true == GameEngineInput::IsDown('V', this))
	{
		ChangeState(ButterFlyState::Ready);
	}

	if (true == GameEngineInput::IsDown('B', this))
	{
		ChangeState(ButterFlyState::Move);
	}

	if (true == GameEngineInput::IsDown('N', this))
	{
		ChangeState(ButterFlyState::Attack);
	}

	if (true == GameEngineInput::IsDown('M', this))
	{
		ChangeState(ButterFlyState::Death);
	}
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
	FlyRenderer->CreateAnimation("Ready", "Phase" + std::to_string(_Phase) + "_ButterFly_Ready", 0.1f, -1, -1, false);
	FlyRenderer->CreateAnimation("Move", "Phase" + std::to_string(_Phase) + "_ButterFly_Move");
	FlyRenderer->CreateAnimation("Attack", "Phase" + std::to_string(_Phase) + "_ButterFly_Attack");
	FlyRenderer->CreateAnimation("Death", "Phase" + std::to_string(_Phase) + "_ButterFly_Death");

	FlyRenderer->SetFrameEvent("Attack", 8, [&](GameEngineSpriteRenderer* _Renderer)
		{
			std::shared_ptr<ButterFly_Ball> _Ball = GetLevel()->CreateActor<ButterFly_Ball>(UpdateOrder::Monster);
			_Ball->Init(Phase::Phase2);
		});
	ReadyStart();
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
	FlyRenderer->ChangeAnimation("Ready");

	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this));
	int RandomInt = Random.RandomInt(0, 1);

	if (0 == RandomInt)
	{
		Dir = ActorDir::Left;
	}
	else
	{
		Dir = ActorDir::Right;
	}

	switch (Dir)
	{
	case ActorDir::Right:
		FlyRenderer->SetPivotValue({ 0.48f, 0.55f });
		FlyRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		FlyRenderer->SetPivotValue({ 0.52f, 0.55f });
		FlyRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void ButterFly::MoveStart()
{
	FlyRenderer->ChangeAnimation("Move");

	switch (Dir)
	{
	case ActorDir::Right:
		FlyRenderer->SetPivotValue({ 0.415f, 0.573f });
		FlyRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		FlyRenderer->SetPivotValue({ 0.585f, 0.573f });
		FlyRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void ButterFly::AttackStart()
{
	FlyRenderer->ChangeAnimation("Attack");

	switch (Dir)
	{
	case ActorDir::Right:
		FlyRenderer->SetPivotValue({ 0.45f, 0.523f });
		FlyRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		FlyRenderer->SetPivotValue({ 0.55f, 0.523f });
		FlyRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void ButterFly::DeathStart()
{
	FlyRenderer->ChangeAnimation("Death");

	switch (Dir)
	{
	case ActorDir::Right:
		FlyRenderer->SetPivotValue({ 0.445f, 0.545f });
		FlyRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		FlyRenderer->SetPivotValue({ 0.555f, 0.545f });
		FlyRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
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