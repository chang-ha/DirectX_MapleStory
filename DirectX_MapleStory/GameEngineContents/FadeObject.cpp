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

	EffectUnit.SetMesh("FullRect");
	EffectUnit.SetMaterial("FadeOutObjectEffect");
	EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	EffectUnit.ShaderResHelper.SetConstantBufferLink("FadeObjectInfo", FadeObjectInfoValue);
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

	if (1.0f <= RenderBaseInfoValue.AccDeltaTime * FadeObjectInfoValue.FadeSpeed && "" != ChangeLevelName)
	{
		GameEngineCore::ChangeLevel(ChangeLevelName);
	}

	EffectTarget->Copy(0, ResultTarget, 0);
}