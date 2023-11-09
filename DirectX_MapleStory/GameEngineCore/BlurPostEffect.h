#pragma once
#include "GameEngineRenderTarget.h"

// Ό³Έν :
class BlurPostEffect : public Effect
{
public:
	// constrcuter destructer
	BlurPostEffect();
	~BlurPostEffect();

	// delete Function
	BlurPostEffect(const BlurPostEffect& _Other) = delete;
	BlurPostEffect(BlurPostEffect&& _Other) noexcept = delete;
	BlurPostEffect& operator=(const BlurPostEffect& _Other) = delete;
	BlurPostEffect& operator=(BlurPostEffect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;
};

