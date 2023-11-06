#pragma once
#include <GameEngineCore\GameEngineRenderTarget.h>

struct FadeObjectInfo
{
	int FadeIn = false;
	int WhiteFade = false;
	float StartColor = -1.0f;
	float FadeSpeed = 1.0f;
};

class FadeObject : public Effect
{
public:
	// constructer destructer
	FadeObject();
	~FadeObject();

	// delete function
	FadeObject(const FadeObject& _Ohter) = delete;
	FadeObject(FadeObject&& _Ohter) noexcept = delete;
	FadeObject& operator=(const FadeObject& _Other) = delete;
	FadeObject& operator=(FadeObject&& _Other) noexcept = delete;

	void SetChangeLevel(std::string_view _ChangeLevelName)
	{
		ChangeLevelName = _ChangeLevelName;
	}

	void SetWhiteFade()
	{
		FadeObjectInfoValue.StartColor = 1.0f;
		FadeObjectInfoValue.WhiteFade = true;
	}

	void SetBlackFade()
	{
		FadeObjectInfoValue.StartColor = -1.0f;
	}

	void SetFadeSpeed(float _FadeSpeed)
	{
		FadeObjectInfoValue.FadeSpeed = _FadeSpeed;
	}

	void SetFadeIn()
	{
		FadeObjectInfoValue.FadeIn = true;
		EffectUnit.SetMaterial("FadeInObjectEffect");
		EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
		EffectUnit.ShaderResHelper.SetConstantBufferLink("FadeObjectInfo", FadeObjectInfoValue);
		EffectUnit.ShaderResHelper.SetSampler("FadeTexSampler", "POINT");
		EffectUnit.ShaderResHelper.SetTexture("FadeTex", EffectTarget->GetTexture(0));
	}

	void SetAlpha(float _Alpha)
	{
		// RenderBaseInfoValue.AccDeltaTime = _Alpha;
	}

	void FadeStart()
	{
		On();
	}

protected:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;

private:
	bool IsFadeOn = false;
	FadeObjectInfo FadeObjectInfoValue;
	std::string ChangeLevelName = "";
};

