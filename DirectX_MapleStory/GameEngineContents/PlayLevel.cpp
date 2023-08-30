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
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\FolderTexture");
		// 해당 경로의 모든 하위폴더를 불러옴
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		// 폴더 1개를 스프라이트 1개로 만듦
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Dir = Directorys[i];
			GameEngineSprite::CreateFolder("Test2", Dir.GetStringPath());
		}
	}

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();
	NewPlayer->TestInit("Test2", -1, -1);

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