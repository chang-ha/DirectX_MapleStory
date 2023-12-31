﻿#include "PreCompile.h"
#include "Dragon.h"
#include "ReleaseFunction.h"

#define DELAY_TIME 1.0f
#define Dir_Up 1.0f
#define Dir_Down -1.0f

Dragon::Dragon()
{

}

Dragon::~Dragon()
{

}

void Dragon::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Dragon::Start()
{
	BreathRenderers.resize(7);
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		if (nullptr == BreathRenderers[i])
		{
			BreathRenderers[i] = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTERATTACK);
			BreathRenderers[i]->Transform.SetLocalPosition({0, 0, RenderDepth::monsterattack});
		}
	}

	if (nullptr == DragonRenderer)
	{
		DragonRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::DRAGON);
		DragonRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::dragon });
		DragonRenderer->AutoSpriteSizeOn();
		DragonRenderer->SetPivotType(PivotType::Bottom);
	}

	if (nullptr == BreathCollision)
	{
		BreathCollision = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
		BreathCollision->Transform.SetLocalScale({ 1800, 400 });
		BreathCollision->Off();
	}

	if (nullptr == GameEngineSprite::Find("Lucid_Phase1_Dragon_Move"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase1_Dragon");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_Phase1_Dragon_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	if (nullptr == GameEngineSound::FindSound("DragonBreath.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BossRoom\\DragonBreath.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
	}

	DragonRenderer->CreateAnimation("Idle", "Lucid_Phase1_Dragon_Move", 0, 0, 0, false);
	DragonRenderer->CreateAnimation("Move", "Lucid_Phase1_Dragon_Move", 0.15f);
	DragonRenderer->CreateAnimation("Breath", "Lucid_Phase1_Dragon_Breath", 0.15f, 0, 35, false);
	IdleStart();

	// Breath
	DragonRenderer->SetFrameEvent("Breath", 10, [&](GameEngineSpriteRenderer*)
		{
			BreathOn();
			BreathCollision->On();
			switch (Dir)
			{
			case ActorDir::Right:
				DragonRenderer->SetPivotValue({ 0.65f, 0.8f });
				break;
			case ActorDir::Left:
				DragonRenderer->SetPivotValue({ 0.35f, 0.8f });
				break;
			case ActorDir::Null:
			default:
				MsgBoxAssert("존재하지 않는 방향입니다.");
				break;
			}

			if (0.0f != Breath_MoveDir)
			{
				IsMoveBreath = true;
			}
		}
	);

	DragonRenderer->SetFrameEvent("Breath", 33, [&](GameEngineSpriteRenderer*)
		{
			BreathOff();
			BreathCollision->Off();
		}
	);

	// Create Animation
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		BreathRenderers[i]->CreateAnimation("Attack", "Lucid_Phase1_Dragon_Attack", 0.15f);
		BreathRenderers[i]->ChangeAnimation("Attack");
		BreathRenderers[i]->AutoSpriteSizeOn();
		BreathRenderers[i]->Off();
	}

	Delay = DELAY_TIME;
}

void Dragon::Update(float _Delta)
{
	StateUpdate(_Delta);
	AttackFunction.AttackUpdate(BreathCollision, CollisionOrder::Player, "Lucid_Phase1_Dragon_Attack_Hit", 0.2f, 1, PLAYER_MAX_HP, false, PivotType::Center);
}

void Dragon::Release()
{
	if (nullptr != DragonRenderer)
	{
		DragonRenderer->Death();
		DragonRenderer = nullptr;
	}

	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		if (nullptr != BreathRenderers[i])
		{
			BreathRenderers[i]->Death();
			BreathRenderers[i] = nullptr;
		}
	}


	if (nullptr != BreathCollision)
	{
		BreathCollision->Death();
		BreathCollision = nullptr;
	}

	AttackFunction.CollisionTime.clear();

	if (nullptr != GameEngineSprite::Find("Lucid_Phase1_Dragon_Move"))
	{
		ReleaseFunction::FolderRelease("Lucid_Phase1_Dragon_Move", "Move_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Dragon_Breath", "Breath_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Dragon_Attack", "Attack_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Dragon_Attack_Hit", "Attack_Hit_");
	}
}

