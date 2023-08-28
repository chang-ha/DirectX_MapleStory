#pragma once
#include "GameEngineResources.h"

// Ό³Έν :
class GameEngineSampler : public GameEngineResources<GameEngineSampler>
{
public:
	// constructer destructer
	GameEngineSampler();
	~GameEngineSampler();

	// delete function
	GameEngineSampler(const GameEngineSampler& _Ohter) = delete;
	GameEngineSampler(GameEngineSampler&& _Ohter) noexcept = delete;
	GameEngineSampler& operator=(const GameEngineSampler& _Other) = delete;
	GameEngineSampler& operator=(GameEngineSampler&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineSampler> Create(std::string_view _Name, const D3D11_SAMPLER_DESC& _Desc)
	{
		std::shared_ptr<GameEngineSampler> Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);

protected:
	void ResCreate(const D3D11_SAMPLER_DESC& _Desc);

private:
	D3D11_SAMPLER_DESC Desc = {};
	ID3D11SamplerState* State = nullptr;
};

