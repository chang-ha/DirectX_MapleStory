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
	CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
	CurMap->Init("Lucid_Next.png");

	if (nullptr == Back)
	{
		Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
		Back->Init("BG_Lucid_Next.png");
	}

	GetMainCamera()->Transform.SetLocalPosition(float4(1000, -500));

	// Player Renderer
	std::shared_ptr<RenderActor> _Actor = CreateActor<RenderActor>();
	_Actor->Renderer->CreateAnimation("Idle", "Idle", 0.5f);
	_Actor->Renderer->ChangeAnimation("Idle");
	_Actor->Renderer->AutoSpriteSizeOn();
	_Actor->Renderer->LeftFlip();
	_Actor->Transform.SetLocalPosition({750, -800});

	// Clock Renderer
	if (nullptr == GameEngineTexture::Find("Clock"))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\Boss\\");
		GameEngineTexture::Load(Path.GetStringPath() + "Clock.png");
		GameEngineSprite::CreateSingle("Clock.png");
	}

	Clock = CreateActor<RenderActor>();
	Clock->Renderer->CreateAnimation("Clock", "Clock.png");
	Clock->Renderer->ChangeAnimation("Clock");
	Clock->Renderer->AutoSpriteSizeOn();
	Clock->Transform.SetLocalPosition({ 1099, -488 });

	// Lucid Renderer
	if (nullptr == GameEngineSprite::Find("Lucid_PhaseChange"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid_PhaseChange");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	_Actor = CreateActor<RenderActor>();
	_Actor->Renderer->CreateAnimation("Lucid_PhaseChange", "Lucid_PhaseChange", 0.09f);
	_Actor->Renderer->ChangeAnimation("Lucid_PhaseChange");
	_Actor->Renderer->AutoSpriteSizeOn();
	_Actor->Transform.SetLocalPosition({ 1099, -488 });

	_Actor->Renderer->SetFrameEvent("Lucid_PhaseChange", 26, [&](GameEngineRenderer* _Renderer)
		{
			Clock->Death();
		}
	);

	_Actor->Renderer->SetEndEvent("Lucid_PhaseChange", [&](GameEngineRenderer* _Renderer)
		{
			// GameEngineCore::ChangeLevel("");
		}
	);
}

void Lucid_Next::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
}

void Lucid_Next::Start()
{
	ContentLevel::Start();
}

void Lucid_Next::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}