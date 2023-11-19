#pragma once

#define GROUND_COLOR GameEngineColor(255, 0, 255, 255)
#define FLOOR_COLOR GameEngineColor(0, 255, 0, 255)
#define LADDER_COLOR GameEngineColor(255, 0, 0, 255)
#define PLAYER_MAX_HP 100
#define PLAYER_MAX_MP 100

// Ό³Έν :
class GlobalValue
{
public:
	static float SkillEffectAlpha;
	static float SkillVolume;
	static float HitVolume;

	// constrcuter destructer
	GlobalValue();
	~GlobalValue();

	// delete Function
	GlobalValue(const GlobalValue& _Other) = delete;
	GlobalValue(GlobalValue&& _Other) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _Other) = delete;
	GlobalValue& operator=(GlobalValue&& _Other) noexcept = delete;

	static float4 WinScale;
	static float4 GetDirectXWinScale()
	{
		float4 Scale = WinScale;
		Scale.Y *= -1.0f;
		return Scale;
	}
protected:

private:

};

