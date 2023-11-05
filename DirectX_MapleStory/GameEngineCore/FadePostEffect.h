#pragma once
#include "GameEngineRenderTarget.h"

class FadePostEffect : public Effect
{
public:
	// constrcuter destructer
	FadePostEffect();
	~FadePostEffect();

	// delete Function
	FadePostEffect(const FadePostEffect& _Other) = delete;
	FadePostEffect(FadePostEffect&& _Other) noexcept = delete;
	FadePostEffect& operator=(const FadePostEffect& _Other) = delete;
	FadePostEffect& operator=(FadePostEffect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;
};
