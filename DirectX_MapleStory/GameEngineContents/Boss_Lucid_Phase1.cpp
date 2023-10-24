﻿#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "Boss_Lucid_Phase1.h"
#include "PhantasmalWind.h"
#include "ContentLevel.h"
#include "Dragon.h"
#include "Lucid_Phase1.h"
#include "Player.h"
#include "MushRoom.h"
#include "Golem.h"

Boss_Lucid_Phase1::Boss_Lucid_Phase1()
{

}

Boss_Lucid_Phase1::~Boss_Lucid_Phase1()
{

}

void Boss_Lucid_Phase1::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseBossActor::LevelStart(_PrevLevel);
	SkillInfo.resize(5);
	SkillInfo[0] = { PhantasmalWind_Colldown , LucidState::PhantasmalWind };
	SkillInfo[1] = { Teleport_Cooldown , LucidState::TeleportSkill };
	SkillInfo[2] = { Summon_Dragon_Cooldown , LucidState::Summon_Dragon };
	SkillInfo[3] = { Summon_Mush_Cooldown , LucidState::Summon_Mush };
	SkillInfo[4] = { Summon_Golem_Cooldown , LucidState::Summon_Golem };

	PhantasmalWind::AllAngleValue = false;

	if (nullptr == FlowerRenderer)
	{
		FlowerRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MAP);
		FlowerRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::map });
		FlowerRenderer->AutoSpriteSizeOn();
	}

	if (nullptr == TeleportRenderer)
	{
		TeleportRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
		TeleportRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::monster });
		TeleportRenderer->AutoSpriteSizeOn();
	}

	if (nullptr == GameEngineSprite::Find("Lucid_Phase1_Death"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase1");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_Phase1_" + Childs.GetFileName(), Childs.GetStringPath());
		}

		if (nullptr == GameEngineSprite::Find("Lucid_Attack"))
		{
			Dir.MoveParentToExistsChild("Phase1");
			Dir.MoveChild("Attack");
			GameEngineSprite::CreateFolder("Lucid_" + Dir.GetFileName(), Dir.GetStringPath());
		}
	}

	BossRenderer->CreateAnimation("Idle", "Lucid_Phase1_Idle");
	BossRenderer->CreateAnimation("PhantasmalWind", "Lucid_Phase1_PhantasmalWind", 0.12f);
	BossRenderer->CreateAnimation("Summon_Dragon", "Lucid_Phase1_Summon_Dragon", 0.09f, -1, -1, false);
	BossRenderer->CreateAnimation("TeleportSkill", "Lucid_Phase1_TeleportSkill", 0.09f);
	BossRenderer->CreateAnimation("Skill4", "Lucid_Phase1_Skill4", 0.09f);
	BossRenderer->CreateAnimation("Death", "Lucid_Phase1_Death", 0.11f, -1, -1, false);
	IdleStart();

	FlowerRenderer->CreateAnimation("Flower", "Lucid_Phase1_Flower", 0.15f);
	FlowerRenderer->SetPivotType(PivotType::Bottom);
	FlowerRenderer->ChangeAnimation("Flower");
	FlowerRenderer->Transform.SetLocalPosition({ -5, 3, RenderDepth::map });

	TeleportRenderer->CreateAnimation("Teleport", "Lucid_Phase1_Teleport", 0.08f);
	TeleportRenderer->ChangeAnimation("Teleport");
	TeleportRenderer->SetPivotValue({ 0.5f, 0.8f });
	TeleportRenderer->Off();

	BossCollision->Transform.SetLocalScale({ 150, 400 });
	BossCollision->Transform.SetLocalPosition({ 0, 200 });

	// Render Event
	BossRenderer->SetFrameEvent("PhantasmalWind", 22, [&](GameEngineRenderer* _Renderer)
		{
			for (size_t i = 0; i < 4; i++)
			{
				std::shared_ptr<PhantasmalWind> Wind = ContentLevel::CurContentLevel->CreateActor<PhantasmalWind>(UpdateOrder::Monster);
				Wind->Transform.SetLocalPosition(Transform.GetWorldPosition() + float4{ 37, 321 });
			}
		}
	);

	BossRenderer->SetEndEvent("Summon_Dragon", [&](GameEngineRenderer* _Renderer)
		{
			Lucid_Phase1* Map = dynamic_cast<Lucid_Phase1*>(ContentLevel::CurContentLevel);
			Map->CallDragon();
		}
	);

	BossRenderer->SetFrameEvent("TeleportSkill", 11, [&](GameEngineRenderer* _Renderer)
		{
			GameEngineRandom Random;
			Random.SetSeed(time(nullptr));
			float RandomValue = Random.RandomFloat(400.0f, 1700.0f);
			Player::MainPlayer->Transform.SetLocalPosition({ RandomValue , -500 });
			TeleportRenderer->On();
			Player::MainPlayer->MoveVectorForceReset();
			float4 Pos = Player::MainPlayer->Transform.GetWorldPosition();
			Pos.Z = RenderDepth::monster;
			TeleportRenderer->Transform.SetWorldPosition(Pos);
		}
	);

	BossRenderer->SetFrameEvent("Skill4", 10, [&](GameEngineRenderer* _Renderer)
		{
			switch (State)
			{
			case LucidState::Summon_Mush:
			{
				std::shared_ptr<MushRoom> _Mush = ContentLevel::CurContentLevel->CreateActor<MushRoom>(UpdateOrder::Monster);
				_Mush->SetDir(ActorDir::Left);
				_Mush->Transform.SetLocalPosition(float4(850, -700));

				_Mush = ContentLevel::CurContentLevel->CreateActor<MushRoom>(UpdateOrder::Monster);
				_Mush->SetDir(ActorDir::Right);
				_Mush->Transform.SetLocalPosition(float4(1150, -700));
				break;
			}
			case LucidState::Summon_Golem:
			{
				GameEngineRandom Random;
				for (size_t i = 0; i < 2; i++)
				{
					std::shared_ptr<Golem> _Golem = ContentLevel::CurContentLevel->CreateActor<Golem>(UpdateOrder::Monster);
					_Golem->Init(1);
					Random.SetSeed(reinterpret_cast<long long>(_Golem.get()));
					float RandomValue = Random.RandomFloat(400.0f, 1700.0f);
					_Golem->Transform.SetLocalPosition({ RandomValue , -450 });
				}
				break;
			}
			default:
				break;
			}
		}
	);
	/////

	BossRenderer->SetEndEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			GameEngineCore::ChangeLevel("5.Lucid_Next");
		}
	);

	TeleportRenderer->SetEndEvent("Teleport", [&](GameEngineRenderer* _Renderer)
		{
			TeleportRenderer->Off();
		}
	);
}

