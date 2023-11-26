#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "Boss_Lucid_Phase2.h"
#include "PhantasmalWind.h"
#include "ContentLevel.h"
#include "Lucid_Phase2.h"
#include "Lucid_BodySlam.h"
#include "ButterFly.h"
#include "BossHpBar.h"
#include "FadeObject.h"
#include "Player.h"
#include "ReleaseFunction.h"

void Lucid_Phase2_GUI::Start()
{

}

void Lucid_Phase2_GUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (false == IsGUIUpdate)
	{
		return;
	}

	float Button_XSizze = 125.0f;
	float Button_YSizze = 20.0f;
	ImGui::Checkbox("BossCoolDown", &_CurBoss->IsCoolDownUpdate);

	if (ImGui::Button("Idle", { Button_XSizze, Button_YSizze }))
	{
		_CurBoss->ChangeState(LucidState::Idle);
	}

	if (ImGui::Button("PhantasmalWind", { Button_XSizze, Button_YSizze }))
	{
		_CurBoss->ChangeState(LucidState::PhantasmalWind);
	}

	if (ImGui::Button("Laser", { Button_XSizze, Button_YSizze }))
	{
		_CurBoss->ChangeState(LucidState::Laser);
	}

	if (ImGui::Button("BodySlam", { Button_XSizze, Button_YSizze }))
	{
		_CurBoss->ChangeState(LucidState::BodySlam);
	}

	if (ImGui::Button("Summon_Dragon", { Button_XSizze, Button_YSizze }))
	{
		_CurBoss->ChangeState(LucidState::Summon_Dragon);
	}

	if (ImGui::Button("Summon_Golem", { Button_XSizze, Button_YSizze }))
	{
		Lucid_Phase2* _BossLevel = dynamic_cast<Lucid_Phase2*>(ContentLevel::CurContentLevel);
		if (nullptr == _BossLevel)
		{
			MsgBoxAssert("잘못된 레벨에서 GUI를 사용하였습니다.");
			return;
		}

		_BossLevel->SummonGolem(1);
	}

	if (ImGui::Button("Summon_ButterFly", { Button_XSizze, Button_YSizze }))
	{
		_CurBoss->ChangeState(LucidState::Summon_ButterFly);
	}

	if (ImGui::Button("Death", { Button_XSizze, Button_YSizze }))
	{
		_CurBoss->ChangeState(LucidState::Death);
	}
}

Boss_Lucid_Phase2::Boss_Lucid_Phase2()
{

}

Boss_Lucid_Phase2::~Boss_Lucid_Phase2()
{

}

