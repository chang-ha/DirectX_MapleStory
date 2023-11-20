﻿#include "PreCompile.h"
#include "Golem.h"
#include "ReleaseFunction.h"

Golem::Golem()
{

}

Golem::~Golem()
{

}

void Golem::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentActor::LevelEnd(_NextLevel);
	Death();
}

void Golem::Start()
{
	if (nullptr == GameEngineSound::FindSound("Golem_Summon.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Boss\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "Golem_Summon.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "Golem_Death.mp3");
	}

	ContentActor::Start();
	HP = 25;

	if (nullptr == MainSpriteRenderer)
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
		MainSpriteRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::monster});
		MainSpriteRenderer->AutoSpriteSizeOn();
	}

	if (nullptr == GolemCollision)
	{
		GolemCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
		GolemCollision->Transform.SetLocalScale({ 150, 200 });
		GolemCollision->Transform.SetLocalPosition({ 0, 100 });
		GolemCollision->Off();
	}

	if (nullptr == TakeDownCollision)
	{
		TakeDownCollision = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
		TakeDownCollision->Transform.SetLocalScale({ 30, 30 });
		TakeDownCollision->Transform.SetLocalPosition({ 0, 30 });
		TakeDownCollision->Off();
	}
}

void Golem::Update(float _Delta)
{
	ContentActor::Update(_Delta);
	StateUpdate(_Delta);

	if (0 >= HP)
	{
		ChangeState(GolemState::Death);
	}

	if (Golem_Phase::Phase1 == Phase)
	{
		AttackFunction.AttackUpdate(TakeDownCollision, CollisionOrder::Player, "Lucid_Phase1_Golem_TakeDown_Hit", 1, 33, false);
	}
}

void Golem::Release()
{
	ContentActor::Release();

	if (nullptr != GolemCollision)
	{
		GolemCollision->Death();
		GolemCollision = nullptr;
	}

	if (nullptr != TakeDownCollision)
	{
		TakeDownCollision->Death();
		TakeDownCollision = nullptr;
	}

	AttackFunction.CollisionActor.clear();

	if (nullptr != GameEngineSprite::Find("Lucid_Phase" + PhaseNumber + "_Golem_Ready"))
	{
		ReleaseFunction::FolderRelease("Lucid_Phase" + PhaseNumber + "_Golem_Ready", "Phase" + PhaseNumber + "_Golem_Ready_");
		ReleaseFunction::FolderRelease("Lucid_Phase" + PhaseNumber + "_Golem_Attack", "Phase" + PhaseNumber + "_Golem_Attack_");
		ReleaseFunction::FolderRelease("Lucid_Phase" + PhaseNumber + "_Golem_Death", "Phase" + PhaseNumber + "_Golem_Death_");
		ReleaseFunction::FolderRelease("Lucid_Phase" + PhaseNumber + "_Golem_Idle", "Phase" + PhaseNumber + "_Golem_Idle_");
		ReleaseFunction::FolderRelease("Lucid_Phase" + PhaseNumber + "_Golem_Revive", "Phase" + PhaseNumber + "_Golem_Revive_");
	}

	if (nullptr != GameEngineSprite::Find("Lucid_Phase1_Golem_TakeDown_Hit"))
	{
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_TakeDown_Hit", "TakeDown_Hit_");
	}
}

