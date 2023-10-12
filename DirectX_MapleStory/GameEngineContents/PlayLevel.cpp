#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "ContentMap.h"
#include "SkillManager.h"
#include "ContentBackGround.h"

//TestCode
#include "ContentMonster.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	ContentLevel::Start();
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	NewPlayer = CreateActor<Player>(UpdateOrder::Play);
	NewPlayer->Transform.SetLocalPosition(float4(100, -800));
	GetMainCamera()->Transform.SetLocalPosition(float4(100, -800));
	CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
	CurMap->Init("Lacheln.png");
	CreateActor<SkillManager>();

	std::shared_ptr<ContentBackGround> Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
	Back->Init("BG_Lacheln.png");
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
	NewPlayer->Death();
}