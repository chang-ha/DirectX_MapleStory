#include "PreCompile.h"
#include "ContentLevel.h"

ContentLevel::ContentLevel()
{

}

ContentLevel::~ContentLevel()
{

}

void ContentLevel::Start()
{

}

void ContentLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress(VK_F1))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (GameEngineInput::IsPress(VK_F2))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	
}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}