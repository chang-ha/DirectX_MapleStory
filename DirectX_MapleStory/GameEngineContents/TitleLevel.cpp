#include "PreCompile.h"
#include "TitleLevel.h"
#include "Player.h"
#include "ContentBackGround.h"
#include "RenderActor.h"
#include "FadeObject.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}


void TitleLevel::Start()
{
	ContentLevel::Start();
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
}

void TitleLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
	FadeInObject->SetFadeSpeed(0.4f);

	if (nullptr == GameEngineSprite::Find("Logo"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Login\\Logo");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	std::shared_ptr<RenderActor> _Actor = CreateActor<RenderActor>(UpdateOrder::RenderActor);
	_Actor->Init(RenderOrder::UI, RenderDepth::ui);
	_Actor->Renderer->CreateAnimation("Logo", "Logo", 0.12f, -1, -1, false);
	_Actor->Renderer->ChangeAnimation("Logo");

	_Actor->Renderer->SetEndEvent("Logo", [&](GameEngineSpriteRenderer*)
		{
			Death();
			GameEngineCore::ChangeLevel("2.ServerLevel");
		}
	);

	float4 WinScale = GlobalValue::WinScale;
	//std::shared_ptr<ContentBackGround> Back = CreateActor<ContentBackGround>(UpdateOrder::BackGround);
	//Back->Init("Title.png", WinScale);
	WinScale.Y *= -1.0f;
	_Actor->Transform.SetLocalPosition(WinScale.Half() + float4(0, 70.0f));
	GetMainCamera()->Transform.SetLocalPosition(WinScale.Half());
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

	if (nullptr != GameEngineSprite::Find("Logo"))
	{
		GameEngineSprite::Release("Logo");
	}
}