void Boss_Lucid_Phase2::LevelStart(GameEngineLevel* _PrevLevel)
{
	IsCoolDownUpdate = true;

	BossGui = GameEngineGUI::CreateGUIWindow<Lucid_Phase2_GUI>("LucidState");
	BossGui->_CurBoss = this;

	BaseBossActor::LevelStart(_PrevLevel);

	GameEngineRandom Random;
	Random.SetSeed(time(nullptr));
	CurLocationIndex = Random.RandomInt(0, 10);

	PhantasmalWind::AllAngleValue = true;
	// Skill Cooldown
	SkillInfo.resize(5);

	SkillInfo[0] = { PhantasmalWind_Cooldown, LucidState::PhantasmalWind };
	SkillInfo[1] = { Laser_Pattern_Cooldown, LucidState::Laser };
	SkillInfo[2] = { BodySlam_Pattern_Cooldown, LucidState::BodySlam };
	SkillInfo[3] = { Summon_Dragon_Cooldown, LucidState::Summon_Dragon };
	SkillInfo[4] = { Summon_Fly_Cooldown, LucidState::Summon_ButterFly };
	SkillInfo[4].SkillCooldown = 0.0f;

	// Move Location
	MoveLocation.resize(11);
	LocationNumber.reserve(10);
	MoveLocation[0] = { 1170, -585 };
	MoveLocation[1] = { 785, -885 };
	MoveLocation[2] = { 1400, -885 };
	MoveLocation[3] = { 1210, -554 };
	MoveLocation[4] = { 840, -1005 };
	MoveLocation[5] = { 1400, -1085 };
	MoveLocation[6] = { 1450, -685 };
	MoveLocation[7] = { 900, -785 };
	MoveLocation[8] = { 1390, -1035 };
	MoveLocation[9] = { 770, -665 };
	MoveLocation[10] = { 1170, -865 };

	if (nullptr == GameEngineSprite::Find("Lucid_Phase2_Death"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase2");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_Phase2_" + Childs.GetFileName(), Childs.GetStringPath());
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

	// BodySlam Resources
	if (nullptr == GameEngineSprite::Find("Lucid_BodySlam_Ready"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase2_BodySlam");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_BodySlam_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	if (nullptr == GameEngineSprite::Find("Phase2_ButterFly_Ready"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase2_ButterFly\\ButterFly");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Phase2_ButterFly_" + Childs.GetFileName(), Childs.GetStringPath());
		}

		Dir.MoveParent();
		Dir.MoveChild("ButterFly_Ball");
		Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Phase2_ButterFly_Ball_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	// 2 Phase Sound
	if (nullptr == GameEngineSound::FindSound("RushPrepare.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Boss\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "RushPrepare.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "RushEnd.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "LaserPattern.mp3");
		// GameEngineSound::SoundLoad(FilePath.GetStringPath() + "Phase2_Death.mp3");
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

	BossRenderer->CreateAnimation("Idle", "Lucid_Phase2_Idle");
	BossRenderer->CreateAnimation("Death", "Lucid_Phase2_Death", 0.1f, -1, -1, false);
	BossRenderer->CreateAnimation("PhantasmalWind", "Lucid_Phase2_PhantasmalWind", 0.12f);
	BossRenderer->CreateAnimation("Summon_Dragon", "Lucid_Phase2_Summon_Dragon");
	BossRenderer->CreateAnimation("Laser", "Lucid_Phase2_Laser", 0.09f, -1, -1, false);
	BossRenderer->CreateAnimation("BodySlam", "Lucid_Phase2_BodySlam");
	BossRenderer->CreateAnimation("Summon", "Lucid_Phase2_Summon");
	BossRenderer->ChangeAnimation("Idle");
	IdleStart();

	BossCollision->Transform.SetLocalScale({ 70, 130 });
	BossCollision->Transform.SetLocalPosition({ -5, 60 });

	// Renderer Event
	BossRenderer->SetFrameEvent("PhantasmalWind", 22, [&](GameEngineRenderer* _Renderer)
		{
			for (size_t i = 0; i < 8; i++)
			{
				std::shared_ptr<PhantasmalWind> Wind = ContentLevel::CurContentLevel->CreateActor<PhantasmalWind>(UpdateOrder::Monster);
				Wind->Transform.SetLocalPosition(Transform.GetWorldPosition() + float4{ 0, 50 });
				Wind->SetSpeed(200.0f);
			}
		}
	);

	// Laser Render Event
	BossRenderer->SetFrameEvent("Laser", 10, [&](GameEngineRenderer* _Renderer)
		{
			BossPlayer = GameEngineSound::SoundPlay("LaserPattern.mp3");
		}
	);

	BossRenderer->SetFrameEvent("Laser", 16, [&](GameEngineRenderer* _Renderer)
		{
			BossCollision->Off();
		}
	);

	BossRenderer->SetFrameEvent("Laser", 32, [&](GameEngineRenderer* _Renderer)
		{
			Lucid_Phase2* Map = dynamic_cast<Lucid_Phase2*>(ContentLevel::CurContentLevel);
			Map->LucidLaserOff();
		}
	);

	BossRenderer->SetFrameEvent("Laser", 37, [&](GameEngineRenderer* _Renderer)
		{
			BossCollision->On();
		}
	);
	//

	// BodySlam Render Evnet
	BossRenderer->SetFrameEvent("BodySlam", 3, [&](GameEngineRenderer* _Renderer)
		{
			BossCollision->Off();
		}
	);

	BossRenderer->SetFrameEvent("BodySlam", 14, [&](GameEngineRenderer* _Renderer)
		{
			ContentLevel::CurContentLevel->CreateActor<Lucid_BodySlam>(UpdateOrder::Monster);
		}
	);

	BossRenderer->SetFrameEvent("BodySlam", 16, [&](GameEngineRenderer* _Renderer)
		{
			BossPlayer = GameEngineSound::SoundPlay("RushEnd.mp3");
		}
	);

	BossRenderer->SetFrameEvent("BodySlam", 25, [&](GameEngineRenderer* _Renderer)
		{
			BossCollision->On();
		}
	);
	//

	BossRenderer->SetEndEvent("Summon_Dragon", [&](GameEngineRenderer* _Renderer)
		{
			Lucid_Phase2* Map = dynamic_cast<Lucid_Phase2*>(ContentLevel::CurContentLevel);
			Map->CallDragon();
		}
	);

	BossRenderer->SetFrameEvent("Summon", 7, [&](GameEngineRenderer* _Renderer)
		{
			switch (State)
			{
			case LucidState::Summon_ButterFly:
			{
				for (int i = 0; i < 3; i++)
				{
					std::shared_ptr<ButterFly> _CurButterFly = ContentLevel::CurContentLevel->CreateActor<ButterFly>(UpdateOrder::Monster);
					_CurButterFly->Init(ButterFly_Phase::Phase2);

					float4 CurBossPos = Transform.GetWorldPosition();
					Random.SetSeed(reinterpret_cast<long long>(_CurButterFly.get()));
					float4 RandomFloat4 = Random.RandomVectorBox2D(-300.0f, 300.0f, -300.0f, 300.0f);
					_CurButterFly->Transform.SetLocalPosition({ CurBossPos + RandomFloat4 });
				}
				break;
			}
			default:
				break;
			}
		}
	);

	BossRenderer->SetEndEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			BossGui->IsGUIUpdate = false;
			ContentLevel::CurContentLevel->FadeOutObject->FadeStart();
		}
	);

	/// Animation Detail
	std::shared_ptr<GameEngineFrameAnimation> _Animation = BossRenderer->FindAnimation("Laser");
	_Animation->Inter[30] = 15.0f;

	_Animation = BossRenderer->FindAnimation("BodySlam");
	_Animation->Inter[14] = 13.0f;

	std::shared_ptr<BossHpBar> _HpBar = GetLevel()->CreateActor<BossHpBar>(UpdateOrder::UI);
	_HpBar->LinkBossHP(&HP);
}

void Boss_Lucid_Phase2::LevelEnd(GameEngineLevel* _NextLevel)
{
	BaseBossActor::LevelEnd(_NextLevel);
	BossGui->IsGUIUpdate = true;
	GameEngineGUI::DeathGUIWindows("LucidState");
}

void Boss_Lucid_Phase2::Start()
{
	DamageSkinPivot = { 0, 170 };
	GameEngineInput::AddInputObject(this);

	BaseBossActor::Start();
}

void Boss_Lucid_Phase2::Update(float _Delta)
{
	if (0 >= HP)
	{
		ChangeState(LucidState::Death);
	}

	BaseBossActor::Update(_Delta);
	StateUpdate(_Delta);
}

void Boss_Lucid_Phase2::Release()
{
	BaseBossActor::Release();

	if (nullptr != BossGui)
	{
		BossGui = nullptr;
	}

	if (nullptr != GameEngineSprite::Find("Lucid_Phase2_Death"))
	{
		ReleaseFunction::FolderRelease("Lucid_Phase2_Death", "Lucid_Phase2_Death_");
		ReleaseFunction::FolderRelease("Lucid_Phase2_BodySlam", "Lucid_Phase2_BodySlam_");
		ReleaseFunction::FolderRelease("Lucid_Phase2_Idle", "Lucid_Phase2_Idle_");
		ReleaseFunction::FolderRelease("Lucid_Phase2_PhantasmalWind", "Lucid_Phase2_PhantasmalWind_");
		ReleaseFunction::FolderRelease("Lucid_Phase2_Summon", "Lucid_Phase2_Summon_");
		ReleaseFunction::FolderRelease("Lucid_Phase2_Summon_Dragon", "Lucid_Phase2_Summon_Dragon_");
		ReleaseFunction::FolderRelease("Lucid_Phase2_Laser", "Lucid_Phase2_Laser_");
	}
}

void Boss_Lucid_Phase2::ChangeState(LucidState _State)
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
		case LucidState::Laser:
			LaserEnd();
			break;
		case LucidState::BodySlam:
			BodySlamEnd();
			break;
		case LucidState::Summon_Dragon:
			Summon_DragonEnd();
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
		case LucidState::Laser:
			LaserStart();
			break;
		case LucidState::BodySlam:
			BodySlamStart();
			break;
		case LucidState::Summon_Dragon:
			Summon_DragonStart();
			break;
		case LucidState::Summon_ButterFly:
			Summon_ButterFlyStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Boss_Lucid_Phase2::StateUpdate(float _Delta)
{
	switch (State)
	{
	case LucidState::Idle:
		return IdleUpdate(_Delta);
	case LucidState::Death:
		return DeathUpdate(_Delta);
	case LucidState::PhantasmalWind:
		return PhantasmalWindUpdate(_Delta);
	case LucidState::Laser:
		return LaserUpdate(_Delta);
	case LucidState::BodySlam:
		return BodySlamUpdate(_Delta);
	case LucidState::Summon_Dragon:
		return Summon_DragonUpdate(_Delta);
	case LucidState::Summon_ButterFly:
		return Summon_ButterFlyUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

///// Start

void Boss_Lucid_Phase2::IdleStart()
{
	BossRenderer->ChangeAnimation("Idle");

	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.33f, 0.63f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.67f, 0.63f });
		BossRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void Boss_Lucid_Phase2::DeathStart()
{
	BossRenderer->ChangeAnimation("Death");
	BossCollision->Off();
	Player::MainPlayer->InvincibilityOn();

	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.463f, 0.62f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.537f, 0.62f });
		BossRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	// BossPlayer = GameEngineSound::SoundPlay("Phase2_Death.mp3");
}

