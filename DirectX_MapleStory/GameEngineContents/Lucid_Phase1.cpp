#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "Lucid_Phase1.h"
#include "Player.h"
#include "ContentMap.h"
#include "SkillManager.h"
#include "ContentBackGround.h"
#include "Boss_Lucid_Phase1.h"
#include "Dragon.h"

Lucid_Phase1::Lucid_Phase1()
{

}

Lucid_Phase1::~Lucid_Phase1()
{

}

void Lucid_Phase1::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
}

void Lucid_Phase1::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
}

void Lucid_Phase1::Start()
{
	ContentLevel::Start();
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>(UpdateOrder::Play);
	NewPlayer->Transform.SetLocalPosition(float4(100, -700));
	GetMainCamera()->Transform.SetLocalPosition(float4(100, -700));
	CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
	CurMap->Init("Lucid_Phase1.png");
	CreateActor<SkillManager>();

	std::shared_ptr<ContentBackGround> Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
	Back->Init("BG_Lucid_Phase1.png");

	std::shared_ptr<Boss_Lucid_Phase1> Boss = CreateActor<Boss_Lucid_Phase1>(UpdateOrder::Monster);
	Boss->Transform.SetLocalPosition(float4(1000, -700));

	LeftDragon = CreateActor<Dragon>(UpdateOrder::Monster);
	LeftDragon->Transform.SetLocalPosition(float4(30, -750));
	LeftDragon->SetDir(ActorDir::Right);

	RightDragon = CreateActor<Dragon>(UpdateOrder::Monster);
	RightDragon->Transform.SetLocalPosition(float4(1970, -750));
	RightDragon->SetDir(ActorDir::Left);
}

void Lucid_Phase1::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

}

void Lucid_Phase1::CallDragon()
{
	GameEngineRandom Random;
	Random.SetSeed(time(nullptr));
	int RandomValue = Random.RandomInt(0, 1);

	if (0 == RandomValue)
	{
		LeftDragon->ChangeState(DragonState::Down);
	}
	else
	{
		RightDragon->ChangeState(DragonState::Down);
	}
}
