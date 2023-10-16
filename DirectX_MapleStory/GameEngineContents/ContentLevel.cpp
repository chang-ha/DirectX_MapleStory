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
	GameEngineInput::AddInputObject(this);

	{
		std::shared_ptr<GameEngineCamera> BackGroundCamera = CreateCamera(INT_MIN, ECAMERAORDER::MainPrev);
	}
}

void ContentLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsPress('1', this))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::IsPress('2', this))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}

	if (true == GameEngineInput::IsDown(VK_F3, this))
	{
		GameEngineLevel::OnDebug();
	}

	if (true == GameEngineInput::IsDown(VK_F4, this))
	{
		GameEngineLevel::OffDebug();
	}

	if (GameEngineInput::IsPress('O', this))
	{
		GameEngineCore::ChangeLevel("Lucid_Phase1");
	}

	if (GameEngineInput::IsPress('P', this))
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