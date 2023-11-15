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
	
Boss_WaitingRoom::Boss_WaitingRoom()
{

}

Boss_WaitingRoom::~Boss_WaitingRoom()
{

}

void Boss_WaitingRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

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
	_Portal->SetMoveMap("ClockTowerOfNightMare_5th");

	_Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 1300, -845 });
	_Portal->SetMoveMap("3.Lucid_Enter");

	Minimap::CreateMinimap("Minimap_Boss_WaitingRoom.png", "악몽의 시계탑 꼭대기");

	std::shared_ptr<ContentNpc> _Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 1200, -838 });
	_Npc->Init("GasMask.png", ActorDir::Left);
}

void Boss_WaitingRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	
	//if (nullptr != GameEngineSprite::Find("BG_Lucid_Next.png"))
	//{
	//	GameEngineSprite::Release("BG_Lucid_Next.png");
	//}

	if (nullptr == CurMap)
	{
		CurMap = nullptr;
	}

	if (nullptr == Back)
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