#include "PreCompile.h"
#include "ContentLevel.h"

ContentLevel::ContentLevel()
{

}

ContentLevel::~ContentLevel()
{

}

ContentLevel* ContentLevel::CurContentLevel = nullptr;

void ContentLevel::Start()
{

}

void ContentLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress('1'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (GameEngineInput::IsPress('2'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CurContentLevel = this;
}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}