void Dragon::SetDir(ActorDir _Dir)
{
	Dir = _Dir;
	switch (Dir)
	{
		break;
	case ActorDir::Right:
		DragonRenderer->LeftFlip();
		RightBreath();
		break;
	case ActorDir::Left:
		DragonRenderer->RightFlip();
		LeftBreath();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void Dragon::ChangeState(DragonState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case DragonState::Idle:
			IdleEnd();
			break;
		case DragonState::Down:
			DownEnd();
			break;
		case DragonState::Up:
			UpEnd();
			break;
		case DragonState::Breath:
			BreathEnd();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 변경하려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case DragonState::Idle:
			IdleStart();
			break;
		case DragonState::Down:
			DownStart();
			break;
		case DragonState::Up:
			UpStart();
			break;
		case DragonState::Breath:
			BreathStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Dragon::StateUpdate(float _Delta)
{
	switch (State)
	{
	case DragonState::Idle:
		return IdleUpdate(_Delta);
	case DragonState::Down:
		return DownUpdate(_Delta);
	case DragonState::Up:
		return UpUpdate(_Delta);
	case DragonState::Breath:
		return BreathUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void Dragon::IdleStart()
{
	DragonRenderer->ChangeAnimation("Idle");
}

void Dragon::DownStart()
{
	DragonRenderer->ChangeAnimation("Move");
}

void Dragon::UpStart()
{
	DragonRenderer->ChangeAnimation("Move");
}

void Dragon::BreathStart()
{
	DragonRenderer->ChangeAnimation("Breath");
	switch (Dir)
	{
	case ActorDir::Right:
		DragonRenderer->SetPivotValue({ 0.63f, 0.88f });
		break;
	case ActorDir::Left:
		DragonRenderer->SetPivotValue({ 0.37f, 0.88f });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	GameEngineSoundPlayer BreathSound = GameEngineSound::SoundPlay("DragonBreath.mp3");
	BreathSound.SetVolume(GlobalValue::FieldMonsterVolume);
}

void Dragon::IdleUpdate(float _Delta)
{

}

void Dragon::DownUpdate(float _Delta)
{
	if (0.0f >= Delay)
	{
		ChangeState(DragonState::Breath);
		Delay = DELAY_TIME;
	}

	if (Destination_YPos > Transform.GetWorldPosition().Y)
	{
		Transform.SetLocalPosition({ Transform.GetWorldPosition().X, Destination_YPos });
		Delay -= _Delta;
	}

	Transform.AddLocalPosition({0, -Speed * _Delta});
}

void Dragon::UpUpdate(float _Delta)
{
	Delay -= _Delta;
	if (0.0f >= Delay)
	{
		Transform.AddLocalPosition({ 0, Speed * _Delta });
	}

	if (200.0f <= Transform.GetWorldPosition().Y)
	{
		Transform.SetLocalPosition({ Transform.GetWorldPosition().X, 200.0f });
		ChangeState(DragonState::Idle);
	}
}

void Dragon::BreathUpdate(float _Delta)
{
	if (true == DragonRenderer->IsCurAnimationEnd())
	{
		ChangeState(DragonState::Up);
	}

	if (false == IsMoveBreath)
	{
		return;
	}

	if (-Breath_Min_Pos < Transform.GetWorldPosition().Y && Dir_Up == Breath_MoveDir)
	{
		Transform.SetLocalPosition({ Transform.GetWorldPosition().X, -Breath_Min_Pos });
		Breath_MoveDir = Dir_Down;
	}
	else if (-Breath_Max_Pos > Transform.GetWorldPosition().Y && Dir_Down == Breath_MoveDir)
	{
		Transform.SetLocalPosition({ Transform.GetWorldPosition().X, -Breath_Max_Pos });
		Breath_MoveDir = Dir_Up;
	}

	Transform.AddLocalPosition({ 0, Breath_MoveDir * BreathSpeed * _Delta });
}

void Dragon::IdleEnd()
{

}

void Dragon::DownEnd()
{

}

void Dragon::UpEnd()
{
	Delay = DELAY_TIME;
}

void Dragon::BreathEnd()
{
	DragonRenderer->SetPivotType(PivotType::Bottom);
	IsMoveBreath = false;
}

void Dragon::BreathOn()
{
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		BreathRenderers[i]->On();
	}
}

void Dragon::BreathOff()
{
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		BreathRenderers[i]->Off();
	}
}

void Dragon::RightBreath()
{
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		BreathRenderers[i]->Transform.SetLocalPosition({ 380 + 190 * static_cast<float>(i), -120, RenderDepth::monsterattack});
		BreathRenderers[i]->LeftFlip();
		BreathRenderers[i]->SetPivotValue({ 1.0f, 1.0f });
	}
}

void Dragon::LeftBreath()
{
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		BreathRenderers[i]->Transform.SetLocalPosition({ -380 - 190 * static_cast<float>(i), -120, RenderDepth::monsterattack });
		BreathRenderers[i]->RightFlip();
		BreathRenderers[i]->SetPivotValue({ 0.0f, 1.0f });
	}
}

void Dragon::SetBreathPos(const float4& _Pos)
{
	BreathCollision->Transform.SetLocalPosition(_Pos);
}