void Golem::Init(int _PhaseNumber)
{
	PhaseNumber = "";
	PhaseNumber = std::to_string(_PhaseNumber);

	if (nullptr == GameEngineSprite::Find("Lucid_Phase" + PhaseNumber + "_Golem_Ready"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase" + PhaseNumber + "_Golem");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_Phase" + PhaseNumber + "_Golem_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	MainSpriteRenderer->CreateAnimation("Ready", "Lucid_Phase" + PhaseNumber + "_Golem_Ready", 0.09f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("Revive", "Lucid_Phase" + PhaseNumber + "_Golem_Revive", 0.1f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("Idle", "Lucid_Phase" + PhaseNumber + "_Golem_Idle");
	MainSpriteRenderer->CreateAnimation("Attack", "Lucid_Phase" + PhaseNumber + "_Golem_Attack");
	MainSpriteRenderer->CreateAnimation("Death", "Lucid_Phase" + PhaseNumber + "_Golem_Death", 0.09f);

	ReadyStart();
	GravityOff();
	MaxGraviry = 100.0f;

	MainSpriteRenderer->SetFrameEvent("Ready", 9, [&](GameEngineSpriteRenderer*)
		{
			GravityOn();
			MoveVectorForce.Y -= 800.0f;
		}
	);

	MainSpriteRenderer->SetFrameEvent("Revive", 2, [&](GameEngineSpriteRenderer*)
		{
			TakeDownCollision->Off();
		}
	);

	MainSpriteRenderer->SetStartEvent("Death", [&](GameEngineSpriteRenderer*)
		{
			GolemCollision->Off();
		}
	);

	MainSpriteRenderer->SetEndEvent("Death", [&](GameEngineSpriteRenderer*)
		{
			Death();
		}
	);
}

void Golem::ChangeState(GolemState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case GolemState::Ready:
			break;
		case GolemState::Revive:
			break;
		case GolemState::Idle:
			break;
		case GolemState::Attack:
			break;
		case GolemState::Death:
			break;
		case GolemState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값을 끝내려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case GolemState::Ready:
			break;
		case GolemState::Revive:
			ReviveStart();
			break;
		case GolemState::Idle:
			IdleStart();
			break;
		case GolemState::Attack:
			AttackStart();
			break;
		case GolemState::Death:
			DeathStart();
			break;
		case GolemState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값을 시작하려고 했습니다.");
			break;
		}
	}

	State = _State;
}

void Golem::StateUpdate(float _Delta)
{
	switch (State)
	{
	case GolemState::Ready:
		return ReadyUpdate(_Delta);
	case GolemState::Revive:
		return ReviveUpdate(_Delta);
	case GolemState::Idle:
		return IdleUpdate(_Delta);
	case GolemState::Attack:
		return AttackUpdate(_Delta);
	case GolemState::Death:
		return DeathUpdate(_Delta);
	case GolemState::Null:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void Golem::ReadyUpdate(float _Delta)
{
	if (true == IsGround)
	{
		TakeDownCollision->On();
		ChangeState(GolemState::Revive);
	}
}

void Golem::ReadyStart()
{
	MainSpriteRenderer->ChangeAnimation("Ready");
	MainSpriteRenderer->SetPivotValue({ 0.48f, 0.8f });
	GolemPlayer = GameEngineSound::SoundPlay("Golem_Summon.mp3");
}

void Golem::ReviveStart()
{
	MainSpriteRenderer->ChangeAnimation("Revive");
	MainSpriteRenderer->SetPivotValue({0.49f, 0.75f});
}

void Golem::IdleStart()
{
	GolemCollision->On();
	MainSpriteRenderer->ChangeAnimation("Idle");
	MainSpriteRenderer->SetPivotValue({0.49f, 1.0f});
}

void Golem::AttackStart()
{
	MainSpriteRenderer->ChangeAnimation("Attack");
	MainSpriteRenderer->SetPivotValue({ 0.473f, 0.808f });
}

void Golem::DeathStart()
{
	MainSpriteRenderer->ChangeAnimation("Death");
	MainSpriteRenderer->SetPivotValue({ 0.52f, 0.9f });
	GolemCollision->Off();
	GolemPlayer = GameEngineSound::SoundPlay("Golem_Death.mp3");
}

void Golem::ReviveUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GolemState::Idle);
	}
}

void Golem::IdleUpdate(float _Delta)
{

}

void Golem::AttackUpdate(float _Delta)
{
	
}

void Golem::DeathUpdate(float _Delta)
{
}