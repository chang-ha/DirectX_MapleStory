#pragma once
#include "GameEngineResources.h"
// Ό³Έν :
class GameEngineDepthStencil : public GameEngineResources<GameEngineDepthStencil>
{
public:
	// constrcuter destructer
	GameEngineDepthStencil();
	~GameEngineDepthStencil();

	// delete Function
	GameEngineDepthStencil(const GameEngineDepthStencil& _Other) = delete;
	GameEngineDepthStencil(GameEngineDepthStencil&& _Other) noexcept = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil& _Other) = delete;
	GameEngineDepthStencil& operator=(GameEngineDepthStencil&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineDepthStencil> Create(std::string_view _Name, const D3D11_DEPTH_STENCIL_DESC& _Desc)
	{
		std::shared_ptr<GameEngineDepthStencil> Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting();

protected:
	void ResCreate(const D3D11_DEPTH_STENCIL_DESC& _Desc);

private:
	D3D11_DEPTH_STENCIL_DESC Desc = {};
	ID3D11DepthStencilState* State = nullptr;
};