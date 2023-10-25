﻿#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "ButterFly.h"
#include "ButterFly_Ball.h"
#include "Player.h"

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

	MoveLocation.resize(9);
	LocationNumber.resize(8);

	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this));
	CurLocationIndex = Random.RandomInt(0, 8);
}

void ButterFly::Update(float _Delta)
{
	LiveTime -= _Delta;
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
	//Path
	switch (_Phase)
	{
	case 1:
		break;
	case 2:
		MoveLocation[0] = { 500, -435 };
		MoveLocation[1] = { 400, -635 };
		MoveLocation[2] = { 600, -1085 };
		MoveLocation[3] = { 1050, -1285 };
		MoveLocation[4] = { 1400, -1285 };
		MoveLocation[5] = { 1600, -885 };
		MoveLocation[6] = { 1400, -585 };
		MoveLocation[7] = { 1240, -285 };
		MoveLocation[8] = { 900, -285 };
		break;
	}

	FlyRenderer->CreateAnimation("Ready", "Phase" + std::to_string(_Phase) + "_ButterFly_Ready");
	FlyRenderer->CreateAnimation("Move", "Phase" + std::to_string(_Phase) + "_ButterFly_Move");
	FlyRenderer->CreateAnimation("Attack", "Phase" + std::to_string(_Phase) + "_ButterFly_Attack");
	FlyRenderer->CreateAnimation("Death", "Phase" + std::to_string(_Phase) + "_ButterFly_Death", 0.1f, -1, -1, false);

	FlyRenderer->SetFrameEvent("Attack", 8, [&](GameEngineSpriteRenderer* _Renderer)
		{
			std::shared_ptr<ButterFly_Ball> _Ball = GetLevel()->CreateActor<ButterFly_Ball>(UpdateOrder::Monster);
			_Ball->Init(Phase::Phase2);

			float4 CurPos = Transform.GetWorldPosition();
			float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
			float4 Vector = PlayerPos - CurPos;
			_Ball->SetDirVector(Vector.NormalizeReturn());

			float PivotValue = 0.0f;

			switch (Dir)
			{
			case ActorDir::Right:
				PivotValue = 50.0f;
				break;
			case ActorDir::Left:
				PivotValue = -50.0f;
				break;
			case ActorDir::Null:
			default:
				MsgBoxAssert("존재하지 않는 방향입니다.");
				break;
			}

			_Ball->Transform.SetLocalPosition(Transform.GetWorldPosition() + PivotValue);
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

	float4 CurPos = Transform.GetWorldPosition();
	float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
	
	if (0.0f >= PlayerPos.X - CurPos.X)
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
	if (true == FlyRenderer->IsCurAnimationEnd())
	{
		ChangeState(ButterFlyState::Move);
	}
}

void ButterFly::MoveUpdate(float _Delta)
{
	if (Fly_Max_MoveSpeed > MoveSpeed)
	{
		MoveSpeed += Fly_Accel_MoveSpeed * _Delta;
	}
	else if (Fly_Max_MoveSpeed <= MoveSpeed)
	{
		MoveSpeed = Fly_Max_MoveSpeed;
	}

	float4 CurPos = Transform.GetLocalPosition();
	float4 DestinationPos = MoveLocation[CurLocationIndex];
	MoveVector = DestinationPos - CurPos;
	Transform.AddLocalPosition(MoveVector.NormalizeReturn() * MoveSpeed * _Delta);

	if (0.0f >= MoveVector.X && Dir == ActorDir::Right)
	{
		Dir = ActorDir::Left;
		FlyRenderer->RightFlip();
		FlyRenderer->SetPivotValue({ 0.585f, 0.573f });
	}
	else if (0.0f < MoveVector.X && Dir == ActorDir::Left)
	{
		Dir = ActorDir::Right;
		FlyRenderer->LeftFlip();
		FlyRenderer->SetPivotValue({ 0.415f, 0.573f });
	}

	if (5.0f >= MoveVector.Size())
	{
		LocationNumber.clear();
		Transform.SetLocalPosition(DestinationPos);

		for (int i = 0; i < LocationNumber.capacity(); i++)
		{
			if (CurLocationIndex == i)
			{
				continue;
			}
			LocationNumber.push_back(i);
		}

		GameEngineRandom Random;
		Random.SetSeed(reinterpret_cast<long long>(this) + CurLocationIndex);
		int RandomInt = Random.RandomInt(0, static_cast<int>(LocationNumber.size() - 1));

		CurLocationIndex = LocationNumber[RandomInt];
		MoveSpeed = Fly_Default_MoveSpeed;
		ChangeState(ButterFlyState::Attack);
	}
}

void ButterFly::AttackUpdate(float _Delta)
{
	if (true == FlyRenderer->IsCurAnimationEnd())
	{
		ChangeState(ButterFlyState::Move);
	}

	if (0.0f >= LiveTime)
	{
		ChangeState(ButterFlyState::Death);
	}
}

void ButterFly::DeathUpdate(float _Delta)
{
	if (true == FlyRenderer->IsCurAnimationEnd())
	{
		Death();
	}
}