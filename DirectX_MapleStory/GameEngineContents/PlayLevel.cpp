#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "ContentMap.h"
#include "GlobalValue.h"

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

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();
	CurMap = CreateActor<ContentMap>();
	CurMap->Init("Lacheln.png");
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