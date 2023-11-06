#include "PreCompile.h"
#include "ServerLevel.h"
#include "FadeObject.h"
#include "RenderActor.h"
#include "ContentButton.h"
#include "UIRenderActor.h"

ServerLevel::ServerLevel()
{

}

ServerLevel::~ServerLevel()
{

}

void ServerLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
	FadeInObject->Off();

	FadeOutObject->SetChangeLevel("CharacterSelect");
	FadeOutObject->SetFadeSpeed(2.0f);

	// Server Animation Logo
	if (nullptr == GameEngineSprite::Find("ServerLogo"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Login\\ServerLogo");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("ServerButton_BG.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\ServerButton_BG.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	std::shared_ptr<RenderActor> _Actor = CreateActor<RenderActor>(UpdateOrder::RenderActor);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->CreateAnimation("ServerLogo", "ServerLogo");
	_Actor->Renderer->ChangeAnimation("ServerLogo");
	_Actor->Renderer->AutoSpriteSizeOff();
	_Actor->Renderer->SetImageScale(GlobalValue::WinScale);

	_Actor->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());
	GetMainCamera()->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());

	std::shared_ptr<UIRenderActor> _UIActor = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_UIActor->Init(RenderOrder::UI, RenderDepth::ui);
	_UIActor->Renderer->SetSprite("ServerButton_BG.png");
	_UIActor->Transform.SetLocalPosition({ 1260, -265 });

	std::shared_ptr<ContentButton> _Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("GameEnd");
	_Button->Transform.SetLocalPosition({ _Button->GetButtonScale().hX(), -730});
	_Button->SetButtonClickEndEvent([]()
		{
			GameEngineWindow::WindowLoopOff();
		});

	_Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("WorldButton");
	_Button->Transform.SetLocalPosition({ 1260, -50 });
	_Button->SetButtonClickEndEvent([&]()
		{
			FadeOutObject->FadeStart();
		});
}

void ServerLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

	if (nullptr != GameEngineSprite::Find("ServerLogo"))
	{
		GameEngineSprite::Release("ServerLogo");
	}
}

void ServerLevel::Start()
{
	ContentLevel::Start();
}

void ServerLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}
