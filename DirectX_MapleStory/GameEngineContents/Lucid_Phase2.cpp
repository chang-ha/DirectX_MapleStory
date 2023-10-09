#include "PreCompile.h"
#include "Lucid_Phase2.h"
#include "Player.h"
#include "ContentMap.h"
#include "SkillManager.h"
#include "ContentBackGround.h"

Lucid_Phase2::Lucid_Phase2()
{

}

Lucid_Phase2::~Lucid_Phase2()
{

}

void Lucid_Phase2::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
	CurMap->Init("Lucid_Phase1.png");

	CurPlayer = CreateActor<Player>(UpdateOrder::Play);
	CurPlayer->Transform.SetLocalPosition(float4(100, -700));
	GetMainCamera()->Transform.SetLocalPosition(float4(100, -700));
	CreateActor<SkillManager>();

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Phase1.png");
	}
}

void Lucid_Phase2::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	CurPlayer->Death();
}

void Lucid_Phase2::Start()
{
	ContentLevel::Start();
	// GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
}

void Lucid_Phase2::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}