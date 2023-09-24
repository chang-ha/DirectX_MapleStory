#pragma once
#include "GameEngineResources.h"

// 설명 :
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

	static std::shared_ptr<GameEngineSampler> Create(D3D11_FILTER _Filter, D3D11_TEXTURE_ADDRESS_MODE _Address)
	{
		// 해당 필터를 가진 Sampler가 없으면 만듦
		if (false == OptionSamplers.contains(_Filter))
		{
			OptionSamplers[_Filter];
		}

		std::map<D3D11_TEXTURE_ADDRESS_MODE, std::shared_ptr<GameEngineSampler>>& Add = OptionSamplers[_Filter];

		// 해당 Texture경계선옵션을 가지고 있으면 해당 Sampler를 리턴
		if (true == Add.contains(_Address))
		{
			return Add[_Address];
		}

		// 없으면 Sampler를 만듦
		D3D11_SAMPLER_DESC Desc = {};
		Desc.Filter = _Filter;
		Desc.AddressU = _Address;
		Desc.AddressV = _Address;
		Desc.AddressW = _Address;
		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> NewSampler = std::make_shared<GameEngineSampler>();
		NewSampler->ResCreate(Desc);
		Add[_Address] = NewSampler;
		return NewSampler;
	}

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);

protected:
	void ResCreate(const D3D11_SAMPLER_DESC& _Desc);

private:
	// Texture마다 Sampler를 가지려고 할 떄 만들때 같은 옵션인 Sampler는 중복으로 만들필요 없어서 만든 Sampler를 자료구조로 관리해 없으면 만들고 있으면 그냥 쓰게 만듦
	static std::map<D3D11_FILTER, std::map<D3D11_TEXTURE_ADDRESS_MODE, std::shared_ptr<GameEngineSampler>>> OptionSamplers;

	D3D11_SAMPLER_DESC Desc = {};
	ID3D11SamplerState* State = nullptr;
};