void Boss_Lucid_Phase1::LevelEnd(GameEngineLevel* _NextLevel)
{
	BaseBossActor::LevelEnd(_NextLevel);
}

void Boss_Lucid_Phase1::Start()
{
	GameEngineInput::AddInputObject(this);

	BaseBossActor::Start();
}

void Boss_Lucid_Phase1::Update(float _Delta)
{
	BaseBossActor::Update(_Delta);
	StateUpdate(_Delta);

	// TestCode
	if (true == GameEngineInput::IsDown('5', this))
	{
		ChangeState(LucidState::PhantasmalWind);
	}

	if (true == GameEngineInput::IsDown('6', this))
	{
		ChangeState(LucidState::Summon_Dragon);
	}

	if (true == GameEngineInput::IsDown('7', this))
	{
		ChangeState(LucidState::TeleportSkill);
	}

	if (true == GameEngineInput::IsDown('8', this))
	{
		ChangeState(LucidState::Summon_Mush);
	}

	if (true == GameEngineInput::IsDown('9', this))
	{
		ChangeState(LucidState::Summon_Golem);
	}

	if (true == GameEngineInput::IsDown('0', this))
	{
		ChangeState(LucidState::Death);
	}
}

void Boss_Lucid_Phase1::Release()
{
	BaseBossActor::Release();
	if (nullptr != BossRenderer)
	{
		BossRenderer->Death();
		BossRenderer = nullptr;
	}

	if (nullptr != TeleportRenderer)
	{
		TeleportRenderer->Death();
		TeleportRenderer = nullptr;
	}
}

