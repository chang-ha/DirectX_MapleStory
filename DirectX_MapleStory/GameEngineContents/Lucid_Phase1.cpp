#include "PreCompile.h"
#include "Lucid_Phase1.h"
#include "Player.h"
#include "ContentMap.h"
#include "SkillManager.h"
#include "ContentBackGround.h"

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
}

void Lucid_Phase1::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

}

