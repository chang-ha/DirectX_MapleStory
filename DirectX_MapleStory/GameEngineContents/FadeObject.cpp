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
	}
}

void FadeObject::Update(float _Delta)
{
	if (false == IsFadeOn)
	{
		return;
	}

	FadeRenderer->GetColorData().MulColor.A -= _Delta * FadeSpeed;
}

void FadeObject::Release()
{
	if (nullptr != FadeRenderer)
	{
		FadeRenderer->Death();
		FadeRenderer = nullptr;
	}
}