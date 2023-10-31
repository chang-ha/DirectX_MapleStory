#include "PreCompile.h"
#include "Boss_WaitingRoom.h"
#include "Player.h"
#include "ContentMap.h"
#include "ContentBackGround.h"
#include "SkillManager.h"

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
		CurPlayer->Transform.SetLocalPosition(float4(1000, -300));
		GetMainCamera()->Transform.SetLocalPosition(float4(1000, -300, -100000));
	}

	if (nullptr == SkillManagerActor)
	{
		SkillManagerActor = CreateActor<SkillManager>();
	}
}

void Boss_WaitingRoom::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

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