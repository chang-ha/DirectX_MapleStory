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
		CurMap->InitMap("Lachlen_Tower_1th.png");
		CurMap->InitMapCollision("Collision_Lachlen_Tower_1th.png");
	}

	StartPos = float4(500, -2800);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		CurPlayer->Transform.SetLocalPosition({ 550, -480 });
		GetMainCamera()->Transform.SetLocalPosition(float4(550, -480, -100000));
	}

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	Minimap::CreateMinimap("Minimap_ClockTowerOfNightMare_1th.png", "악몽의시계탑 1층");

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 1350, -418 });
	_Portal->SetMoveMap("Boss_WaitingRoom");

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