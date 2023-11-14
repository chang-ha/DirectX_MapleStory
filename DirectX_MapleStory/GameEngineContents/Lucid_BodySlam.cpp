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
	MoveLocation[0] = { 15.0f, float4(445, -865) };
	MoveLocation[1] = { 20.0f, float4(581, -741) };
	MoveLocation[2] = { 25.0f, float4(794, -547) };
	MoveLocation[3] = { 30.0f, float4(1098, -493) };
	MoveLocation[4] = { 25.0f, float4(1378, -539) };
	MoveLocation[5] = { 20.0f,float4(1467, -698) };
	MoveLocation[6] = { 15.0f, float4(1428, -882) };
	MoveLocation[7] = { 20.0f, float4(1132, -1168) };
	MoveLocation[8] = { 25.0f, float4(869, -1178) };
	MoveLocation[9] = { 20.0f, float4(741, -1060) };
	MoveLocation[10] = { 15.0f, float4(756, -868) };
	MoveLocation[11] = { 20.0f, float4(938, -709) };
	MoveLocation[12] = { 25.0f,float4(1204, -543) };
	MoveLocation[13] = { 20.0f, float4(1378, -543) };

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

	BodySlamRenderer->SetEndEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			BodySlamCollision->Off();
			Death();
		}
	);

	Transform.SetLocalPosition({ 1085, -775});
	BodySlamRenderer->Off();
	Dir = ActorDir::Right;
}

void Lucid_BodySlam::Update(float _Delta)
{
	StateUpdate(_Delta);
	AttackFunction.AttackUpdate(BodySlamCollision, CollisionOrder::Player, "", 1.0f, 1, 50, false);
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
	BodySlamRenderer->LeftFlip();
	BodySlamRenderer->SetPivotValue({ 0.538f, 0.54f });
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
	float4 CurPos = Transform.GetLocalPosition();
	float4 DestinationPos = MoveLocation[CurLocationIndex].DestinationPos;
	MoveVector = DestinationPos - CurPos;
	Transform.AddLocalPosition(MoveVector.NormalizeReturn() * BaseSpeed * MoveLocation[CurLocationIndex].PlusMoveSpeed * _Delta);

	if (0.0f >= MoveVector.X && Dir == ActorDir::Right)
	{
		Dir = ActorDir::Left;
		BodySlamRenderer->RightFlip();
	}
	else if (0.0f < MoveVector.X && Dir == ActorDir::Left)
	{
		Dir = ActorDir::Right;
		BodySlamRenderer->LeftFlip();
	}
	
	if (10.0f >= MoveVector.Size())
	{
		Transform.SetLocalPosition(DestinationPos);
		++CurLocationIndex;
	}

	if (MoveLocation.size() == CurLocationIndex)
	{
		ChangeState(BodySlamState::Death);
	}
}

void Lucid_BodySlam::DeathUpdate(float _Delta)
{

}