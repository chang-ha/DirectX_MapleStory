#include "PreCompile.h"
#include "Boss_WaitingRoom.h"
#include "Player.h"
#include "ContentMap.h"
#include "ContentBackGround.h"
#include "SkillManager.h"
#include "FireWork.h"
#include "Portal.h"
#include "Minimap.h"
#include "ClockTowerOfNightMare_5th.h"
#include "Lachlen.h"
#include "ContentNpc.h"
#include "FadeObject.h"
	
Boss_WaitingRoom::Boss_WaitingRoom()
{

}

Boss_WaitingRoom::~Boss_WaitingRoom()
{

}

void Boss_WaitingRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = "9.ClockTowerOfNightMare_5th";
	NextLevel = "12.Lucid_Phase1";

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

	ClockTowerOfNightMare_5th* PrevLevel = dynamic_cast<ClockTowerOfNightMare_5th*>(_PrevLevel);
	if (nullptr != PrevLevel)
	{
		CurPlayer->Transform.SetLocalPosition(float4(750, -836));
		GetMainCamera()->Transform.SetLocalPosition(float4(750, -836, -100000));
	}
	else
	{
		CurPlayer->Transform.SetLocalPosition(float4(1000, -836));
		GetMainCamera()->Transform.SetLocalPosition(float4(1000, -836, -100000));
	}

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

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({750, -845});
	_Portal->SetMoveMap("9.ClockTowerOfNightMare_5th");

	std::shared_ptr<ContentNpc> _Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 1200, -838 });
	_Npc->Init("GasMask", "방독면", ActorDir::Left);
	_Npc->CreateTwoButtonMent("Npc_BossEnter_Cancel", "Npc_BossEnter_Ok", [=]()
		{
			_Npc->NpcMentOff();
			std::shared_ptr<FadeObject> _FadeObject = ContentLevel::CurContentLevel->FadeOutObject;
			_FadeObject->SetChangeLevel("11.Lucid_Enter");
			_FadeObject->FadeStart();
		});
	_Npc->SetMentText(L"루시드를 쓰러트리기 위해 몽환의 숲으로 이동하시겠습니까?");

	Minimap::CreateMinimap("Minimap_Boss_WaitingRoom.png", "악몽의 시계탑 꼭대기");

	if (false == BGMPlayer.IsPlaying())
	{
		BGMPlayer = GameEngineSound::SoundPlay("ClockTowerofNightMare.mp3", 10000);
		BGMPlayer.SetVolume(GlobalValue::BGVolume);
		return;
	}

	std::string BGMName = BGMPlayer.GetCurSoundName();
	if ("ClockTowerofNightMare.mp3" != BGMName)
	{
		BGMPlayer.Stop();
		BGMPlayer = GameEngineSound::SoundPlay("ClockTowerofNightMare.mp3", 10000);
		BGMPlayer.SetVolume(GlobalValue::BGVolume);
	}
}

void Boss_WaitingRoom::LevelEnd(GameEngineLevel* _NextLevel)
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

void Boss_WaitingRoom::Start()
{
	ContentLevel::Start();
}

void Boss_WaitingRoom::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void Boss_WaitingRoom::ResourcesRelease()
{

}