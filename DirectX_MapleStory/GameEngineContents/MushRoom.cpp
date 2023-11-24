#include "PreCompile.h"
#include "MushRoom.h"
#include "ReleaseFunction.h"

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
	if (nullptr == GameEngineSound::FindSound("MushRoom_Summon.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Boss\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "MushRoom_Summon.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "MushRoom_Death.mp3");
	}

	DamageSkinPivot = { 0, 230 };
	HP = 50;

	MushRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	MushRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::monster});
	MushRenderer->AutoSpriteSizeOn();

	MushCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	MushCollision->Transform.SetLocalScale({ 125, 220 });
	MushCollision->Transform.SetLocalPosition({0, 100});
	MushCollision->Off();

	AttackCollision = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
	AttackCollision->Transform.SetLocalScale({ 80, 80 });
	AttackCollision->Transform.SetLocalPosition({ -10, 80 });
	AttackCollision->Off();

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
	MushRoomPlayer = GameEngineSound::SoundPlay("MushRoom_Summon.mp3");
	MushRoomPlayer.SetVolume(0.5f);

	////// Render Event
	MushRenderer->SetEndEvent("Ready", [&](GameEngineSpriteRenderer*)
		{
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

	if (0 >= HP)
	{
		ChangeState(MushState::Death);
	}

	AttackFunction.AttackUpdate(AttackCollision, CollisionOrder::Player, "", 1.0f, 1, 10, false);
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

	if (nullptr != AttackCollision)
	{
		AttackCollision->Death();
		AttackCollision = nullptr;
	}

	if (nullptr != GameEngineSprite::Find("Lucid_Phase1_MushRoom_Move"))
	{
		ReleaseFunction::FolderRelease("Lucid_Phase1_MushRoom_Move", "MushRoom_Move_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_MushRoom_Death", "MushRoom_Death_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_MushRoom_Idle", "MushRoom_Idle_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_MushRoom_Ready", "MushRoom_Ready_");
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
	MushCollision->On();
	AttackCollision->On();
	MushRenderer->ChangeAnimation("Idle");
	MushRenderer->SetPivotType(PivotType::Bottom);
}

void MushRoom::MoveStart()
{
	MushRenderer->ChangeAnimation("Move");
}

void MushRoom::DeathStart()
{
	MushCollision->Off();
	AttackCollision->Off();
	MushRenderer->ChangeAnimation("Death");
	MushRoomPlayer = GameEngineSound::SoundPlay("MushRoom_Death.mp3");
	MushRoomPlayer.SetVolume(0.5f);
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
