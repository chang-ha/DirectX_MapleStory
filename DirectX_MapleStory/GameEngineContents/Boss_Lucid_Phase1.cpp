#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "Boss_Lucid_Phase1.h"
#include "PhantasmalWind.h"
#include "ContentLevel.h"
#include "Dragon.h"
#include "Lucid_Phase1.h"
#include "Player.h"
#include "MushRoom.h"
#include "Golem.h"
#include "ButterFly.h"
#include "BossHpBar.h"
#include "FadeObject.h"
#include "ReleaseFunction.h"

Boss_Lucid_Phase1::Boss_Lucid_Phase1()
{

}

Boss_Lucid_Phase1::~Boss_Lucid_Phase1()
{

}

void Boss_Lucid_Phase1::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseBossActor::LevelStart(_PrevLevel);
	SkillInfo.resize(6);
	SkillInfo[0] = { PhantasmalWind_Cooldown , LucidState::PhantasmalWind };
	SkillInfo[1] = { Teleport_Cooldown , LucidState::TeleportSkill };
	SkillInfo[2] = { Summon_Dragon_Cooldown , LucidState::Summon_Dragon };
	SkillInfo[3] = { Summon_Mush_Cooldown , LucidState::Summon_Mush };
	SkillInfo[4] = { Summon_Golem_Cooldown , LucidState::Summon_Golem };
	SkillInfo[5] = { Summon_Fly_Cooldown , LucidState::Summon_ButterFly };
	SkillInfo[5].SkillCooldown = 0.0f;

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
	}

	if (nullptr == GameEngineSprite::Find("PhantasmalWind"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\PhantasmalWind");
		GameEngineSprite::CreateFolder("PhantasmalWind", Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("PhantasmalWind_Hit"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\PhantasmalWind_Hit");
		GameEngineSprite::CreateFolder("PhantasmalWind_Hit", Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("Phase1_ButterFly_Ready"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase1_ButterFly\\ButterFly");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Phase1_ButterFly_" + Childs.GetFileName(), Childs.GetStringPath());
		}

		Dir.MoveParent();
		Dir.MoveChild("ButterFly_Ball");
		Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Phase1_ButterFly_Ball_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	// 1 Phase Sound
	if (nullptr == GameEngineSound::FindSound("Phase1_Death.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Boss\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "Phase1_Death.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "Teleport.mp3");
	}
	
	// 1 & 2 Phase Common Sound
	if (nullptr == GameEngineSound::FindSound("PhantasmalWind.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Boss\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "PhantasmalWind.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "CallDragon.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "Summon.mp3");
	}

	BossRenderer->CreateAnimation("Idle", "Lucid_Phase1_Idle");
	BossRenderer->CreateAnimation("PhantasmalWind", "Lucid_Phase1_PhantasmalWind", 0.12f);
	BossRenderer->CreateAnimation("Summon_Dragon", "Lucid_Phase1_Summon_Dragon", 0.09f, -1, -1, false);
	BossRenderer->CreateAnimation("TeleportSkill", "Lucid_Phase1_TeleportSkill", 0.09f);
	BossRenderer->CreateAnimation("Summon", "Lucid_Phase1_Summon", 0.09f);
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

	BossRenderer->SetFrameEvent("Summon", 10, [&](GameEngineRenderer* _Renderer)
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
					_Golem->Init(Golem_Phase::Phase1);
					Random.SetSeed(reinterpret_cast<long long>(_Golem.get()));
					float RandomValue = Random.RandomFloat(400.0f, 1700.0f);
					_Golem->Transform.SetLocalPosition({ RandomValue , -450 });
				}
				break;
			}
			case LucidState::Summon_ButterFly:
			{
				GameEngineRandom Random;
				for (int i = 0; i < 3; i++)
				{
					std::shared_ptr<ButterFly> _CurButterFly = ContentLevel::CurContentLevel->CreateActor<ButterFly>(UpdateOrder::Monster);
					_CurButterFly->Init(ButterFly_Phase::Phase1);
					Random.SetSeed(reinterpret_cast<long long>(_CurButterFly.get()));
					float RandomValue = Random.RandomFloat(400.0f, 1700.0f);
					_CurButterFly->Transform.SetLocalPosition({ RandomValue , -650 });
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
			ContentLevel::CurContentLevel->FadeOutObject->FadeStart();
		}
	);

	TeleportRenderer->SetEndEvent("Teleport", [&](GameEngineRenderer* _Renderer)
		{
			TeleportRenderer->Off();
		}
	);

	std::shared_ptr<BossHpBar> _HpBar = GetLevel()->CreateActor<BossHpBar>(UpdateOrder::UI);
	_HpBar->LinkBossHP(&HP);
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

	if (0 >= HP)
	{
		ChangeState(LucidState::Death);
	}

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
		ChangeState(LucidState::Summon_ButterFly);
	}

	if (true == GameEngineInput::IsDown('0', this))
	{
		ChangeState(LucidState::Death);
	}
}

void Boss_Lucid_Phase1::Release()
{
	BaseBossActor::Release();
	if (nullptr != FlowerRenderer)
	{
		FlowerRenderer->Death();
		FlowerRenderer = nullptr;
	}

	if (nullptr != TeleportRenderer)
	{
		TeleportRenderer->Death();
		TeleportRenderer = nullptr;
	}

	if (nullptr != GameEngineSprite::Find("Lucid_Phase1_Death"))
	{
		ReleaseFunction::FolderRelease("Lucid_Phase1_Death", "Lucid_Phase1_Death_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Flower", "Lucid_Phase1_Flower_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Idle", "Lucid_Phase1_Idle_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_PhantasmalWind", "Lucid_Phase1_PhantasmalWind_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Summon", "Lucid_Phase1_Summon_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Summon_Dragon", "Lucid_Phase1_Summon_Dragon_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Teleport", "Lucid_Phase1_Teleport_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_TeleportSkill", "Lucid_Phase1_TeleportSkill_");
	}

	if (nullptr != GameEngineSprite::Find("Lucid_Phase1_Golem_Ready"))
	{
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_Ready", "Phase1_Golem_Ready_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_Attack", "Phase1_Golem_Attack_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_Death", "Phase1_Golem_Death_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_Idle", "Phase1_Golem_Idle_");
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_Revive", "Phase1_Golem_Revive_");
	}

	if (nullptr != GameEngineSprite::Find("Lucid_Phase1_Golem_TakeDown_Hit"))
	{
		ReleaseFunction::FolderRelease("Lucid_Phase1_Golem_TakeDown_Hit", "TakeDown_Hit_");
	}

	if (nullptr != GameEngineSprite::Find("Phase1_ButterFly_Ready"))
	{
		ReleaseFunction::FolderRelease("Phase1_ButterFly_Ready", "Phase1_ButterFly_Ready_");
		ReleaseFunction::FolderRelease("Phase1_ButterFly_Attack", "Phase1_ButterFly_Attack_");
		ReleaseFunction::FolderRelease("Phase1_ButterFly_Move", "Phase1_ButterFly_Move_");
		ReleaseFunction::FolderRelease("Phase1_ButterFly_Death", "Phase1_ButterFly_Death_");

		ReleaseFunction::FolderRelease("Phase1_ButterFly_Ball_Ball", "Phase1_ButterFly_Ball_Ball_");
		ReleaseFunction::FolderRelease("Phase1_ButterFly_Ball_Hit", "Phase1_ButterFly_Ball_Hit_");
	}

	if (nullptr != GameEngineSprite::Find("PhantasmalWind"))
	{
		ReleaseFunction::FolderRelease("PhantasmalWind", "PhantasmalWind_");
		ReleaseFunction::FolderRelease("PhantasmalWind_Hit", "PhantasmalWind_Hit_");
	}

	if (nullptr != GameEngineSprite::Find("WarningMent_Start.png"))
	{
		GameEngineTexture::Release("WarningMent_Start.png");
		GameEngineSprite::Release("WarningMent_Start.png");

		GameEngineTexture::Release("WarningMent_Middle.png");
		GameEngineSprite::Release("WarningMent_Middle.png");

		GameEngineTexture::Release("WarningMent_End.png");
		GameEngineSprite::Release("WarningMent_End.png");
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
		case LucidState::Summon_ButterFly:
			Summon_ButterFlyEnd();
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
		case LucidState::Summon_ButterFly:
			Summon_ButterFlyStart();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값을 시작하려고 했습니다.");
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
	case LucidState::Summon_ButterFly:
		return Summon_ButterFlyUpdate(_Delta);
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
	BossCollision->Off();
	Player::MainPlayer->InvincibilityOn();
	BossPlayer = GameEngineSound::SoundPlay("Phase1_Death.mp3");
}

void Boss_Lucid_Phase1::PhantasmalWindStart()
{
	BossRenderer->SetPivotValue({ 0.433f, 0.677f });
	BossRenderer->ChangeAnimation("PhantasmalWind");
	if (false == OnceWarning)
	{
		BossWarningMent->SetWarningMent("저 바람을 맞으면 꿈이 더 강해질 겁니다!");
		OnceWarning = true;
	}

	BossPlayer = GameEngineSound::SoundPlay("PhantasmalWind.mp3");
}

void Boss_Lucid_Phase1::Summon_DragonStart()
{
	BossRenderer->SetPivotValue({ 0.274f, 0.706f });
	BossRenderer->ChangeAnimation("Summon_Dragon");
	BossWarningMent->SetWarningMent("루시드가 강력한 소환수를 소환했습니다!");

	BossPlayer = GameEngineSound::SoundPlay("CallDragon.mp3");
}

void Boss_Lucid_Phase1::TeleportSkillStart()
{
	BossRenderer->SetPivotValue({ 0.215f, 0.648f });
	BossRenderer->ChangeAnimation("TeleportSkill");
	BossPlayer = GameEngineSound::SoundPlay("Teleport.mp3");
}

void Boss_Lucid_Phase1::Summon_MushStart()
{
	BossRenderer->SetPivotValue({ 0.452f, 0.444f });
	BossRenderer->ChangeAnimation("Summon");
	BossPlayer = GameEngineSound::SoundPlay("Summon.mp3");
}

void Boss_Lucid_Phase1::Summon_GolemStart()
{
	BossRenderer->SetPivotValue({ 0.452f, 0.444f });
	BossRenderer->ChangeAnimation("Summon");
	BossPlayer = GameEngineSound::SoundPlay("Summon.mp3");
}

void Boss_Lucid_Phase1::Summon_ButterFlyStart()
{
	BossRenderer->SetPivotValue({ 0.452f, 0.444f });
	BossRenderer->ChangeAnimation("Summon");
	BossPlayer = GameEngineSound::SoundPlay("Summon.mp3");
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

void Boss_Lucid_Phase1::Summon_ButterFlyUpdate(float _Delta)
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

void Boss_Lucid_Phase1::Summon_ButterFlyEnd()
{

}
