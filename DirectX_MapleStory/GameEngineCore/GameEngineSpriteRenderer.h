#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"

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

protected:
	void Render(GameEngineCamera* _Camera, float _Delta) override;

private:
	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteDataInfo CurSprite;
};

