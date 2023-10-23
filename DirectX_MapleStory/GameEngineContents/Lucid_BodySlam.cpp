#include "PreCompile.h"
#include "Lucid_BodySlam.h"


Lucid_BodySlam::Lucid_BodySlam()
{

}

Lucid_BodySlam::~Lucid_BodySlam()
{

}

void Lucid_BodySlam::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Lucid_BodySlam::Start()
{
	MoveLocation.resize(14);
	MoveLocation[0] = float4(445, -685);
	MoveLocation[1] = float4(581, -836);
	MoveLocation[2] = float4(794, -1003);
	MoveLocation[3] = float4(1098, -1057);
	MoveLocation[4] = float4(1378, -1011);
	MoveLocation[5] = float4(1467, -852);
	MoveLocation[6] = float4(1428, -668);
	MoveLocation[7] = float4(1132, -382);
	MoveLocation[8] = float4(869, -372);
	MoveLocation[9] = float4(741, -490);
	MoveLocation[10] = float4(756, -682);
	MoveLocation[11] = float4(938, -841);
	MoveLocation[12] = float4(1204, -1007);
	MoveLocation[13] = float4(1378, -1007);

	if (nullptr == BodySlamRenderer)
	{
		BodySlamRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
		BodySlamRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::monster});
		BodySlamRenderer->AutoSpriteSizeOn();
	}

	if (nullptr == BodySlamCollision)
	{
		BodySlamCollision = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
		BodySlamCollision->Transform.SetLocalScale({250, 275});
		BodySlamCollision->Off();
	}

	BodySlamRenderer->CreateAnimation("Ready", "Lucid_BodySlam_Ready", 0.1f, -1, -1, false);
	BodySlamRenderer->CreateAnimation("Attack", "Lucid_BodySlam_Attack");
	BodySlamRenderer->CreateAnimation("Death", "Lucid_BodySlam_Death");
	ReadyStart();

	// Render Event
	BodySlamRenderer->SetEndEvent("Ready", [&](GameEngineRenderer* _Renderer)
		{
			ChangeState(BodySlamState::Attack);
			BodySlamCollision->On();
		}
	);

	Transform.SetLocalPosition({ 1085, -775});
	BodySlamRenderer->Off();
}

void Lucid_BodySlam::Update(float _Delta)
{
	GameEngineInput::AddInputObject(this);
	StateUpdate(_Delta);

	if (true == GameEngineInput::IsDown('B', this))
	{
		ChangeState(BodySlamState::Ready);
	}

	if (true == GameEngineInput::IsDown('N', this))
	{
		ChangeState(BodySlamState::Attack);
	}

	if (true == GameEngineInput::IsDown('M', this))
	{
		ChangeState(BodySlamState::Death);
	}
}

void Lucid_BodySlam::Release()
{
	if (nullptr != BodySlamRenderer)
	{
		BodySlamRenderer->Death();
		BodySlamRenderer = nullptr;
	}

	if (nullptr != BodySlamCollision)
	{
		BodySlamCollision->Death();
		BodySlamCollision = nullptr;
	}
}

void Lucid_BodySlam::ChangeState(BodySlamState _State)
{
	if (_State != State)
	{
		// State Start
		switch (_State)
		{
		case BodySlamState::Ready:
			ReadyStart();
			break;
		case BodySlamState::Attack:
			AttackStart();
			break;
		case BodySlamState::Death:
			DeathStart();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값을 시작하려고 했습니다.");
			break;
		}
	}

	State = _State;
}

void Lucid_BodySlam::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BodySlamState::Ready:
		return ReadyUpdate(_Delta);
	case BodySlamState::Attack:
		return AttackUpdate(_Delta);
	case BodySlamState::Death:
		return DeathUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void Lucid_BodySlam::ChangeDir(ActorDir _Dir)
{
	if (Dir == _Dir)
	{
		return;
	}
	Dir = _Dir;

	switch (Dir)
	{
	case ActorDir::Right:
		switch (State)
		{
		case BodySlamState::Ready:
			break;
		case BodySlamState::Attack:
			break;
		case BodySlamState::Death:
			BodySlamRenderer->SetPivotValue({ 0.5f, 0.5f });
			break;
		default:
			break;
		}
		BodySlamRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		switch (State)
		{
		case BodySlamState::Ready:
			BodySlamRenderer->SetPivotValue({ 0.6f, 0.5f });
			break;
		case BodySlamState::Attack:
			BodySlamRenderer->SetPivotValue({ 0.5f, 0.5f });
			break;
		case BodySlamState::Death:
			BodySlamRenderer->SetPivotValue({ 0.5f, 0.5f });
			break;
		default:
			break;
		}
		BodySlamRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void Lucid_BodySlam::ReadyStart()
{
	BodySlamRenderer->ChangeAnimation("Ready");
	BodySlamRenderer->SetPivotValue({ 0.63f, 0.55f });
}

void Lucid_BodySlam::AttackStart()
{
	BodySlamRenderer->ChangeAnimation("Attack");
	BodySlamRenderer->SetPivotValue({ 0.515f, 0.535f });
}

void Lucid_BodySlam::DeathStart()
{
	BodySlamRenderer->ChangeAnimation("Death");
	BodySlamRenderer->SetPivotValue({ 0.462f, 0.54f });
}

void Lucid_BodySlam::ReadyUpdate(float _Delta)
{
	DelayTime -= _Delta;
	if (0.0f >= DelayTime)
	{
		BodySlamRenderer->On();
	}
}

void Lucid_BodySlam::AttackUpdate(float _Delta)
{
	
}

void Lucid_BodySlam::DeathUpdate(float _Delta)
{

}