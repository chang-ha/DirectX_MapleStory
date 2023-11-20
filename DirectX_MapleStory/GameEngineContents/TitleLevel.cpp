#include "PreCompile.h"
#include "TitleLevel.h"
#include "Player.h"
#include "ContentBackGround.h"
#include "RenderActor.h"
#include "FadeObject.h"
#include "ContentMap.h"
#include "ReleaseFunction.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	NextLevel = "02.ServerLevel";

	if (nullptr == GameEngineSound::FindSound("NxLogo.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\BGM\\NxLogo.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
	}

	ContentLevel::LevelStart(_PrevLevel);
	FadeInObject->SetWhiteFade();
	FadeInObject->SetFadeSpeed(0.5f);

	FadeOutObject->SetWhiteFade();
	FadeOutObject->SetChangeLevel("02.ServerLevel");

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

	_Actor->Renderer->SetFrameEvent("Logo", 36, [&](GameEngineSpriteRenderer*)
		{
			FadeOutObject->FadeStart();
		}
	);

	float4 WinScale = GlobalValue::WinScale;
	WinScale.Y *= -1.0f;
	_Actor->Transform.SetLocalPosition(WinScale.Half() + float4(0, 70.0f));
	GetMainCamera()->Transform.SetLocalPosition(WinScale.Half());

	if (nullptr == CurMap)
	{
		CurMap = CreateActor<ContentMap>(UpdateOrder::Map);
		CurMap->CreateBaseColorMap({ 1.0f, 1.0f, 1.0f, 1.0f });
	}

	BGMPlayer.Stop();
	BGMPlayer = GameEngineSound::SoundPlay("NxLogo.mp3", 0);
	BGMPlayer.SetVolume(GlobalValue::BGVolume);
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
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

void TitleLevel::ResourcesRelease()
{
	ContentLevel::ResourcesRelease();

	if (nullptr != GameEngineSprite::Find("Logo"))
	{
		ReleaseFunction::FolderRelease("Logo", "Logo_");
	}
}