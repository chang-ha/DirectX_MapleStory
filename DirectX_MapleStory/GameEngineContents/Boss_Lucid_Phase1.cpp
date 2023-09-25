#include "PreCompile.h"
#include "Boss_Lucid_Phase1.h"

Boss_Lucid_Phase1::Boss_Lucid_Phase1()
{

}

Boss_Lucid_Phase1::~Boss_Lucid_Phase1()
{

}

void Boss_Lucid_Phase1::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseBossActor::LevelStart(_PrevLevel);
}

void Boss_Lucid_Phase1::LevelEnd(GameEngineLevel* _NextLevel)
{
	BaseBossActor::LevelEnd(_NextLevel);
}

void Boss_Lucid_Phase1::Start()
{
	BaseBossActor::Start();
}

void Boss_Lucid_Phase1::Update(float _Delta)
{
	BaseBossActor::Update(_Delta);
}
