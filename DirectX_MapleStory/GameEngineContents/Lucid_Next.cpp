#include "PreCompile.h"
#include "Lucid_Next.h"
#include "RenderActor.h"
#include "ContentMap.h"
#include "ContentBackGround.h"
#include "FadeObject.h"
#include "FireWork.h"
#include "Minimap.h"
#include "ReleaseFunction.h"

Lucid_Next::Lucid_Next()
{

}

Lucid_Next::~Lucid_Next()
{

}

void Lucid_Next::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	FadeOutObject->SetWhiteFade();

	FadeOutObject->SetChangeLevel("6.Lucid_Phase2");

	if (nullptr == GameEngineSprite::Find("Render_Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Character\\Idle");
		GameEngineSprite::CreateFolder("Render_Idle", Dir.GetStringPath());
	}

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->InitMap("Lucid_Next.png");
	}

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Next.png");
	}

	GetMainCamera()->Transform.SetLocalPosition(float4(750, -580));

	// Player Renderer
	if (nullptr == PlayerRender)
	{
		PlayerRender = CreateActor<RenderActor>(UpdateOrder::RenderActor);
		PlayerRender->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		PlayerRender->Renderer->Transform.SetLocalPosition({0, 0, RenderDepth::renderactor});
		PlayerRender->Renderer->CreateAnimation("Idle", "Render_Idle", 0.5f);
		PlayerRender->Renderer->ChangeAnimation("Idle");
		PlayerRender->Renderer->AutoSpriteSizeOn();
		PlayerRender->Renderer->LeftFlip();
		PlayerRender->Transform.SetLocalPosition({ 750, -800 });
	}

	// Clock Renderer
	if (nullptr == GameEngineSprite::Find("Clock.png"))
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
		Clock->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		Clock->Renderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::renderactor });
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
		LucidRender->Init(RenderOrder::RENDERACTOR, RenderDepth::renderactor);
		LucidRender->Renderer->Transform.SetLocalPosition({0, 0, RenderDepth::renderactor});
		LucidRender->Renderer->CreateAnimation("Lucid_PhaseChange", "Lucid_PhaseChange", 0.09f, -1, -1, false);
		LucidRender->Renderer->ChangeAnimation("Lucid_PhaseChange");
		LucidRender->Renderer->AutoSpriteSizeOn();
		LucidRender->Transform.SetLocalPosition({ 1099, -488 });

		LucidRender->Renderer->SetFrameEvent("Lucid_PhaseChange", 26, [&](GameEngineRenderer* _Renderer)
			{
				Clock->Death();
			}
		);

		LucidRender->Renderer->SetFrameEvent("Lucid_PhaseChange", 37, [&](GameEngineRenderer* _Renderer)
			{
				FadeOutObject->FadeStart();
				// GameEngineCore::ChangeLevel("6.Lucid_Phase2");
			}
		);
	}

	std::shared_ptr<FireWork> _FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork1);
	_FireWork->Transform.SetLocalPosition({ 200, -100 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork2);
	_FireWork->Transform.SetLocalPosition({ 300, -200 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork3);
	_FireWork->Transform.SetLocalPosition({ 400, -300 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork4);
	_FireWork->Transform.SetLocalPosition({ 500, -400 });

	_FireWork = CreateActor<FireWork>(UpdateOrder::BackGround);
	_FireWork->Init(FireWorkType::FireWork5);
	_FireWork->Transform.SetLocalPosition({ 600, -500 });

	Minimap::CreateMinimap("Minimap_Lucid_Next.png", "악몽의 시계탑");
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

void Lucid_Next::ResourcesRelease()
{
	if (nullptr != GameEngineSprite::Find("Render_Idle"))
	{
		GameEngineSprite::Release("Render_Idle");
	}
	
	if (nullptr != GameEngineSprite::Find("Clock.png"))
	{
		GameEngineTexture::Release("Clock.png");
		GameEngineSprite::Release("Clock.png");
	}

	if (nullptr != GameEngineSprite::Find("Lucid_PhaseChange"))
	{
		ReleaseFunction::FolderRelease("Lucid_PhaseChange", "PhaseChange_");
	}
}
