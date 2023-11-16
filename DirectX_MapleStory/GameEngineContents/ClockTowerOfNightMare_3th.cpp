#include "PreCompile.h"
#include "ClockTowerOfNightMare_3th.h"
#include "Player.h"
#include "ContentMap.h"
#include "Minimap.h"
#include "Lamp.h"
#include "BlueEyed_Gargoyle.h"
#include "Portal.h"
#include "LinkPortal.h"
#include "ClockTowerOfNightMare_4th.h"
#include "ContentNpc.h"

ClockTowerOfNightMare_3th::ClockTowerOfNightMare_3th()
{

}

ClockTowerOfNightMare_3th::~ClockTowerOfNightMare_3th()
{

}

void ClockTowerOfNightMare_3th::LevelStart(GameEngineLevel* _PrevLevel)
{
	ClockTowerBaseLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("ClockOfTower_3th.png");
		CurMap->InitMapCollision("Collision_ClockOfTower_3th.png");
		CurMap->InitFootHold("ClockOfTower_3th_FootHold.png");
	}

	TeleportPos = float4(1115, -2860);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
	}

	ClockTowerOfNightMare_4th* PrevLevel = dynamic_cast<ClockTowerOfNightMare_4th*>(_PrevLevel);
	if (nullptr != PrevLevel)
	{
		CurPlayer->Transform.SetLocalPosition({ 1350, -488 });
		GetMainCamera()->Transform.SetLocalPosition(float4(1350, -488, -100000));
	}
	else
	{
		CurPlayer->Transform.SetLocalPosition({ 500, -2998 });
		GetMainCamera()->Transform.SetLocalPosition(float4(500, -2998, -100000));
	}

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 500, -3005 });
	_Portal->SetMoveMap("ClockTowerOfNightMare_2th");

	_Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 1350, -496 });
	_Portal->SetMoveMap("ClockTowerOfNightMare_4th");

	std::shared_ptr<LinkPortal> _LinkPortal1 = CreateActor<LinkPortal>(UpdateOrder::Portal);
	_LinkPortal1->Transform.SetLocalPosition({ 1115, -2925 });

	std::shared_ptr<LinkPortal> _LinkPortal2 = CreateActor<LinkPortal>(UpdateOrder::Portal);
	_LinkPortal2->Transform.SetLocalPosition({ 600, -470 });
	_LinkPortal2->DoubleLinkPortal(_LinkPortal1.get());

	std::shared_ptr<Lamp> _Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp10);
	_Lamp->Transform.SetLocalPosition({1075, -460});

	_Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp8);
	_Lamp->Transform.SetLocalPosition({ 477, -1280 });

	CreateMonster<BlueEyed_Gargoyle>({ 510, -491 });
	CreateMonster<BlueEyed_Gargoyle>({ 750, -415 });
	CreateMonster<BlueEyed_Gargoyle>({ 1150, -415 });
	CreateMonster<BlueEyed_Gargoyle>({ 1380, -488 });
	CreateMonster<BlueEyed_Gargoyle>({ 900, -772 });
	CreateMonster<BlueEyed_Gargoyle>({ 530, -996 });
	CreateMonster<BlueEyed_Gargoyle>({ 1300, -819 });
	CreateMonster<BlueEyed_Gargoyle>({ 980, -1042 });
	CreateMonster<BlueEyed_Gargoyle>({ 730, -1313 });
	CreateMonster<BlueEyed_Gargoyle>({ 1280, -1313 });
	CreateMonster<BlueEyed_Gargoyle>({ 870, -1567 });
	CreateMonster<BlueEyed_Gargoyle>({ 650, -1640 });
	CreateMonster<BlueEyed_Gargoyle>({ 550, -1790 });
	CreateMonster<BlueEyed_Gargoyle>({ 700, -1790 });
	CreateMonster<BlueEyed_Gargoyle>({ 950, -1790 });
	CreateMonster<BlueEyed_Gargoyle>({ 1100, -1790 });
	CreateMonster<BlueEyed_Gargoyle>({ 1330, -1713 });
	CreateMonster<BlueEyed_Gargoyle>({ 1000	, -1963 });
	CreateMonster<BlueEyed_Gargoyle>({ 750	, -2070 });
	CreateMonster<BlueEyed_Gargoyle>({ 550	, -2188 });
	CreateMonster<BlueEyed_Gargoyle>({ 800	, -2506 });
	CreateMonster<BlueEyed_Gargoyle>({ 1200	, -2506 });
	CreateMonster<BlueEyed_Gargoyle>({ 1000	, -2581 });
	CreateMonster<BlueEyed_Gargoyle>({ 1030	, -2581	 });
	CreateMonster<BlueEyed_Gargoyle>({ 1350	, -2430 });
	CreateMonster<BlueEyed_Gargoyle>({ 800	, -2709 });
	CreateMonster<BlueEyed_Gargoyle>({ 1050	, -2785 });
	CreateMonster<BlueEyed_Gargoyle>({ 1120	, -2920 });
	CreateMonster<BlueEyed_Gargoyle>({ 1300	, -2995 });

	std::shared_ptr<ContentNpc> _Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 500, -2505 });
	_Npc->Init("DarkMask", "검은가면", ActorDir::Right);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"검은가면");

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	Minimap::CreateMinimap("Minimap_ClockTowerOfNightMare_3th.png", "악몽의시계탑 3층");
}

void ClockTowerOfNightMare_3th::LevelEnd(GameEngineLevel* _NextLevel)
{
	ClockTowerBaseLevel::LevelEnd(_NextLevel);

}

void ClockTowerOfNightMare_3th::Start()
{
	ClockTowerBaseLevel::Start();

}

void ClockTowerOfNightMare_3th::Update(float _Delta)
{
	ClockTowerBaseLevel::Update(_Delta);

}