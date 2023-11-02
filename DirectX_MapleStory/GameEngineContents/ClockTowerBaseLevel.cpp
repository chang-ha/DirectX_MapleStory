#include "PreCompile.h"
#include "ClockTowerBaseLevel.h"
#include "ContentBackGround.h"
#include "SkillManager.h"
#include "ContentMap.h"
#include "Player.h"

ClockTowerBaseLevel::ClockTowerBaseLevel()
{

}

ClockTowerBaseLevel::~ClockTowerBaseLevel()
{

}

void ClockTowerBaseLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Next.png");
	}

	if (nullptr == SkillManagerActor)
	{
		SkillManagerActor = CreateActor<SkillManager>();
	}

}

void ClockTowerBaseLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

	if (nullptr == CurMap)
	{
		CurMap->Death();
		CurMap = nullptr;
	}

	if (nullptr != CurPlayer)
	{
		CurPlayer->Death();
		CurPlayer = nullptr;
	}

	if (nullptr != Back)
	{
		Back->Death();
		Back = nullptr;
	}

	if (nullptr != SkillManagerActor)
	{
		SkillManagerActor->Death();
		SkillManagerActor = nullptr;
	}
}

void ClockTowerBaseLevel::Start()
{
	ContentLevel::Start();
}

void ClockTowerBaseLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	if (CurPlayer->Transform.GetWorldPosition().Y <= -CurMapScale.Y)
	{
		CurPlayer->Transform.SetLocalPosition(StartPos);
		CurPlayer->MoveVectorForceReset();
	}
}