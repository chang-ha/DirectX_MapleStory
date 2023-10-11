#include "PreCompile.h"
#include "Lucid_Next.h"
#include "RenderActor.h"
#include "ContentMap.h"
#include "ContentBackGround.h"

Lucid_Next::Lucid_Next()
{

}

Lucid_Next::~Lucid_Next()
{

}

void Lucid_Next::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->Init("Lucid_Next.png");
	}

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Next.png");
	}

	GetMainCamera()->Transform.SetLocalPosition(float4(1000, -500));

	// Player Renderer
	if (nullptr == PlayerRender)
	{
		PlayerRender = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		PlayerRender->Init(RenderOrder::RenderActor);
		PlayerRender->Renderer->CreateAnimation("Idle", "Idle", 0.5f);
		PlayerRender->Renderer->ChangeAnimation("Idle");
		PlayerRender->Renderer->AutoSpriteSizeOn();
		PlayerRender->Renderer->LeftFlip();
		PlayerRender->Transform.SetLocalPosition({ 750, -800 });
	}

	// Clock Renderer
	if (nullptr == GameEngineSprite::Find("Clock"))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\Boss\\Clock.png");
		GameEngineTexture::Load(Path.GetStringPath());
		GameEngineSprite::CreateSingle("Clock.png");
	}

	if (nullptr == Clock)
	{
		Clock = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		Clock->Init(RenderOrder::RenderActor);
		Clock->Renderer->SetSprite("Clock.Png");
		Clock->Renderer->AutoSpriteSizeOn();
		Clock->Transform.SetLocalPosition({ 1099, -488 });
	}

	// Lucid Renderer
	if (nullptr == GameEngineSprite::Find("Lucid_PhaseChange"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid_PhaseChange");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	if (nullptr == LucidRender)
	{
		LucidRender = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		LucidRender->Init(RenderOrder::RenderActor);
		LucidRender->Renderer->CreateAnimation("Lucid_PhaseChange", "Lucid_PhaseChange", 0.09f, -1, -1, false);
		LucidRender->Renderer->ChangeAnimation("Lucid_PhaseChange");
		LucidRender->Renderer->AutoSpriteSizeOn();
		LucidRender->Transform.SetLocalPosition({ 1099, -488 });

		LucidRender->Renderer->SetFrameEvent("Lucid_PhaseChange", 26, [&](GameEngineRenderer* _Renderer)
			{
				Clock->Death();
			}
		);

		LucidRender->Renderer->SetEndEvent("Lucid_PhaseChange", [&](GameEngineRenderer* _Renderer)
			{
				GameEngineCore::ChangeLevel("Lucid_Phase2");
			}
		);
	}
}

void Lucid_Next::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

	if (nullptr != PlayerRender)
	{
		PlayerRender->Death();
		PlayerRender = nullptr;
	}

	if (nullptr != Clock)
	{
		Clock->Death();
		Clock = nullptr;
	}

	if (nullptr != LucidRender)
	{
		LucidRender->Death();
		LucidRender = nullptr;
	}
}

void Lucid_Next::Start()
{
	ContentLevel::Start();
}

void Lucid_Next::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}