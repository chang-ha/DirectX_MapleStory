#include "PreCompile.h"
#include "FadeObject.h"

FadeObject::FadeObject()
{

}

FadeObject::~FadeObject()
{

}

void FadeObject::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void FadeObject::Start()
{
	if (nullptr == FadeRenderer)
	{
		FadeRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::FADEOBJECT);
		FadeRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::fadeobject});
		FadeRenderer->SetImageScale(GlobalValue::WinScale);
		// 기본으로 검은 FadeObject
		FadeRenderer->GetColorData().PlusColor = { -1.0f, -1.0f, -1.0f };

		Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());
	}
}

void FadeObject::Update(float _Delta)
{
	if (1.0f <= FadeRenderer->GetColorData().MulColor.A && "" != ChangeLevelName)
	{
		GameEngineCore::ChangeLevel(ChangeLevelName);
	}

	if (false == IsFadeOn)
	{
		return;
	}

	float _Alpha = _Delta * FadeSpeed;
	FadeRenderer->GetColorData().MulColor.A -= _Alpha;

	float test = FadeRenderer->GetColorData().MulColor.A;

}

void FadeObject::Release()
{
	if (nullptr != FadeRenderer)
	{
		FadeRenderer->Death();
		FadeRenderer = nullptr;
	}
}