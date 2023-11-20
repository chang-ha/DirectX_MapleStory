#include "PreCompile.h"
#include "ServerLevel.h"
#include "FadeObject.h"
#include "RenderActor.h"
#include "ContentButton.h"
#include "UIRenderActor.h"
#include "ButtonWarningMent.h"
#include "ReleaseFunction.h"

ServerLevel::ServerLevel()
{

}

ServerLevel::~ServerLevel()
{

}

void ServerLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	PrevLevel = "01.TitleLevel";
	NextLevel = "03.CharacterSelect";

	ContentLevel::LevelStart(_PrevLevel);
	FadeInObject->Off();

	FadeOutObject->SetChangeLevel("03.CharacterSelect");
	FadeOutObject->SetFadeSpeed(2.0f);

	// Server Animation Logo
	if (nullptr == GameEngineSprite::Find("ServerLogo"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Login\\ServerLogo");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	// Server Recommend
	if (nullptr == GameEngineSprite::Find("RecommendServer"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\RecommendServer");
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

	if (nullptr == GameEngineSound::FindSound("ServerSelect.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BGM\\ServerSelect.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
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
			std::shared_ptr<ButtonWarningMent> _Ment = ButtonWarningMent::CreateTwoButtonMent();
			_Ment->Init("MentBG_Normal.png", "Ment_EndGame.png");

			std::shared_ptr<ContentButton> _MentButton = _Ment->GetOkButton();
			_MentButton->SetButtonClickEndEvent([]()
				{
					GameEngineWindow::WindowLoopOff();
				});
		});
	AllButton.push_back(_Button);

	_Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("GoFirstLevel");
	_Button->Transform.SetLocalPosition({ _Button->GetButtonScale().hX(), -680 });
	_Button->SetButtonClickEndEvent([&]()
		{
			std::shared_ptr<ButtonWarningMent> _Ment = ButtonWarningMent::CreateTwoButtonMent();
			_Ment->Init("MentBG_Normal.png", "Ment_GoFirst.png");

			std::shared_ptr<ContentButton> _MentButton = _Ment->GetOkButton();
			_MentButton->SetButtonClickEndEvent([&]()
				{
					FadeOutObject->SetChangeLevel("01.TitleLevel");
					FadeOutObject->FadeStart();
				});
		});
	AllButton.push_back(_Button);

	_Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("TestWorldButton");
	_Button->Transform.SetLocalPosition({ 1260, -50 });
	_Button->SetButtonClickEndEvent([&]()
		{
			FadeOutObject->FadeStart();
		});
	_Button->SetButtonCollisionScale({90, 15});
	AllButton.push_back(_Button);

	_Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("TestWorld2Button");
	_Button->Transform.SetLocalPosition({ 1260, -84 });
	_Button->SetButtonClickEndEvent([&]()
		{
			std::shared_ptr<ButtonWarningMent> _Ment = ButtonWarningMent::CreateOneButtonMent();
			_Ment->Init("MentBG_Warning.png", "Ment_ServerFail.png");
		});
	_Button->SetButtonCollisionScale({ 90, 15 });
	AllButton.push_back(_Button);

	_Button = CreateActor<ContentButton>(UpdateOrder::UI);
	_Button->Init("TestWorld3Button");
	_Button->Transform.SetLocalPosition({ 1260, -117 });
	_Button->SetButtonClickEndEvent([&]()
		{
			std::shared_ptr<ButtonWarningMent> _Ment = ButtonWarningMent::CreateOneButtonMent();
			_Ment->Init("MentBG_Warning.png", "Ment_ServerFail.png");
		});
	_Button->SetButtonCollisionScale({ 90, 15 });
	AllButton.push_back(_Button);

	std::shared_ptr<UIRenderActor> _Actor2 = CreateActor<UIRenderActor>(UpdateOrder::UI);
	_Actor2->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor2->Renderer->CreateAnimation("RecommendServer", "RecommendServer");
	_Actor2->Renderer->ChangeAnimation("RecommendServer");
	_Actor2->Transform.SetLocalPosition({ 1236, -50 });

	if (false == BGMPlayer.IsPlaying())
	{
		BGMPlayer = GameEngineSound::SoundPlay("ServerSelect.mp3", 10000);
		return;
	}

	std::string BGMName = BGMPlayer.GetCurSoundName();
	if ("ServerSelect.mp3" != BGMName)
	{
		BGMPlayer.Stop();
		BGMPlayer = GameEngineSound::SoundPlay("ServerSelect.mp3", 10000);
	}
}

void ServerLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);


}

void ServerLevel::Start()
{
	ContentLevel::Start();
}

void ServerLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void ServerLevel::ResourcesRelease()
{
	ContentLevel::ResourcesRelease();

	if (nullptr != GameEngineSprite::Find("ServerLogo"))
	{
		ReleaseFunction::FolderRelease("ServerLogo", "ServerLogo_");
	}

	if (nullptr != GameEngineSprite::Find("RecommendServer"))
	{
		ReleaseFunction::FolderRelease("RecommendServer", "RecommendServer_");
	}

	if (nullptr != GameEngineSprite::Find("ServerButton_BG.png"))
	{
		GameEngineTexture::Release("ServerButton_BG.png");
		GameEngineSprite::Release("ServerButton_BG.png");
	}

	ContentButton::ReleaseButton("GameEnd");
	ContentButton::ReleaseButton("GoFirstLevel");
	ContentButton::ReleaseButton("TestWorldButton");
	ContentButton::ReleaseButton("TestWorld2Button");
	ContentButton::ReleaseButton("TestWorld3Button");
}

