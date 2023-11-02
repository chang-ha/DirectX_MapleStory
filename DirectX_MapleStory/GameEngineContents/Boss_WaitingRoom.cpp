﻿#include "PreCompile.h"
#include "Boss_WaitingRoom.h"
#include "Player.h"
#include "ContentMap.h"
#include "ContentBackGround.h"
#include "SkillManager.h"
#include "FireWork.h"
#include "Portal.h"
#include "Minimap.h"
#include "ClockTowerOfNightMare_1th.h"
	
Boss_WaitingRoom::Boss_WaitingRoom()
{

}

Boss_WaitingRoom::~Boss_WaitingRoom()
{

}

void Boss_WaitingRoom::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("Lucid_WaitingRoom.png");
		CurMap->InitMapCollision("Collision_Lucid_WaitingRoom.png");
	}

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Next.png");
	}

	if (nullptr == CurPlayer)
	{
		CurPlayer = CreateActor<Player>(UpdateOrder::Play);
		ClockTowerOfNightMare_1th* _Level = dynamic_cast<ClockTowerOfNightMare_1th*>(_PrevLevel);
		if (nullptr != _Level)
		{
			CurPlayer->Transform.SetLocalPosition(float4(750, -810));
			GetMainCamera()->Transform.SetLocalPosition(float4(750, -810, -100000));
		}
		else
		{
			CurPlayer->Transform.SetLocalPosition(float4(1000, -810));
			GetMainCamera()->Transform.SetLocalPosition(float4(1000, -810, -100000));
		}
	}

	if (nullptr == SkillManagerActor)
	{
		SkillManagerActor = CreateActor<SkillManager>();
	}

	std::shared_ptr<FireWork> _FireWork = CreateActor<FireWork>(UpdateOrder::Map);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({100, -100});

	_FireWork = CreateActor<FireWork>(UpdateOrder::Map);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({ 350, -350 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::Map);
	_FireWork->Init(FireWorkType::FireWork1);
	_FireWork->Transform.SetLocalPosition({ 300, -350 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::Map);
	_FireWork->Init(FireWorkType::FireWork2);
	_FireWork->Transform.SetLocalPosition({ 300, -550 });	

	_FireWork = CreateActor<FireWork>(UpdateOrder::Map);
	_FireWork->Init(FireWorkType::FireWork3);
	_FireWork->Transform.SetLocalPosition({ 430, -150 });

	std::shared_ptr<Portal> _Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({750, -772});
	_Portal->SetMoveMap("ClockTowerOfNightMare_1th");

	_Portal = CreateActor<Portal>(UpdateOrder::Portal);
	_Portal->Transform.SetLocalPosition({ 1300, -772 });
	_Portal->SetMoveMap("3.Lucid_Enter");

	Minimap::CreateMinimap("Minimap_Boss_WaitingRoom.png", "악몽의시계탑꼭대기");
}

void Boss_WaitingRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	
	if (nullptr == CurMap)
	{
		CurMap->Death();
		CurMap = nullptr;
	}

	if (nullptr == Back)
	{
		Back->Death();
		Back = nullptr;
	}

	if (nullptr != CurPlayer)
	{
		CurPlayer = nullptr;
	}

	if (nullptr != SkillManagerActor)
	{
		SkillManagerActor = nullptr;
	}
}

void Boss_WaitingRoom::Start()
{
	ContentLevel::Start();
}

void Boss_WaitingRoom::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}