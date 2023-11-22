#include "PreCompile.h"
#include "Boss_ClearRoom.h"
#include "Player.h"
#include "ContentMap.h"
#include "ContentBackGround.h"
#include "FireWork.h"
#include "Portal.h"
#include "Minimap.h"
#include "FadeObject.h"
#include "NightmareMusicBox.h"	

Boss_ClearRoom::Boss_ClearRoom()
{

}

Boss_ClearRoom::~Boss_ClearRoom()
{

}

void Boss_ClearRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = "10.Boss_WaitingRoom";
	NextLevel = "10.Boss_WaitingRoom";

	ContentLevel::LevelStart(_PrevLevel);

	if (nullptr == GameEngineSound::FindSound("ClockTowerofNightMare.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BGM\\ClockTowerofNightMare.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
	}

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("Lucid_WaitingRoom.png");
		CurMap->InitMapCollision("Collision_Lucid_WaitingRoom.png");
	}

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Next.png");
	}

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
	}

	CurPlayer->Transform.SetLocalPosition(float4(1250, -836));
	CurPlayer->SetDir(ActorDir::Left);
	GetMainCamera()->Transform.SetLocalPosition(float4(1250, -836, -100000));

	std::shared_ptr<FireWork> _FireWork = CreateActor<FireWork>(UpdateOrder::Map);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({100, -100});

	_FireWork = CreateActor<FireWork>(UpdateOrder::Map);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({ 350, -350 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::Map);
	_FireWork->Init(FireWorkType::FireWork1);
	_FireWork->Transform.SetLocalPosition({ 300, -350 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::Map);
	_FireWork->Init(FireWorkType::FireWork2);
	_FireWork->Transform.SetLocalPosition({ 300, -550 });	

	_FireWork = CreateActor<FireWork>(UpdateOrder::Map);
	_FireWork->Init(FireWorkType::FireWork3);
	_FireWork->Transform.SetLocalPosition({ 430, -150 });

	std::shared_ptr<NightmareMusicBox> _MusicBox = CreateActor<NightmareMusicBox>(UpdateOrder::Monster);
	_MusicBox->Transform.SetLocalPosition({ 1000, -842 });

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({750, -845});
	_Portal->SetMoveMap("10.Boss_WaitingRoom");

	Minimap::CreateMinimap("Minimap_Boss_WaitingRoom.png", "악몽의 시계탑");

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

void Boss_ClearRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	
	if (nullptr != CurMap)
	{
		CurMap = nullptr;
	}

	if (nullptr != Back)
	{
		Back = nullptr;
	}

	if (nullptr != CurPlayer)
	{
		CurPlayer = nullptr;
	}
}

void Boss_ClearRoom::Start()
{
	ContentLevel::Start();
}

void Boss_ClearRoom::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}