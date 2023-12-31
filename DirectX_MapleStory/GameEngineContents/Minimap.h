#pragma once 
#include "ContentLevel.h"

class MinimapStruct
{
	friend class Minimap;
	std::shared_ptr<GameEngineUIRenderer> LT = nullptr;
	std::shared_ptr<GameEngineUIRenderer> RT = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MT = nullptr;
	std::shared_ptr<GameEngineUIRenderer> LB = nullptr;
	std::shared_ptr<GameEngineUIRenderer> RB = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MB = nullptr;
	std::shared_ptr<GameEngineUIRenderer> LM = nullptr;
	std::shared_ptr<GameEngineUIRenderer> RM = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Minimap = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MiniPlayer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> MapName1 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> MapName2 = nullptr;
};

class Minimap : public GameEngineActor
{
public:
	// constructer destructer
	Minimap();
	~Minimap();

	// delete function
	Minimap(const Minimap& _Ohter) = delete;
	Minimap(Minimap&& _Ohter) noexcept = delete;
	Minimap& operator=(const Minimap& _Other) = delete;
	Minimap& operator=(Minimap&& _Other) noexcept = delete;
	
	static void CreateMinimap(std::string_view _MinimapName, std::string_view _MinimapTextName)
	{
		std::shared_ptr<Minimap> CurMinimap = ContentLevel::CurContentLevel->CreateActor<Minimap>(UpdateOrder::UI);
		CurMinimap->MinimapName = _MinimapName;
		CurMinimap->Init(_MinimapName, _MinimapTextName);
		CurMinimap->Transform.SetWorldPosition({0, 0, 1});
	}

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	std::string MinimapName = "";
	float4 MinimapScale = float4::ZERO;
	float4 FullMinimapScale = float4::ZERO;
	float4 PlayerPos = float4::ZERO;
	float4 RealMapScale = float4::ZERO;
	MinimapStruct MinimapObject;
	void Init(std::string_view _MinimapName, std::string_view _MinimapTextName);
};

