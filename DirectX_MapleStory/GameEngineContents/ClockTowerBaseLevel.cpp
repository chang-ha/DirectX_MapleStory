#include "PreCompile.h"
#include "ClockTowerBaseLevel.h"
#include "ContentBackGround.h"
#include "SkillManager.h"
#include "ContentMap.h"
#include "Player.h"
#include "FieldMonster.h"
#include "TowerWall.h"

ClockTowerBaseLevel::ClockTowerBaseLevel()
{

}

ClockTowerBaseLevel::~ClockTowerBaseLevel()
{

}

void ClockTowerBaseLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	AllMonster.clear();

	ContentLevel::LevelStart(_PrevLevel);

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Next.png");
	}

	LeftWall = CreateActor<TowerWall>(UpdateOrder::Map);
	LeftWall->Transform.SetLocalPosition({290, 3});
	LeftWall->WallRenderer->LeftFlip();
	RightWall = CreateActor<TowerWall>(UpdateOrder::Map);
	RightWall->Transform.SetLocalPosition({ 1593, 3 });
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

}

void ClockTowerBaseLevel::Start()
{
	ContentLevel::Start();
	AllMonster.reserve(27);
}

void ClockTowerBaseLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	RespawnMonster(_Delta);

	if (CurPlayer->Transform.GetWorldPosition().Y <= -CurMapScale.Y)
	{
		CurPlayer->Transform.SetLocalPosition(StartPos);
		CurPlayer->MoveVectorForceReset();
	}
}

void ClockTowerBaseLevel::RespawnMonster(float _Delta)
{
	RespawnTime -= _Delta;
	if (0.0f < RespawnTime)
	{
		return;
	}

	for (size_t i = 0; i < AllMonster.size(); i++)
	{
		if (false == AllMonster[i].Monster->IsUpdate() || FieldMonsterState::Death == AllMonster[i].Monster->GetState())
		{
			AllMonster[i].Monster->Respawn();
			AllMonster[i].Monster->Transform.SetLocalPosition(AllMonster[i].RespawnPos);
		}
	}

	RespawnTime = RESPAWN_TIME;
}

void ClockTowerBaseLevel::PlaceMonster(std::shared_ptr<class FieldMonster> _Monster, float4 _RespawnPos)
{
	_Monster->Transform.SetLocalPosition(_RespawnPos);
}
