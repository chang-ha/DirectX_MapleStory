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
	unsigned int Start = -1;
	unsigned int End = -1;
	unsigned int CurIndex = 0;
	float CurTime = 0.0f; // CurAnimationTime
	std::vector<int> Index;

	std::string AnimationName = "";
	std::string SpriteName = "";
	std::shared_ptr<GameEngineSprite> Sprite;
};
// Ό³Έν :
class GameEngineSpriteRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();

	// delete Function
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator=(GameEngineSpriteRenderer&& _Other) noexcept = delete;

	void SetSprite(std::string_view _Name, unsigned int Index = 0);
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, float _Inter = 0.1f, unsigned int _Start = -1, unsigned int _End = -1, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName);

	void AutoSpriteSizeOn();
	void AutoSpriteSizeOff();

protected:
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;

private:
	int Index = 0;
	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteData CurSprite;

	/////////// Animation Member
	bool IsImageSize = false; // Rendering ImageSize
	std::shared_ptr<GameEngineFrameAnimation> CurFrameAnimations;
	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>> FrameAnimations;
};

