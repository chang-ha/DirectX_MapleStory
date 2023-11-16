#include "PreCompile.h"
#include "ClockTowerOfNightMare_1th.h"
#include "ContentMap.h"
#include "Player.h"
#include "Minimap.h"
#include "Portal.h"
#include "FieldMonster.h"
#include "BlueEyed_Gargoyle.h"
#include "RedEyed_Gargoyle.h"
#include "Dreamkeeper.h"
#include "Lamp.h"
#include "FireWork.h"
#include "ClockTowerOfNightMare_2th.h"
#include "LinkPortal.h"
#include "ContentNpc.h"

ClockTowerOfNightMare_1th::ClockTowerOfNightMare_1th()
{

}

ClockTowerOfNightMare_1th::~ClockTowerOfNightMare_1th()
{

}

void ClockTowerOfNightMare_1th::LevelStart(GameEngineLevel* _PrevLevel)
{
	ClockTowerBaseLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("ClockOfTower_1th.png");
		CurMap->InitMapCollision("Collision_ClockOfTower_1th.png");
		CurMap->InitFootHold("ClockOfTower_1th_FootHold.png");
	}

	TeleportPos = float4(1300, -2800);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
	}

	ClockTowerOfNightMare_2th* PrevLevel = dynamic_cast<ClockTowerOfNightMare_2th*>(_PrevLevel);
	if (nullptr != PrevLevel)
	{
		CurPlayer->Transform.SetLocalPosition({ 1350, -480 });
		GetMainCamera()->Transform.SetLocalPosition(float4(1350, -480, -100000));
	}
	else
	{
		CurPlayer->Transform.SetLocalPosition({ 455, -2860 });
		GetMainCamera()->Transform.SetLocalPosition(float4(455, -2860, -100000));
	}

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	Minimap::CreateMinimap("Minimap_ClockTowerOfNightMare_1th.png", "악몽의시계탑 1층");

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 1350, -490 });
	_Portal->SetMoveMap("ClockTowerOfNightMare_2th");

	_Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 450, -2875 });
	_Portal->SetMoveMap("Lachlen");

	std::shared_ptr<LinkPortal> _LinkPortal1 = CreateActor<LinkPortal>(UpdateOrder::Portal);
	_LinkPortal1->Transform.SetLocalPosition({ 1300, -2870 });

	std::shared_ptr<LinkPortal> _LinkPortal2 = CreateActor<LinkPortal>(UpdateOrder::Portal);
	_LinkPortal2->Transform.SetLocalPosition({ 650, -483 });
	_LinkPortal2->DoubleLinkPortal(_LinkPortal1.get());

	std::shared_ptr<Lamp> _Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp9);
	_Lamp->Transform.SetLocalPosition({ 1135, -482 });

	CreateMonster<Dreamkeeper>({ 900, -480 });
	CreateMonster<Dreamkeeper>({ 1200, -480 });
	CreateMonster<Dreamkeeper>({ 550, -480 });
	CreateMonster<Dreamkeeper>({ 1000, -700 });
	CreateMonster<Dreamkeeper>({ 810, -775 });
	CreateMonster<Dreamkeeper>({ 750, -1050 });
	CreateMonster<Dreamkeeper>({ 1100, -1050 });
	CreateMonster<Dreamkeeper>({ 910, -1125 });
	CreateMonster<Dreamkeeper>({ 800, -1320 });
	CreateMonster<Dreamkeeper>({ 950, -1400 });
	CreateMonster<Dreamkeeper>({ 550, -1630 });
	CreateMonster<Dreamkeeper>({ 900, -1630 });
	CreateMonster<Dreamkeeper>({ 1300, -1630 });
	CreateMonster<Dreamkeeper>({ 1050, -1865 });
	CreateMonster<Dreamkeeper>({ 1300, -1865 });
	CreateMonster<Dreamkeeper>({ 700, -1940 });
	CreateMonster<Dreamkeeper>({ 550, -2168 });
	CreateMonster<Dreamkeeper>({ 750, -2242 });
	CreateMonster<Dreamkeeper>({ 1300, -2245 });
	CreateMonster<Dreamkeeper>({ 1100, -2320 });
	CreateMonster<Dreamkeeper>({ 930, -2395 });
	CreateMonster<Dreamkeeper>({ 570, -2547 });
	CreateMonster<Dreamkeeper>({ 820, -2735 });
	CreateMonster<Dreamkeeper>({ 1000, -2660 });
	CreateMonster<Dreamkeeper>({ 1070, -2965 });
	CreateMonster<Dreamkeeper>({ 1300, -2865});

	std::shared_ptr<ContentNpc> _Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 620, -2868 });
	_Npc->Init("ShrimpMask", "새우가면", ActorDir::Left);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"새우가면");
}

void ClockTowerOfNightMare_1th::LevelEnd(GameEngineLevel* _NextLevel)
{
	ClockTowerBaseLevel::LevelEnd(_NextLevel);
}

void ClockTowerOfNightMare_1th::Start()
{
	ClockTowerBaseLevel::Start();
}

void ClockTowerOfNightMare_1th::Update(float _Delta)
{
	ClockTowerBaseLevel::Update(_Delta);
}