#pragma once
#include "GameEngineResources.h"

class GameEngineRasterizer : public GameEngineResources<GameEngineRasterizer>
{
public:
	// constructer destructer
	GameEngineRasterizer();
	~GameEngineRasterizer();

	// delete function
	GameEngineRasterizer(const GameEngineRasterizer& _Ohter) = delete;
	GameEngineRasterizer(GameEngineRasterizer&& _Ohter) noexcept = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer& operator=(GameEngineRasterizer&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineRasterizer> Create(const std::string_view& _Name, const D3D11_RASTERIZER_DESC& _Desc)
	{
		std::shared_ptr<GameEngineRasterizer> Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting();
protected:
	void ResCreate(const D3D11_RASTERIZER_DESC& _Desc);

private:
	D3D11_RASTERIZER_DESC Desc = {};
	ID3D11RasterizerState* State = nullptr;
};