void Boss_Lucid_Phase2::PhantasmalWindStart()
{
	BossRenderer->ChangeAnimation("PhantasmalWind");
	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.47f, 0.68f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.53f, 0.68f });
		BossRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	BossPlayer = GameEngineSound::SoundPlay("PhantasmalWind.mp3");
}

void Boss_Lucid_Phase2::LaserStart()
{
	BossRenderer->ChangeAnimation("Laser");
	Lucid_Phase2* Map = dynamic_cast<Lucid_Phase2*>(ContentLevel::CurContentLevel);
	Map->LucidLaserOn();

	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.483f, 0.75f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.517f, 0.75f });
		BossRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	BossWarningMent->SetWarningMent("루시드가 강력한 공격을 사용하려 합니다!");
}

void Boss_Lucid_Phase2::BodySlamStart()
{
	BossRenderer->ChangeAnimation("BodySlam");

	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.375f, 0.566f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.625f, 0.566f });
		BossRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	BossWarningMent->SetWarningMent("루시드가 강력한 공격을 사용하려 합니다!");
	BossPlayer = GameEngineSound::SoundPlay("RushPrepare.mp3");
}

void Boss_Lucid_Phase2::Summon_DragonStart()
{
	BossRenderer->ChangeAnimation("Summon_Dragon");

	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.595f, 0.758f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.405f, 0.758f });
		BossRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	BossWarningMent->SetWarningMent("루시드가 강력한 소환수를 소환했습니다!");

	BossPlayer = GameEngineSound::SoundPlay("CallDragon.mp3");
}

