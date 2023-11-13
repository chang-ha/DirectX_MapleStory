#include "PreCompile.h"
#include "ClockTowerOfNightMare_4th.h"
#include "ContentMap.h"
#include "Player.h"
#include "Minimap.h"
#include "RedEyed_Gargoyle.h"
#include "Portal.h"

ClockTowerOfNightMare_4th::ClockTowerOfNightMare_4th()
{

}

ClockTowerOfNightMare_4th::~ClockTowerOfNightMare_4th()
{

}

void ClockTowerOfNightMare_4th::LevelStart(GameEngineLevel* _PrevLevel)
{
	ClockTowerBaseLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("ClockOfTower_4th.png");
		CurMap->InitMapCollision("Collision_ClockOfTower_4th.png");
		CurMap->InitFootHold("ClockOfTower_4th_FootHold.png");
	}

	// TeleportPos = float4(500, -2800);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		CurPlayer->Transform.SetLocalPosition({ 510, -491 });
		GetMainCamera()->Transform.SetLocalPosition(float4(510, -491, -100000));
	}

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	Minimap::CreateMinimap("Minimap_ClockTowerOfNightMare_4th.png", "악몽의시계탑 4층");

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 1250, -464 });
	_Portal->SetMoveMap("ClockTowerOfNightMare_5th");

	_Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 750, -2833 });
	_Portal->SetMoveMap("ClockTowerOfNightMare_3th");

	CreateMonster<RedEyed_Gargoyle>({ 650, -349 });
	CreateMonster<RedEyed_Gargoyle>({ 820, -450 });
	CreateMonster<RedEyed_Gargoyle>({ 1000, -525 });
	CreateMonster<RedEyed_Gargoyle>({ 1130, -525 });
	CreateMonster<RedEyed_Gargoyle>({ 1350, -525 });
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