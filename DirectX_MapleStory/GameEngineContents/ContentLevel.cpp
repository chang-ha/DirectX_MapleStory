#include "PreCompile.h"
#include "ContentLevel.h"
#include "ContentMap.h"
#include "FadeObject.h"

void LevelDebug::Start()
{
	
}

void LevelDebug::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Checkbox("MapCollision", &ContentMap::IsCollisionDebug);
	ImGui::Checkbox("Collision", &GameEngineLevel::IsDebug);
}

ContentLevel::ContentLevel()
{

}

ContentLevel::~ContentLevel()
{

}

ContentLevel* ContentLevel::CurContentLevel = nullptr;

void ContentLevel::Start()
{
	GameEngineInput::AddInputObject(this);
	GameEngineGUI::CreateGUIWindow<LevelDebug>("LevelDebug");

	std::shared_ptr<GameEngineCamera> UICamera = GetCamera(static_cast<int>(ECAMERAORDER::UI));
	UICamera->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());
}

void ContentLevel::Update(float _Delta)
{
}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CurContentLevel = this;

	if (nullptr == FadeInObject)
	{
		FadeInObject = CreateActor<FadeObject>(UpdateOrder::UI);
		FadeInObject->SetFadeSpeed(1.0f);
		FadeInObject->SetAlpha(1.0f);
	}

	if (nullptr == FadeOutObject)
	{
		FadeOutObject = CreateActor<FadeObject>(UpdateOrder::UI);
		FadeOutObject->SetFadeSpeed(-1.0f);
		FadeOutObject->SetAlpha(0.0f);
	}

	FadeInObject->FadeStart();
}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	// sFadeOutObject->FadeStart();

	if (nullptr != FadeInObject)
	{
		FadeInObject = nullptr;
	}

	if (nullptr != FadeOutObject)
	{
		FadeOutObject = nullptr;
	}
}