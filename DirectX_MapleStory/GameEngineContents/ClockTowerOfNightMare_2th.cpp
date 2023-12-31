﻿#include "PreCompile.h"
#include "ClockTowerOfNightMare_2th.h"
#include "ContentMap.h"
#include "Player.h"
#include "Minimap.h"
#include "Portal.h"
#include "Lamp.h"
#include "Dreamkeeper.h"
#include "ClockTowerOfNightMare_3th.h"
#include "LinkPortal.h"
#include "ContentNpc.h"
#include "ReleaseFunction.h"

ClockTowerOfNightMare_2th::ClockTowerOfNightMare_2th()
{

}

ClockTowerOfNightMare_2th::~ClockTowerOfNightMare_2th()
{

}


void ClockTowerOfNightMare_2th::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = "05.ClockTowerOfNightMare_1th";
	NextLevel = "07.ClockTowerOfNightMare_3th";

	ClockTowerBaseLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("ClockOfTower_2th.png");
		CurMap->InitMapCollision("Collision_ClockOfTower_2th.png");
		CurMap->InitFootHold("ClockOfTower_2th_FootHold.png");
	}

	TeleportPos = float4(1115, -2800);

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
	}

	ClockTowerOfNightMare_3th* PrevLevel = dynamic_cast<ClockTowerOfNightMare_3th*>(_PrevLevel);
	if (nullptr != PrevLevel)
	{
		CurPlayer->Transform.SetLocalPosition({ 1350, -489 });
		GetMainCamera()->Transform.SetLocalPosition(float4(1350, -489, -100000));
	}
	else
	{
		CurPlayer->Transform.SetLocalPosition({ 510, -2965 });
		GetMainCamera()->Transform.SetLocalPosition(float4(510, -2965, -100000));
	}

	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	Minimap::CreateMinimap("Minimap_ClockTowerOfNightMare_2th.png", "악몽의시계탑 2층");

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 1350, -496 });
	_Portal->SetMoveMap("07.ClockTowerOfNightMare_3th");

	_Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 510, -2972 });
	_Portal->SetMoveMap("05.ClockTowerOfNightMare_1th");

	std::shared_ptr<LinkPortal> _LinkPortal1 = CreateActor<LinkPortal>(UpdateOrder::Portal);
	_LinkPortal1->Transform.SetLocalPosition({ 1115, -2855 });

	std::shared_ptr<LinkPortal> _LinkPortal2 = CreateActor<LinkPortal>(UpdateOrder::Portal);
	_LinkPortal2->Transform.SetLocalPosition({ 600, -470 });
	_LinkPortal2->DoubleLinkPortal(_LinkPortal1.get());

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

	std::shared_ptr<ContentNpc> _Npc = CreateActor<ContentNpc>(UpdateOrder::RenderActor);
	_Npc->Transform.SetLocalPosition({ 700, -2890 });
	_Npc->Init("WaterMelonMask", "수박가면", ActorDir::Left);
	_Npc->CreateOneButtonMent("Npc_Ok");
	_Npc->SetMentText(L"클리너는 위험하잖아~ 이 도시를 벗어나야 하잖아~");
}

void ClockTowerOfNightMare_2th::LevelEnd(GameEngineLevel* _NextLevel)
{
	ClockTowerBaseLevel::LevelEnd(_NextLevel);

	if (nullptr != GameEngineSprite::Find("Dreamkeeper_Death"))
	{
		ReleaseFunction::FolderRelease("Dreamkeeper_Death", "Dreamkeeper_Death_");
		ReleaseFunction::FolderRelease("Dreamkeeper_Attack", "Dreamkeeper_Attack_");
		ReleaseFunction::FolderRelease("Dreamkeeper_Attack_Hit", "Dreamkeeper_Attack_Hit_");
		ReleaseFunction::FolderRelease("Dreamkeeper_Idle", "Dreamkeeper_Idle_");
		ReleaseFunction::FolderRelease("Dreamkeeper_Move", "Dreamkeeper_Move_");
	}
}

void ClockTowerOfNightMare_2th::Start()
{
	ClockTowerBaseLevel::Start();

}

void ClockTowerOfNightMare_2th::Update(float _Delta)
{
	ClockTowerBaseLevel::Update(_Delta);

}