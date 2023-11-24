#include "PreCompile.h"
#include "MultiKillManager.h"
#include "ContentLevel.h"
#include "ReleaseFunction.h"

MultiKillManager::MultiKillManager()
{

}

MultiKillManager::~MultiKillManager()
{

}

void MultiKillManager::LevelStart(class GameEngineLevel* _PrevLevel)
{

}

void MultiKillManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();

	if (nullptr != GameEngineSprite::Find("MultiKill_BG_Effect0"))
	{
		ReleaseFunction::FolderRelease("MultiKill_BG_Effect0", "MultiKill_BG_Effect0_");
		ReleaseFunction::FolderRelease("MultiKill_BG_Effect1", "MultiKill_BG_Effect1_");
	}

	if (nullptr != GameEngineSprite::Find("MultiKill_Num_010.png"))
	{
		for (size_t i = 0; i <= 10; i++)
		{
			GameEngineTexture::Release("MultiKill_Num_00" + std::to_string(i) +".png");
			GameEngineTexture::Release("MultiKill_Num_00" + std::to_string(i) +".png");

		}
	}
}

void MultiKillManager::Start()
{
	if (nullptr == GameEngineSprite::Find("MultiKill_BG_Effect0"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\MultiKill\\");
		GameEngineSprite::CreateFolder(Dir.GetStringPath() + "MultiKill_BG_Effect0");
		GameEngineSprite::CreateFolder(Dir.GetStringPath() + "MultiKill_BG_Effect1");
	}

	if (nullptr == GameEngineSprite::Find("MultiKill_Num_010.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\MultiKill\\MultiKill_Num");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	if (nullptr == MultiKill_BG_Renderer)
	{
		MultiKill_BG_Renderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		MultiKill_BG_Renderer->Transform.SetLocalPosition({GlobalValue::WinScale.hX(), -100, RenderDepth::ui});
		MultiKill_BG_Renderer->AutoSpriteSizeOn();
	}

	if (nullptr == MultiKill_Num_Renderer)
	{
		MultiKill_Num_Renderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		MultiKill_Num_Renderer->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 10 , -113, RenderDepth::ui });
		MultiKill_Num_Renderer->AutoSpriteSizeOn();
	}
}

void MultiKillManager::Release()
{
	if (nullptr != MultiKill_BG_Renderer)
	{
		MultiKill_BG_Renderer->Death();
		MultiKill_BG_Renderer = nullptr;
	}

	if (nullptr != MultiKill_Num_Renderer)
	{
		MultiKill_Num_Renderer->Death();
		MultiKill_Num_Renderer = nullptr;
	}
}

void MultiKillManager::MultiKillPrint(int _KillCount)
{
	if (3 > _KillCount)
	{
		return;
	}

	std::shared_ptr<MultiKillManager> _MultiManager = ContentLevel::CurContentLevel->CreateActor<MultiKillManager>(UpdateOrder::UI);
	_MultiManager->Init(_KillCount);
}

void MultiKillManager::Init(int _KillCount)
{
	if (10 <= _KillCount)
	{
		MultiKill_Num_Renderer->SetSprite("MultiKill_Num_0" + std::to_string(10) + ".png");
	}
	else
	{
		MultiKill_Num_Renderer->SetSprite("MultiKill_Num_00" + std::to_string(_KillCount) + ".png");
	}

	std::string BG_Effect = "";
	if (5 >= _KillCount)
	{
		BG_Effect = "0";
	}
	else if (5 < _KillCount)
	{
		BG_Effect = "1";
	}

	MultiKill_BG_Renderer->CreateAnimation("Effect", "MultiKill_BG_Effect" + BG_Effect, 0.09f, -1, -1, false);

	std::shared_ptr<GameEngineFrameAnimation> _Animation = MultiKill_BG_Renderer->FindAnimation("Effect");
	_Animation->Inter[2] = 0.3f;

	MultiKill_BG_Renderer->ChangeAnimation("Effect");

	MultiKill_BG_Renderer->SetFrameEvent("Effect", 3, [&](GameEngineRenderer* _Renderer)
		{
			MultiKill_Num_Renderer->GetColorData().MulColor.A = 0.7f;
		});

	MultiKill_BG_Renderer->SetFrameEvent("Effect", 4, [&](GameEngineRenderer* _Renderer)
		{
			MultiKill_Num_Renderer->GetColorData().MulColor.A = 0.4f;
		});

	MultiKill_BG_Renderer->SetFrameEvent("Effect", 5, [&](GameEngineRenderer* _Renderer)
		{
			MultiKill_Num_Renderer->GetColorData().MulColor.A = 0.1f;
		});

	MultiKill_BG_Renderer->SetEndEvent("Effect", [&](GameEngineRenderer* _Renderer)
		{
			Death();
		});
}
