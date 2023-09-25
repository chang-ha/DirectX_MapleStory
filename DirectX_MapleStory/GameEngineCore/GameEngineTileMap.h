#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSpriteRenderer.h"

class Tile
{
public:
	SpriteData Data;
	int Index = -1;
};

class CreateTileParameter
{
public:
	size_t TileCountX = 10;
	size_t TileCountY = 10;
	float4 TileScale = { 50, 50 };
	std::string_view SpriteName = "";
};


class SetTileParameterIndex
{
public:
	size_t X = -1;
	size_t Y = -1;
	unsigned int Index = 0;
	std::string_view SpriteName = "";
};

class SetTileParameterPos
{
public:
	float4 Pos;
	unsigned int Index = 0;
	std::string_view SpriteName = "";

	SetTileParameterPos(float4 _Pos, unsigned int _Index = 0, std::string_view _SpriteName = "")
		: Pos(_Pos), Index(_Index), SpriteName(_SpriteName)
	{
	}
};


// Ό³Έν :
class GameEngineTileMap : public GameEngineSpriteRenderer
{
public:
	// constrcuter destructer
	GameEngineTileMap();
	~GameEngineTileMap();

	// delete Function
	GameEngineTileMap(const GameEngineTileMap& _Other) = delete;
	GameEngineTileMap(GameEngineTileMap&& _Other) noexcept = delete;
	GameEngineTileMap& operator=(const GameEngineTileMap& _Other) = delete;
	GameEngineTileMap& operator=(GameEngineTileMap&& _Other) noexcept = delete;

	//                       100           100            50 50 
	void CreateTileMap(const CreateTileParameter& _Parameter);
	// void SetTile(size_t _TileCountX, size_t _TileCountY, float4 TileScale);

	//size_t X;
	//size_t Y;
	//unsigned int Index = 0;
	//std::string_view SpriteName = "";
	void SetTileIndex(const SetTileParameterIndex& _Parameter);

	void SetTilePos(const SetTileParameterPos& _Parameter);

	void ExpandRenderedTileMap(int _Size)
	{
		TileMapExpansionSize = _Size;
	}

	std::shared_ptr<class GameEngineSampler> Sampler;

	float4 PosToIndex(float4 _Pos)
	{
		float4 Index = { static_cast<float>(_Pos.iX() / TileData.TileScale.iX()), static_cast<float>(_Pos.iY() / TileData.TileScale.iY()) };
		return Index;
	}

	float4 IndexToPos(float4 _Index)
	{
		float4 Pos = { _Index.X * TileData.TileScale.X, _Index.Y * TileData.TileScale.Y };
		return Pos;
	}

protected:
	void Start();
	void Render(GameEngineCamera* _Camera, float _Delta) override;

private:
	CreateTileParameter TileData;

	std::shared_ptr<GameEngineSprite> DefaultSprite;

	std::vector<std::vector<Tile>> Tiles;

	int TileMapExpansionSize = 0;
};

