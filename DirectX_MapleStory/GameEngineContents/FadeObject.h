#pragma once

class FadeObject : public GameEngineActor
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
		FadeRenderer->RenderBaseInfoValue.BaseColorOnly = true;
		FadeRenderer->RenderBaseInfoValue.BaseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	void SetBlackFade()
	{
		FadeRenderer->RenderBaseInfoValue.BaseColorOnly = true;
		FadeRenderer->RenderBaseInfoValue.BaseColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	}

	void SetFadeSpeed(float _FadeSpeed)
	{
		FadeSpeed = _FadeSpeed;
	}

	void SetAlpha(float _Alpha)
	{
		FadeRenderer->GetColorData().MulColor.A = _Alpha;
	}

	float GetCurAlpha()
	{
		return FadeRenderer->GetColorData().MulColor.A;
	}

	void FadeStart()
	{
		IsFadeOn = true;
	}

protected:

private:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	bool IsFadeOn = false;
	float FadeSpeed = 0.0f;
	std::string ChangeLevelName = "";
	std::shared_ptr<GameEngineUIRenderer> FadeRenderer = nullptr;
};

