#include "PreCompile.h"
#include "FadeObject.h"


FadeObject::FadeObject()
{

}

FadeObject::~FadeObject()
{

}

void FadeObject::Start()
{
	Off();

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("FadeObjectEffect");
	EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	EffectUnit.ShaderResHelper.SetSampler("FadeTexSampler", "POINT");
	EffectUnit.ShaderResHelper.SetTexture("FadeTex", EffectTarget->GetTexture(0));

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
}

void FadeObject::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	EffectTarget->Copy(0, ResultTarget, 0);
}

//void FadeObject::Update(float _Delta)
//{
//
//	if (1.0f <= FadeRenderer->GetColorData().MulColor.A && "" != ChangeLevelName)
//	{
//		GameEngineCore::ChangeLevel(ChangeLevelName);
//	}
//
//	float _Alpha = _Delta * FadeSpeed;
//	FadeRenderer->GetColorData().MulColor.A -= _Alpha;
//	if (0.0f > FadeRenderer->GetColorData().MulColor.A)
//	{
//		FadeRenderer->GetColorData().MulColor.A = 0.0f;
//	}
//}