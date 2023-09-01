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

// Ό³Έν :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
	friend class GameEngineFrameAnimation;
public:
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
		AutoScaleRatio = _Ratio;
	}

	void SetSprite(std::string_view _Name, unsigned int Index = 0);
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, float _Inter = 0.1f, unsigned int _Start = -1, unsigned int _End = -1, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false);

	void AutoSpriteSizeOn();
	void AutoSpriteSizeOff();

	void SetSamplerState(SamplerOption _Option);

	bool IsCurAnimationEnd()
	{
		return CurFrameAnimations->IsEnd;
	}

	void SetStartEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetEndEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameEngineSpriteRenderer*)> _Function);

protected:
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;

private:
	int Index = 0;
	std::shared_ptr<GameEngineSprite> Sprite;
	std::shared_ptr<class GameEngineSampler> Sampler;
	SpriteData CurSprite;

	/////////// Animation Member
	bool IsImageSize = false; // Rendering ImageSize
	float AutoScaleRatio = 1.0f; // Rendering ScaleRation
	std::shared_ptr<GameEngineFrameAnimation> CurFrameAnimations;
	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>> FrameAnimations;
};

