#include "PreCompile.h"
#include "ClockTowerOfNightMare_3th.h"
#include "Player.h"
#include "ContentMap.h"
#include "Minimap.h"

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

	// StartPos = float4(500, -2800);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		CurPlayer->Transform.SetLocalPosition({ 550, -200 });
		GetMainCamera()->Transform.SetLocalPosition(float4(550, -200, -100000));
	}

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