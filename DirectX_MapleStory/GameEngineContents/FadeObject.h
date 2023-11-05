#pragma once
#include <GameEngineCore\GameEngineRenderTarget.h>

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
	}

	void SetBlackFade()
	{
	}

	void SetFadeSpeed(float _FadeSpeed)
	{
		FadeSpeed = _FadeSpeed;
	}

	void SetAlpha(float _Alpha)
	{
	}

	float GetCurAlpha()
	{
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
	float FadeSpeed = 0.0f;
	std::string ChangeLevelName = "";
};

