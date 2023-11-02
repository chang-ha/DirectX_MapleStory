#include "PreCompile.h"
#include "ServerLevel.h"
#include "FadeObject.h"
#include "RenderActor.h"
#include "ContentButton.h"

ServerLevel::ServerLevel()
{

}

ServerLevel::~ServerLevel()
{

}

void ServerLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
	FadeInObject->SetWhiteFade();
	FadeInObject->SetAlpha(0.0f);

	FadeOutObject->SetChangeLevel("3.Lucid_Enter");
	FadeOutObject->SetFadeSpeed(-1.0f);

	if (nullptr == GameEngineSprite::Find("ServerLogo"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Login\\ServerLogo");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	std::shared_ptr<RenderActor> _Actor = CreateActor<RenderActor>(UpdateOrder::RenderActor);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->CreateAnimation("ServerLogo", "ServerLogo");
	_Actor->Renderer->ChangeAnimation("ServerLogo");
	_Actor->Renderer->AutoSpriteSizeOff();
	_Actor->Renderer->SetImageScale(GlobalValue::WinScale);

	_Actor->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());
	GetMainCamera()->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());

	std::shared_ptr<ContentButton> _Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("GameEnd");
	_Button->Transform.SetLocalPosition({40, -730});
	_Button->SetButtonClickEndEvent([]()
		{
			GameEngineWindow::WindowLoopOff();
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
