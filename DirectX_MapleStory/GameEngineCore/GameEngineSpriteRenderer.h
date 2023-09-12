#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"

class GameEngineFrameAnimation
{
	friend class GameEngineSpriteRenderer;

	void Reset();
	SpriteData Update(float _Delta);

	float Inter = 0.0f; // AnimationSpeed
	bool Loop = true;
	bool IsEnd = false;
	unsigned int Start = -1;
	unsigned int End = -1;
	unsigned int CurIndex = 0;
	float CurTime = 0.0f; // CurAnimationTime
	std::vector<int> Index;

	std::string AnimationName = "";
	std::string SpriteName = "";
	std::shared_ptr<GameEngineSprite> Sprite = nullptr;
	GameEngineSpriteRenderer* Parent = nullptr;

	// FrameEvent
	bool EventCheck = false;
	std::map<int, std::function<void(GameEngineSpriteRenderer*)>> FrameEventFunction;
	std::function<void(GameEngineSpriteRenderer*)> EndEvent;
	void EventCall(int _Frame);
};

enum class SamplerOption
{
	LINEAR,
	POINT,
};

enum class PivotType
{
	Center,
	Bottom,
	Left,
	Top,
	Right,
};

// Ό³Έν :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
	friend class GameEngineFrameAnimation;
public:
	static std::shared_ptr<class GameEngineSampler> DefaultSampler;

	// constrcuter destructer
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();

	// delete Function
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator=(GameEngineSpriteRenderer&& _Other) noexcept = delete;

	inline void SetAutoScaleRatio(float _Ratio)
	{
		AutoScaleRatio.X = _Ratio;
		AutoScaleRatio.Y = _Ratio;
	}

	inline void SetAutoScaleRatio(const float4& _Ratio)
	{
		AutoScaleRatio = _Ratio;
	}

	bool IsRight()
	{
		return 0 < AutoScaleRatio.X;
	}

	void RightFlip()
	{
		AutoScaleRatio.X = abs(AutoScaleRatio.X);
	}

	void LeftFlip()
	{
		AutoScaleRatio.X = -abs(AutoScaleRatio.X);
	}

	void Flip()
	{
		AutoScaleRatio.X = -AutoScaleRatio.X;
	}

	void SetSprite(std::string_view _Name, unsigned int Index = 0);
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, float _Inter = 0.1f, unsigned int _Start = -1, unsigned int _End = -1, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false, unsigned int _FrameIndex = 0);

	void AutoSpriteSizeOn();
	void AutoSpriteSizeOff();

	void SetSamplerState(SamplerOption _Option);

	bool IsCurAnimationEnd()
	{
		return CurFrameAnimations->IsEnd;
	}

	bool IsCurAnimation(std::string_view _AnimationName)
	{
		return _AnimationName == CurFrameAnimations->AnimationName ;
	}

	inline unsigned int GetCurIndex() const
	{
		return CurFrameAnimations->CurIndex;
	}

	void SetStartEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetEndEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameEngineSpriteRenderer*)> _Function);
	
	void AnimationPauseSwitch();
	void AnimationPauseOn();
	void AnimationPauseOff();

	void SetPivotType(PivotType _Type);
	void SetImageScale(const float4& _Scale);
	void AddImageScale(const float4& _Scale);

	static void SetDefaultSampler(std::string_view _SamplerName);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;

private:
	int Index = 0;
	std::shared_ptr<GameEngineSprite> Sprite;
	std::shared_ptr<class GameEngineSampler> Sampler;
	SpriteData CurSprite;

	/////////// Animation Member
	bool IsPause = false;
	bool IsImageSize = false; // Rendering ImageSize
	float4 AutoScaleRatio = { 1.0f, 1.0f, 1.0f };// Rendering ScaleRation
	std::shared_ptr<GameEngineFrameAnimation> CurFrameAnimations;
	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>> FrameAnimations;

	float4 Pivot = { 0.5f, 0.5f };
	GameEngineTransform ImageTransform;
};

