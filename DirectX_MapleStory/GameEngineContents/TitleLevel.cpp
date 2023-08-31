#include "PreCompile.h"
#include "TitleLevel.h"
#include "Player.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}


void TitleLevel::Start()
{
	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();
}

void TitleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress(VK_F2))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}