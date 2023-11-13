#include "PreCompile.h"
#include "ClockTowerOfNightMare_5th.h"
#include "ContentMap.h"
#include "Player.h"
#include "Portal.h"
#include "Minimap.h"
#include "Dreamkeeper.h"

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
		CurMap->InitMap("Lachlen_Tower_5th.png");
		CurMap->InitMapCollision("Collision_Lachlen_Tower_5th.png");
	}

	TeleportPos = float4(500, -2800);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		CurPlayer->Transform.SetLocalPosition({ 600, -340 });
		GetMainCamera()->Transform.SetLocalPosition(float4(600, -300, -100000));
	}

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 600, -290 });
	_Portal->SetMoveMap("Boss_WaitingRoom");

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	Minimap::CreateMinimap("Minimap_ClockTowerOfNightMare_5th.png", "악몽의시계탑 5층");

	std::shared_ptr<Dreamkeeper> _FieldMonster = CreateActor<Dreamkeeper>(UpdateOrder::Monster);
	_FieldMonster->Transform.SetLocalPosition({ 1000, -480 });

	//std::shared_ptr<RedEyed_Gargoyle> _FieldMonster2 = CreateActor<RedEyed_Gargoyle>(UpdateOrder::Monster);
	//_FieldMonster2->Transform.SetLocalPosition({ 1200, -480 });
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