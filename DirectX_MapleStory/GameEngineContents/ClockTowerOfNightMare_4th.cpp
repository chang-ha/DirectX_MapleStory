#include "PreCompile.h"
#include "ClockTowerOfNightMare_4th.h"
#include "ContentMap.h"
#include "Player.h"
#include "Minimap.h"
#include "RedEyed_Gargoyle.h"
#include "Portal.h"
#include "Lamp.h"
#include "ClockTowerOfNightMare_5th.h"
#include "LinkPortal.h"

ClockTowerOfNightMare_4th::ClockTowerOfNightMare_4th()
{

}

ClockTowerOfNightMare_4th::~ClockTowerOfNightMare_4th()
{

}

void ClockTowerOfNightMare_4th::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = "07.ClockTowerOfNightMare_3th";
	NextLevel = "09.ClockTowerOfNightMare_5th";

	ClockTowerBaseLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("ClockOfTower_4th.png");
		CurMap->InitMapCollision("Collision_ClockOfTower_4th.png");
		CurMap->InitFootHold("ClockOfTower_4th_FootHold.png");
	}

	TeleportPos = float4(920, -2900);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
	}

	ClockTowerOfNightMare_5th* PrevLevel = dynamic_cast<ClockTowerOfNightMare_5th*>(_PrevLevel);
	if (nullptr != PrevLevel)
	{
		CurPlayer->Transform.SetLocalPosition({ 1250, -523 });
		GetMainCamera()->Transform.SetLocalPosition(float4(1250, -523, -100000));
	}
	else
	{
		CurPlayer->Transform.SetLocalPosition({ 750, -2893 });
		GetMainCamera()->Transform.SetLocalPosition(float4(750, -2893, -100000));
	}

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	Minimap::CreateMinimap("Minimap_ClockTowerOfNightMare_4th.png", "악몽의시계탑 4층");

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 1250, -532 });
	_Portal->SetMoveMap("09.ClockTowerOfNightMare_5th");

	_Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 750, -2900 });
	_Portal->SetMoveMap("07.ClockTowerOfNightMare_3th");

	std::shared_ptr<LinkPortal> _LinkPortal1 = CreateActor<LinkPortal>(UpdateOrder::Portal);
	_LinkPortal1->Transform.SetLocalPosition({ 920, -2970 });

	std::shared_ptr<LinkPortal> _LinkPortal2 = CreateActor<LinkPortal>(UpdateOrder::Portal);
	_LinkPortal2->Transform.SetLocalPosition({ 790, -452 });
	_LinkPortal2->DoubleLinkPortal(_LinkPortal1.get());

	std::shared_ptr<Lamp> _Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp9);
	_Lamp->Transform.SetLocalPosition({ 1115, -530 });

	CreateMonster<RedEyed_Gargoyle>({ 650, -349 });
	CreateMonster<RedEyed_Gargoyle>({ 820, -475 });
	CreateMonster<RedEyed_Gargoyle>({ 1000, -525 });
	CreateMonster<RedEyed_Gargoyle>({ 1130, -525 });
	CreateMonster<RedEyed_Gargoyle>({ 1350, -525 });
	CreateMonster<RedEyed_Gargoyle>({ 750, -634 });
	CreateMonster<RedEyed_Gargoyle>({ 530, -710 });
	CreateMonster<RedEyed_Gargoyle>({ 1180, -692 });
	CreateMonster<RedEyed_Gargoyle>({ 850, -828 });
	CreateMonster<RedEyed_Gargoyle>({ 600, -1016 });
	CreateMonster<RedEyed_Gargoyle>({ 500, -1255 });
	CreateMonster<RedEyed_Gargoyle>({ 700, -1181 });
	CreateMonster<RedEyed_Gargoyle>({ 1100, -1178 });
	CreateMonster<RedEyed_Gargoyle>({ 1300, -1255 });
	CreateMonster<RedEyed_Gargoyle>({ 900, -1390 });
	CreateMonster<RedEyed_Gargoyle>({ 650, -1567 });
	CreateMonster<RedEyed_Gargoyle>({ 530, -1613 });
	CreateMonster<RedEyed_Gargoyle>({ 1250, -1745 });
	CreateMonster<RedEyed_Gargoyle>({ 620, -1916 });
	CreateMonster<RedEyed_Gargoyle>({ 800, -1990 });
	CreateMonster<RedEyed_Gargoyle>({ 900, -1990 });
	CreateMonster<RedEyed_Gargoyle>({ 1000, -1990 });
	CreateMonster<RedEyed_Gargoyle>({ 1350, -1990 });
	CreateMonster<RedEyed_Gargoyle>({ 1150, -2340 });
	CreateMonster<RedEyed_Gargoyle>({ 650, -2265 });
	CreateMonster<RedEyed_Gargoyle>({ 800, -2265 });
	CreateMonster<RedEyed_Gargoyle>({ 720, -2571 });
	CreateMonster<RedEyed_Gargoyle>({ 1120, -2570 });
	CreateMonster<RedEyed_Gargoyle>({ 500, -2646 });
	CreateMonster<RedEyed_Gargoyle>({ 1350, -2645 });
	CreateMonster<RedEyed_Gargoyle>({ 550, -2817 });
	CreateMonster<RedEyed_Gargoyle>({ 1300, -2817 });
	CreateMonster<RedEyed_Gargoyle>({ 930, -2968 });
}

void ClockTowerOfNightMare_4th::LevelEnd(GameEngineLevel* _NextLevel)
{
	ClockTowerBaseLevel::LevelEnd(_NextLevel);

}

void ClockTowerOfNightMare_4th::Start()
{
	ClockTowerBaseLevel::Start();

}

void ClockTowerOfNightMare_4th::Update(float _Delta)
{
	ClockTowerBaseLevel::Update(_Delta);

}