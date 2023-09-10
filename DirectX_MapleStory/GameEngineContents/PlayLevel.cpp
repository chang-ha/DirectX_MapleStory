#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "ContentMap.h"
#include "SkillManager.h"

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

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>(UpdateOrder::Play);
	NewPlayer->Transform.SetLocalPosition(float4(100, -100));
	CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
	CurMap->Init("Lacheln.png");
	CreateActor<SkillManager>();

	std::shared_ptr<ContentMonster> TestMonster = CreateActor<ContentMonster>(UpdateOrder::Monster);
	TestMonster->Transform.SetLocalPosition({400, -780});
}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
}