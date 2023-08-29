#include "PreCompile.h"
#include "PlayLevel.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start()
{
}

void PlayLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress(VK_F1))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}