#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();
}

void PlayLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}