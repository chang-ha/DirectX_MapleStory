#pragma once
#include <GameEngineCore\GameEngineActor.h>

class ContentMap : public GameEngineActor
{
	friend class ContentLevel;
public:
	static bool IsCollisionDebug;

	// constructer destructer
	ContentMap();
	~ContentMap();

	// delete function
	ContentMap(const ContentMap& _Ohter) = delete;
	ContentMap(ContentMap&& _Ohter) noexcept = delete;
	ContentMap& operator=(const ContentMap& _Other) = delete;
	ContentMap& operator=(ContentMap&& _Other) noexcept = delete;

	inline float4& GetMapScale()
	{
		return MapScale;
	}

	void InitMap(std::string_view _MapName);
	void InitMapCollision(std::string_view _MapName);
	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = GROUND_COLOR);

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	float4 MapScale = float4::ZERO;
	// std::string MapName = "";
	std::shared_ptr<GameEngineTexture> MapCollisionTexture = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> MapCollisionRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> MapRenderer = nullptr;
};

