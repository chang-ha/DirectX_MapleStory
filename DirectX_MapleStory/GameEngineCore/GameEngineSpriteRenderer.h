#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"

class GameEngineFrameAnimation
{
	friend class GameEngineSpriteRenderer;

public:
	void Reset();
	SpriteData Update(float _Delta);

	// float Inter = 0.0f; // AnimationSpeed
	bool Loop = true;
	bool IsEnd = false;
	int Start = -1;
	int End = -1;
	int InterIndex;
	int CurIndex;
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
public:
	std::vector<float> Inter; // AnimationSpeed
};

enum class PivotType
{
	Center,
	Top,
	RightUp,
	Right,
	RightBottom,
	Bottom,
	LeftBottom,
	Left,
	LeftTop,
};

enum class MaskMode
{
	StaticMask, // 스크린 좌표계로 마스크를 
	DynamicMask, // 스크린좌표계인데 랜더러의 위치에 따라서 마스크 위치를 변경한다.
};

struct SpriteRendererInfo
{
	int FlipLeft = 0;
	int FlipUp = 0;
	float Temp1;
	float Temp2;
};

struct ColorData
{
	float4 PlusColor = float4::ZERONULL; // 최종색상에 더한다.
	float4 MulColor = float4::ONE; // 최종색상에 곱한다.
};

// 설명 :
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
		SpriteRendererInfoValue.FlipLeft = 0;
	}

	void LeftFlip()
	{
		SpriteRendererInfoValue.FlipLeft = 1;
	}

	void UpFlip()
	{
		SpriteRendererInfoValue.FlipUp = 1;
	}

	void DownFlip()
	{
		SpriteRendererInfoValue.FlipUp = 0;
	}

	void SetSprite(std::string_view _Name, unsigned int Index = 0);
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, float _Inter = 0.1f, unsigned int _Start = -1, unsigned int _End = -1, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false, unsigned int _FrameIndex = 0);

	void AutoSpriteSizeOn();
	void AutoSpriteSizeOff();

	bool IsCurAnimationEnd()
	{
		return CurFrameAnimations->IsEnd;
	}

	bool IsCurAnimation(std::string_view _AnimationName)
	{
		return _AnimationName == CurFrameAnimations->AnimationName ;
	}

	std::shared_ptr<GameEngineFrameAnimation> FindAnimation(std::string_view _AnimationName)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

		if (false == FrameAnimations.contains(UpperName))
		{
			return nullptr;
		}

		return FrameAnimations[UpperName];
	}

	inline unsigned int GetCurIndex() const
	{
		return CurFrameAnimations->CurIndex;
	}

	std::shared_ptr<GameEngineFrameAnimation> CurAnimation()
	{
		return CurFrameAnimations;
	}

	inline GameEngineTransform& GetImageTransform()
	{
		return ImageTransform;
	}

	inline ColorData& GetColorData()
	{
		return ColorDataValue;
	}

	void SetStartEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetEndEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameEngineSpriteRenderer*)> _Function);
	
	void AnimationPauseSwitch();
	void AnimationPauseOn();
	void AnimationPauseOff();

	void SetSampler(std::string_view _Name);

	void SetPivotValue(const float4& _Value)
	{
		Pivot = _Value;
	}

	float4 GetPivotValue()
	{
		return Pivot;
	}

	void SetPivotType(PivotType _Type);
	void SetImageScale(const float4& _Scale);
	void AddImageScale(const float4& _Scale);
	void SetMaskTexture(std::string_view _Texture, MaskMode _Mask = MaskMode::StaticMask);

	void SetText(const std::string& _Font, const std::string& _Text, float _Scale = 20.0f, const float4& Color = float4::RED, FW1_TEXT_FLAG Flag = FW1_LEFT);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;
	void SetMaterialEvent(std::string_view _Name, int _Index) override;

private:
	int Index = 0;
	std::shared_ptr<GameEngineSprite> Sprite;
	std::shared_ptr<class GameEngineSampler> Sampler;
	SpriteData CurSprite;

	/////////// Animation Member
	bool IsPause = false;
	bool IsImageSize = false; // Rendering ImageSize
	bool IsUserSampler = true; // if using user Sampler, not auto sampler setting
	float4 AutoScaleRatio = { 1.0f, 1.0f, 1.0f };// Rendering ScaleRation
	std::shared_ptr<GameEngineFrameAnimation> CurFrameAnimations;
	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>> FrameAnimations;

	float4 Pivot = { 0.5f, 0.5f };
	GameEngineTransform ImageTransform;
	SpriteRendererInfo SpriteRendererInfoValue;
	ColorData ColorDataValue;
};

