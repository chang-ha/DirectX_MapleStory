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
	// All Resource Files Load
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
		GameEngineSprite::CreateCut("TestPlayer.png", 6, 6);
	}

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

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