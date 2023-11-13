#include "PreCompile.h"
#include "ClockTowerOfNightMare_2th.h"
#include "ContentMap.h"
#include "Player.h"
#include "Minimap.h"
#include "Portal.h"
#include "Lamp.h"
#include "Dreamkeeper.h"

ClockTowerOfNightMare_2th::ClockTowerOfNightMare_2th()
{

}

ClockTowerOfNightMare_2th::~ClockTowerOfNightMare_2th()
{

}


void ClockTowerOfNightMare_2th::LevelStart(GameEngineLevel* _PrevLevel)
{
	ClockTowerBaseLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("ClockOfTower_2th.png");
		CurMap->InitMapCollision("Collision_ClockOfTower_2th.png");
		CurMap->InitFootHold("ClockOfTower_2th_FootHold.png");
	}

	// TeleportPos = float4(500, -2800);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		CurPlayer->Transform.SetLocalPosition({ 600, -2300 });
		GetMainCamera()->Transform.SetLocalPosition(float4(600, -2300, -100000));
	}

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	Minimap::CreateMinimap("Minimap_ClockTowerOfNightMare_2th.png", "악몽의시계탑 2층");

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 1350, -426 });
	_Portal->SetMoveMap("ClockTowerOfNightMare_3th");

	_Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 510, -2901 });
	_Portal->SetMoveMap("ClockTowerOfNightMare_1th");

	std::shared_ptr<Lamp> _Lamp = CreateActor<Lamp>(UpdateOrder::Map);
	_Lamp->Init(LampType::Lamp10);
	_Lamp->Transform.SetLocalPosition({ 925, -68 });

	CreateMonster<Dreamkeeper>({ 500, -492 });
	CreateMonster<Dreamkeeper>({ 1300, -490 });
	CreateMonster<Dreamkeeper>({ 650, -717 });
	CreateMonster<Dreamkeeper>({ 900, -717 });
	CreateMonster<Dreamkeeper>({ 1050, -717 });
	CreateMonster<Dreamkeeper>({ 500, -1145 });
	CreateMonster<Dreamkeeper>({ 700, -1070 });
	CreateMonster<Dreamkeeper>({ 1100, -1070 });
	CreateMonster<Dreamkeeper>({ 1350, -1145 });
	CreateMonster<Dreamkeeper>({ 700, -1354 });
	CreateMonster<Dreamkeeper>({ 950, -1279 });
	CreateMonster<Dreamkeeper>({ 1250, -1279 });
	CreateMonster<Dreamkeeper>({ 500, -1595 });
	CreateMonster<Dreamkeeper>({ 700, -1672 });
	CreateMonster<Dreamkeeper>({ 1150, -1674 });
	CreateMonster<Dreamkeeper>({ 1350, -1749 });
	CreateMonster<Dreamkeeper>({ 700, -1938 });
	CreateMonster<Dreamkeeper>({ 850, -1938 });
	CreateMonster<Dreamkeeper>({ 1000, -1938 });
	CreateMonster<Dreamkeeper>({ 1150, -1938 });
	CreateMonster<Dreamkeeper>({ 750, -2317 });
	CreateMonster<Dreamkeeper>({ 1100, -2317 });
	CreateMonster<Dreamkeeper>({ 910, -2393 });
	CreateMonster<Dreamkeeper>({ 1150, -2489 });
	CreateMonster<Dreamkeeper>({ 960, -2563 });
	CreateMonster<Dreamkeeper>({ 800, -2639 });
	CreateMonster<Dreamkeeper>({ 1100, -2852 });
	CreateMonster<Dreamkeeper>({ 1340, -2925 });
}

void ClockTowerOfNightMare_2th::LevelEnd(GameEngineLevel* _NextLevel)
{
	ClockTowerBaseLevel::LevelEnd(_NextLevel);

}

void ClockTowerOfNightMare_2th::Start()
{
	ClockTowerBaseLevel::Start();

}

void ClockTowerOfNightMare_2th::Update(float _Delta)
{
	ClockTowerBaseLevel::Update(_Delta);

}