void Boss_Lucid_Phase1::ChangeState(LucidState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case LucidState::Idle:
			IdleEnd();
			break;
		case LucidState::Death:
			DeathEnd();
			break;
		case LucidState::PhantasmalWind:
			PhantasmalWindEnd();
			break;
		case LucidState::Summon_Dragon:
			Summon_DragonEnd();
			break;
		case LucidState::TeleportSkill:
			TeleportSkillEnd();
			break;
		case LucidState::Summon_Mush:
			Summon_MushEnd();
			break;
		case LucidState::Summon_Golem:
			Summon_GolemEnd();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 변경하려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case LucidState::Idle:
			IdleStart();
			break;
		case LucidState::Death:
			DeathStart();
			break;
		case LucidState::PhantasmalWind:
			PhantasmalWindStart();
			break;
		case LucidState::Summon_Dragon:
			Summon_DragonStart();
			break;
		case LucidState::TeleportSkill:
			TeleportSkillStart();
			break;
		case LucidState::Summon_Mush:
			Summon_MushStart();
			break;
		case LucidState::Summon_Golem:
			Summon_GolemStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Boss_Lucid_Phase1::StateUpdate(float _Delta)
{
	switch (State)
	{
	case LucidState::Idle:
		return IdleUpdate(_Delta);
	case LucidState::Death:
		return DeathUpdate(_Delta);
	case LucidState::PhantasmalWind:
		return PhantasmalWindUpdate(_Delta);
	case LucidState::Summon_Dragon:
		return Summon_DragonUpdate(_Delta);
	case LucidState::TeleportSkill:
		return TeleportSkillUpdate(_Delta);
	case LucidState::Summon_Mush:
		return Summon_MushUpdate(_Delta);
	case LucidState::Summon_Golem:
		return Summon_GolemUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}


void Boss_Lucid_Phase1::IdleStart()
{
	BossRenderer->SetPivotType(PivotType::Center);
	BossRenderer->Transform.SetLocalPosition({ 37, 321, RenderDepth::monster });
	BossRenderer->ChangeAnimation("Idle");
	FlowerRenderer->On();
}

void Boss_Lucid_Phase1::DeathStart()
{
	BossRenderer->SetPivotType(PivotType::Bottom);
	BossRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::monster});
	BossRenderer->ChangeAnimation("Death");
	FlowerRenderer->Off();
}

void Boss_Lucid_Phase1::PhantasmalWindStart()
{
	BossRenderer->SetPivotValue({ 0.433f, 0.677f });
	BossRenderer->ChangeAnimation("PhantasmalWind");
}

void Boss_Lucid_Phase1::Summon_DragonStart()
{
	BossRenderer->SetPivotValue({ 0.274f, 0.706f });
	BossRenderer->ChangeAnimation("Summon_Dragon");
}

void Boss_Lucid_Phase1::TeleportSkillStart()
{
	BossRenderer->SetPivotValue({ 0.215f, 0.648f });
	BossRenderer->ChangeAnimation("TeleportSkill");
}

void Boss_Lucid_Phase1::Summon_MushStart()
{
	BossRenderer->SetPivotValue({ 0.452f, 0.444f });
	BossRenderer->ChangeAnimation("Skill4");
}

void Boss_Lucid_Phase1::Summon_GolemStart()
{
	BossRenderer->SetPivotValue({ 0.452f, 0.444f });
	BossRenderer->ChangeAnimation("Skill4");
}


void Boss_Lucid_Phase1::IdleUpdate(float _Delta)
{
	for (size_t i = 0; i < SkillInfo.size(); i++)
	{
		SkillInfo[i].SkillCooldown -= _Delta;

		if (0.0f >= SkillInfo[i].SkillCooldown)
		{
			ChangeState(SkillInfo[i].SkillState);
			SkillInfo[i].SkillCooldown = SkillInfo[i].SkillCooldownValue;
			return;
		}
	}
}

void Boss_Lucid_Phase1::DeathUpdate(float _Delta)
{
	
}

void Boss_Lucid_Phase1::PhantasmalWindUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase1::Summon_DragonUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase1::TeleportSkillUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase1::Summon_MushUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase1::Summon_GolemUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase1::IdleEnd()
{

}

void Boss_Lucid_Phase1::DeathEnd()
{
	BossRenderer->Transform.SetLocalPosition({ 37, 321, RenderDepth::monster });
	FlowerRenderer->On();
}

void Boss_Lucid_Phase1::PhantasmalWindEnd()
{

}

void Boss_Lucid_Phase1::Summon_DragonEnd()
{

}

void Boss_Lucid_Phase1::TeleportSkillEnd()
{

}

void Boss_Lucid_Phase1::Summon_MushEnd()
{

}

void Boss_Lucid_Phase1::Summon_GolemEnd()
{

}