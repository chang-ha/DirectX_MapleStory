#include "PreCompile.h"
#include "ClockTowerOfNightMare_1th.h"
#include "ContentMap.h"
#include "Player.h"

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
		CurMap->InitMap("Lachlen_Tower_5th.png");
		CurMap->InitMapCollision("Collision_Lachlen_Tower_5th.png");
	}

	StartPos = float4(500, -2800);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		CurPlayer->Transform.SetLocalPosition(StartPos);
		GetMainCamera()->Transform.SetLocalPosition(float4(500, -2800, -100000));
	}


	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
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