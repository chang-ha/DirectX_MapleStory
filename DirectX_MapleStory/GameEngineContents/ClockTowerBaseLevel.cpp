#include "PreCompile.h"
#include "ClockTowerBaseLevel.h"
#include "ContentBackGround.h"
#include "SkillManager.h"
#include "ContentMap.h"
#include "Player.h"
#include "FieldMonster.h"
#include "TowerWall.h"
#include "Lamp.h"
#include "FireWork.h"

ClockTowerBaseLevel::ClockTowerBaseLevel()
{

}

ClockTowerBaseLevel::~ClockTowerBaseLevel()
{

}

void ClockTowerBaseLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	if (nullptr == GameEngineSound::FindSound("ClockTowerofNightMare.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BGM\\ClockTowerofNightMare.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
	}

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Next.png");
	}

	std::shared_ptr<Lamp> _Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp7);
	_Lamp->Transform.SetLocalPosition({ 600, -64 });

	_Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp7);
	_Lamp->Transform.SetLocalPosition({ 1172, -64 });

	_Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp7);
	_Lamp->Transform.SetLocalPosition({ 600, -684 });

	_Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp7);
	_Lamp->Transform.SetLocalPosition({ 1172, -684 });

	_Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp7);
	_Lamp->Transform.SetLocalPosition({ 600, -1304 });

	_Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp7);
	_Lamp->Transform.SetLocalPosition({ 1172, -1304 });

	_Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp7);
	_Lamp->Transform.SetLocalPosition({ 600, -1919 });

	_Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp7);
	_Lamp->Transform.SetLocalPosition({ 1172, -1919 });

	_Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp7);
	_Lamp->Transform.SetLocalPosition({ 600, -2539 });

	_Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp7);
	_Lamp->Transform.SetLocalPosition({ 1172, -2539 });

	std::shared_ptr<FireWork> _FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({ 1700, -250 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork3);
	_FireWork->Transform.SetLocalPosition({ 800, -250 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({ 900, -950 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork2);
	_FireWork->Transform.SetLocalPosition({ 170, -700 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork3);
	_FireWork->Transform.SetLocalPosition({ 150, -1050 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork2);
	_FireWork->Transform.SetLocalPosition({ 70, -1650 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork2);
	_FireWork->Transform.SetLocalPosition({ 120, -2150 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork1);
	_FireWork->Transform.SetLocalPosition({ 50, -2000 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({ 90, -2550 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork3);
	_FireWork->Transform.SetLocalPosition({ 900, -2200 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork3);
	_FireWork->Transform.SetLocalPosition({ 1750, -2100 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({ 1680, -2000 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork1);
	_FireWork->Transform.SetLocalPosition({ 1780, -1880 });

	LeftWall = CreateActor<TowerWall>(UpdateOrder::Map);
	LeftWall->Transform.SetLocalPosition({290, 3});
	LeftWall->WallRenderer->LeftFlip();
	RightWall = CreateActor<TowerWall>(UpdateOrder::Map);
	RightWall->Transform.SetLocalPosition({ 1593, 3 });

	if (false == BGMPlayer.IsPlaying())
	{
		BGMPlayer = GameEngineSound::SoundPlay("ClockTowerofNightMare.mp3", 10000);
		return;
	}

	std::string BGMName = BGMPlayer.GetCurSoundName();
	if ("ClockTowerofNightMare.mp3" != BGMName)
	{
		BGMPlayer.Stop();
		BGMPlayer = GameEngineSound::SoundPlay("ClockTowerofNightMare.mp3", 10000);
	}
}

void ClockTowerBaseLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

	if (nullptr != CurMap)
	{
		CurMap = nullptr;
	}

	if (nullptr != CurPlayer)
	{
		CurPlayer = nullptr;
	}

	if (nullptr != Back)
	{
		Back = nullptr;
	}

	AllMonster.clear();
}

void ClockTowerBaseLevel::Start()
{
	ContentLevel::Start();
	AllMonster.reserve(33);
}

void ClockTowerBaseLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	RespawnMonster(_Delta);

	if (CurPlayer->Transform.GetWorldPosition().Y <= -CurMapScale.Y)
	{
		CurPlayer->Transform.SetLocalPosition(TeleportPos);
		CurPlayer->MoveVectorForceReset();
	}
}

void ClockTowerBaseLevel::ResourcesRelease()
{

}

void ClockTowerBaseLevel::RespawnMonster(float _Delta)
{
	RespawnTime -= _Delta;
	if (0.0f < RespawnTime)
	{
		return;
	}

	for (size_t i = 0; i < AllMonster.size(); i++)
	{
		if (false == AllMonster[i].Monster->IsUpdate() /*|| FieldMonsterState::Death == AllMonster[i].Monster->GetState()*/)
		{
			AllMonster[i].Monster->Respawn();
			AllMonster[i].Monster->Transform.SetLocalPosition(AllMonster[i].RespawnPos);
		}
	}

	RespawnTime = RESPAWN_TIME;
}

void ClockTowerBaseLevel::PlaceMonster(std::shared_ptr<class FieldMonster> _Monster, float4 _RespawnPos)
{
	_Monster->Transform.SetLocalPosition(_RespawnPos);
}
