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
	if (true == GameEngineInput::IsPress('1'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::IsPress('2'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}

	if (true == GameEngineInput::IsDown(VK_F3))
	{
		GameEngineLevel::OnDebug();
	}

	if (true == GameEngineInput::IsDown(VK_F4))
	{
		GameEngineLevel::OffDebug();
	}

	if (GameEngineInput::IsPress('O'))
	{
		GameEngineCore::ChangeLevel("Lucid_Phase1");
	}

	if (GameEngineInput::IsPress('P'))
	{
		GameEngineCore::ChangeLevel("Lucid_Next");
	}
}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CurContentLevel = this;
}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}