void Boss_Lucid_Phase2::Summon_ButterFlyStart()
{
	BossRenderer->ChangeAnimation("Summon");
	BossRenderer->SetPivotValue({ 0.5f, 0.635f });
	BossPlayer = GameEngineSound::SoundPlay("Summon.mp3");
	BossPlayer.SetVolume(0.5f);
}

///// Update

void Boss_Lucid_Phase2::IdleUpdate(float _Delta)
{
	// Skill Cooldown
	for (size_t i = 0; i < SkillInfo.size(); i++)
	{
		if (false == IsCoolDownUpdate)
		{
			continue;
		}
		SkillInfo[i].SkillCooldown -= _Delta;

		if (0.0f >= SkillInfo[i].SkillCooldown)
		{
			ChangeState(SkillInfo[i].SkillState);
			SkillInfo[i].SkillCooldown = SkillInfo[i].SkillCooldownValue;
			return;
		}
	}

	// Move
	MoveDelay -= _Delta;
	if (0.0f < MoveDelay)
	{
		return;
	}

	if (Max_MoveSpeed > MoveSpeed)
	{
		MoveSpeed += Accel_MoveSpeed * _Delta;
	}
	else if (Max_MoveSpeed <= MoveSpeed)
	{
		MoveSpeed = Max_MoveSpeed;
	}

	float4 CurPos = Transform.GetLocalPosition();
	float4 DestinationPos = MoveLocation[CurLocationIndex];
	MoveVector = DestinationPos - CurPos;
	Transform.AddLocalPosition(MoveVector.NormalizeReturn() * MoveSpeed * _Delta);

	if (0.0f >= MoveVector.X && Dir == ActorDir::Right)
	{
		Dir = ActorDir::Left;
		BossRenderer->RightFlip();
		BossRenderer->SetPivotValue({ 0.67f, 0.63f });
	}
	else if (0.0f < MoveVector.X && Dir == ActorDir::Left)
	{
		Dir = ActorDir::Right;
		BossRenderer->LeftFlip();
		BossRenderer->SetPivotValue({ 0.33f, 0.63f });
	}

	if (5.0f >= MoveVector.Size())
	{
		LocationNumber.clear();
		Transform.SetLocalPosition(DestinationPos);
		MoveDelay = Move_Delay_Value;

		for (int i = 0; i < LocationNumber.capacity(); i++)
		{
			if (CurLocationIndex == i)
			{
				continue;
			}
			LocationNumber.push_back(i);
		}

		GameEngineRandom Random;
		Random.SetSeed(reinterpret_cast<long long>(this) + time(nullptr) + CurLocationIndex);
		int RandomInt = Random.RandomInt(0, static_cast<int>(LocationNumber.size() - 1));

		CurLocationIndex = LocationNumber[RandomInt];
		MoveSpeed = Default_MoveSpeed;
	}
}

void Boss_Lucid_Phase2::DeathUpdate(float _Delta)
{

}

void Boss_Lucid_Phase2::PhantasmalWindUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase2::LaserUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase2::BodySlamUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase2::Summon_DragonUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase2::Summon_ButterFlyUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}


///// End

void Boss_Lucid_Phase2::IdleEnd()
{

}
void Boss_Lucid_Phase2::DeathEnd()
{
}

void Boss_Lucid_Phase2::PhantasmalWindEnd()
{

}

void Boss_Lucid_Phase2::LaserEnd()
{

}

void Boss_Lucid_Phase2::BodySlamEnd()
{

}

void Boss_Lucid_Phase2::Summon_DragonEnd()
{

}

void Boss_Lucid_Phase2::Summon_ButterFlyEnd()
{

}
