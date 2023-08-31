#pragma once
#include <GameEngineCore\GameEngineActor.h>

class ContentMap : public GameEngineActor
{
public:
	// constructer destructer
	ContentMap();
	~ContentMap();

	// delete function
	ContentMap(const ContentMap& _Ohter) = delete;
	ContentMap(ContentMap&& _Ohter) noexcept = delete;
	ContentMap& operator=(const ContentMap& _Other) = delete;
	ContentMap& operator=(ContentMap&& _Other) noexcept = delete;

	void Init(std::string_view _MapName);
	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineTexture> MapCollisionTexture = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> MapRenderer = nullptr;
};

