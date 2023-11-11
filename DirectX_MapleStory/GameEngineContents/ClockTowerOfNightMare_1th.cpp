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
		CurPlayer->Transform.SetLocalPosition({ 600, -340 });
		GetMainCamera()->Transform.SetLocalPosition(float4(600, -300, -100000));
	}

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	Minimap::CreateMinimap("Minimap_ClockTowerOfNightMare_1th.png", "악몽의시계탑 1층");

	CreateMonster<Dreamkeeper>({ 1000, -480 });
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