#include "PreCompile.h"
#include "MushRoom.h"

MushRoom::MushRoom()
{

}

MushRoom::~MushRoom()
{

}

void MushRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void MushRoom::Start()
{
	MushRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	MushRenderer->AutoSpriteSizeOn();

	MushCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	MushCollision->Transform.SetLocalScale({ 125, 220 });
	MushCollision->Transform.SetLocalPosition({0, 100});
	// MushCollision->Off();

	if (nullptr == GameEngineSprite::Find("Lucid_Phase1_MushRoom_Move"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase1_MushRoom");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_Phase1_MushRoom_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	MushRenderer->CreateAnimation("Ready", "Lucid_Phase1_MushRoom_Ready");
	MushRenderer->CreateAnimation("Idle", "Lucid_Phase1_MushRoom_Idle");
	MushRenderer->CreateAnimation("Move", "Lucid_Phase1_MushRoom_Move");
	MushRenderer->CreateAnimation("Death", "Lucid_Phase1_MushRoom_Death");
	MushRenderer->ChangeAnimation("Ready");

	////// Render Event
	MushRenderer->SetEndEvent("Ready", [&](GameEngineSpriteRenderer*)
		{
			// MushCollision->On();
			ChangeState(MushState::Idle);
		}
	);

	MushRenderer->SetEndEvent("Death", [&](GameEngineSpriteRenderer*)
		{
			Death();
		}
	);
}

void MushRoom::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void MushRoom::Release()
{
	if (nullptr != MushRenderer)
	{
		MushRenderer->Death();
		MushRenderer = nullptr;
	}

	if (nullptr != MushCollision)
	{
		MushCollision->Death();
		MushCollision = nullptr;
	}
}

void MushRoom::ChangeState(MushState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case MushState::Ready:
			break;
		case MushState::Idle:
			break;
		case MushState::Move:
			break;
		case MushState::Death:
			break;
		case MushState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값을 끝내려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case MushState::Ready:
			break;
		case MushState::Idle:
			IdleStart();
			break;
		case MushState::Move:
			MoveStart();
			break;
		case MushState::Death:
			DeathStart();
			break;
		case MushState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값을 시작하려고 했습니다.");
			break;
		}
	}

	State = _State;
}

void MushRoom::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MushState::Ready:
		return;
	case MushState::Idle:
		return IdleUpdate(_Delta);
	case MushState::Move:
		return MoveUpdate(_Delta);
	case MushState::Death:
		return;
	case MushState::Null:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void MushRoom::IdleStart()
{
	MushRenderer->ChangeAnimation("Idle");
	MushRenderer->SetPivotType(PivotType::Bottom);
}

void MushRoom::MoveStart()
{
	MushRenderer->ChangeAnimation("Move");
}

void MushRoom::DeathStart()
{
	MushRenderer->ChangeAnimation("Death");
}

void MushRoom::IdleUpdate(float _Delta)
{
	WaitTime -= _Delta;

	if (0.0f >= WaitTime && true == MushRenderer->IsCurAnimationEnd())
	{
		ChangeState(MushState::Move);
	}
}

void MushRoom::MoveUpdate(float _Delta)
{
	Transform.AddLocalPosition(MoveDir * 35.0f * _Delta);

	if (300.0f >= Transform.GetLocalPosition().X || 1700.0f <= Transform.GetLocalPosition().X)
	{
		ChangeState(MushState::Death);
	}
}

void MushRoom::SetDir(ActorDir _Dir)
{
	Dir = _Dir;

	switch (Dir)
	{
	case ActorDir::Right:
		MushRenderer->LeftFlip();
		MushRenderer->SetPivotValue({ 0.489f, 0.88f });
		MoveDir = float4::RIGHT;
		break;
	case ActorDir::Left:
		MushRenderer->SetPivotValue({ 0.511f, 0.88f });
		MoveDir = float4::LEFT;
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}
