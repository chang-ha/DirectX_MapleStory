﻿#include "PreCompile.h"
#include "ClockTowerOfNightMare_5th.h"
#include "ContentMap.h"
#include "Player.h"
#include "Portal.h"
#include "Minimap.h"
#include "BlueEyed_Gargoyle.h"
#include "RedEyed_Gargoyle.h"

ClockTowerOfNightMare_5th::ClockTowerOfNightMare_5th()
{

}

ClockTowerOfNightMare_5th::~ClockTowerOfNightMare_5th()
{

}


void ClockTowerOfNightMare_5th::LevelStart(GameEngineLevel* _PrevLevel)
{
	ClockTowerBaseLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("ClockOfTower_5th.png");
		CurMap->InitMapCollision("Collision_ClockOfTower_5th.png");
		CurMap->InitFootHold("ClockOfTower_5th_FootHold.png");
	}

	TeleportPos = float4(500, -2800);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		CurPlayer->Transform.SetLocalPosition({ 600, -2750 });
		GetMainCamera()->Transform.SetLocalPosition(float4(600, -2750, -100000));
	}

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 600, -290 });
	_Portal->SetMoveMap("Boss_WaitingRoom");

	_Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 500, -2815 });
	_Portal->SetMoveMap("ClockTowerOfNightMare_4th");

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	Minimap::CreateMinimap("Minimap_ClockTowerOfNightMare_5th.png", "악몽의시계탑 5층");

	CreateMonster<RedEyed_Gargoyle>({ 900, -525 });
	CreateMonster<BlueEyed_Gargoyle>({1000, -525 });
	CreateMonster<RedEyed_Gargoyle>({ 1150, -525 });
	CreateMonster<RedEyed_Gargoyle>({ 970, -710 });
	CreateMonster<BlueEyed_Gargoyle>({ 1100, -690 });
	CreateMonster<RedEyed_Gargoyle>({ 800, -880 });
	CreateMonster<BlueEyed_Gargoyle>({ 600, -1016 });
	CreateMonster<BlueEyed_Gargoyle>({ 1080, -1057 });
	CreateMonster<RedEyed_Gargoyle>({ 1330, -1133 });
	CreateMonster<RedEyed_Gargoyle>({ 900, -1389 });
	CreateMonster<BlueEyed_Gargoyle>({ 550, -1614 });
	CreateMonster<BlueEyed_Gargoyle>({ 550, -2017 });
	CreateMonster<RedEyed_Gargoyle>({ 780, -1943 });
	CreateMonster<BlueEyed_Gargoyle>({ 1100, -1943 });
	CreateMonster<RedEyed_Gargoyle>({ 1350, -2017 });
	CreateMonster<RedEyed_Gargoyle>({ 700, -2289 });
	CreateMonster<RedEyed_Gargoyle>({ 1150, -2288 });
	CreateMonster<BlueEyed_Gargoyle>({ 510, -2364 });
	CreateMonster<BlueEyed_Gargoyle>({ 1350, -2363});
	CreateMonster<BlueEyed_Gargoyle>({ 800, -2465});
	CreateMonster<RedEyed_Gargoyle>({ 600, -2540});
	CreateMonster<BlueEyed_Gargoyle>({ 1100, -2577});
	CreateMonster<RedEyed_Gargoyle>({ 700, -2802 });
	CreateMonster<BlueEyed_Gargoyle>({ 650, -2953});
	CreateMonster<RedEyed_Gargoyle>({ 750, -2953 });
	CreateMonster<BlueEyed_Gargoyle>({ 1150, -2840});
	CreateMonster<RedEyed_Gargoyle>({ 1350, -2765 });
}

void ClockTowerOfNightMare_5th::LevelEnd(GameEngineLevel* _NextLevel)
{
	ClockTowerBaseLevel::LevelEnd(_NextLevel);


}

void ClockTowerOfNightMare_5th::Start()
{
	ClockTowerBaseLevel::Start();
}

void ClockTowerOfNightMare_5th::Update(float _Delta)
{
	ClockTowerBaseLevel::Update(_Delta);
}