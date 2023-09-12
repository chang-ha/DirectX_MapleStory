#pragma once
#include "GameEngineResources.h"
// Ό³Έν :
class GameEngineBlend : public GameEngineResources<GameEngineBlend>
{
public:
	// constrcuter destructer	
	GameEngineBlend();
	~GameEngineBlend();


	// delete Function
	GameEngineBlend(const GameEngineBlend& _Other) = delete;
	GameEngineBlend(GameEngineBlend&& _Other) noexcept = delete;
	GameEngineBlend& operator=(const GameEngineBlend& _Other) = delete;
	GameEngineBlend& operator=(GameEngineBlend&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineBlend> Create(std::string_view _Name, const D3D11_BLEND_DESC& _Desc)
	{
		std::shared_ptr<GameEngineBlend> Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting();

protected:
	void ResCreate(const D3D11_BLEND_DESC& _Desc);

private:
	D3D11_BLEND_DESC Desc = {};
	ID3D11BlendState* State = nullptr;
	float4 Factor;
	UINT Mask = 0xffffffff;
};

