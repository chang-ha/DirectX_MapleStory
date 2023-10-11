#pragma once
#include "GameEngineResources.h"
// 각 Texture가 Sampler를 들고있게 만듦
#include "GameEngineSampler.h"

#include "..\\GameEngineCore\\ThirdParty\\DirectXTex\\inc\\DirectXTex.h"

class GameEngineColor
{
public:
	static const GameEngineColor RED;

public:
	unsigned char R = 0;
	unsigned char G = 0;
	unsigned char B = 0;
	unsigned char A = 0;

	bool operator==(const GameEngineColor& _Other) const
	{
		// Compare Bit ( 0 == Same Bit)
		return memcmp(this, &_Other, sizeof(GameEngineColor)) == 0;
	}
};
// 설명 :
class GameEngineTexture : public GameEngineResources<GameEngineTexture>
{
public:
	// constrcuter destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	// 스왑체인에서 얻어온 백버퍼를 우리 리소스로 등록시켜서 사용할때.
	static std::shared_ptr<GameEngineTexture> Create(ID3D11Texture2D* _Res)
	{
		std::shared_ptr<GameEngineTexture> NewRes = CreateRes();
		NewRes->ResCreate(_Res);
		return NewRes;
	}

	// 내가 아무것도 없는 특정 포맷의 텍스처를 직접 만들고 싶을때.
	static std::shared_ptr<GameEngineTexture> Create(const D3D11_TEXTURE2D_DESC& _Desc)
	{
		std::shared_ptr<GameEngineTexture> NewRes = CreateRes();
		NewRes->ResCreate(_Desc);
		return NewRes;
	}

	// Texture를 Load할 때 Sampler옵션을 선택할 수 있음 (기본은 POINT, CLAMP)
	static std::shared_ptr<GameEngineTexture> Load(std::string_view _Path,
		D3D11_FILTER _Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT,
		D3D11_TEXTURE_ADDRESS_MODE _Address = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP)
	{
		GameEnginePath Path = _Path;
		return Load(Path.GetStringPath(), Path.GetFileName());
	}

	static std::shared_ptr<GameEngineTexture> Load(std::string_view _Path, std::string_view _Name,
		D3D11_FILTER _Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT,
		D3D11_TEXTURE_ADDRESS_MODE _Address = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP)
	{
		std::shared_ptr<GameEngineTexture> NewRes = CreateRes(_Name);
		NewRes->ResLoad(_Path);
		NewRes->Sampler = GameEngineSampler::Create(_Filter, _Address);
		return NewRes;
	}

	inline ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

	inline float4 GetScale()
	{
		return { static_cast<float>(Desc.Width), static_cast<float>(Desc.Height), 1.0f, 0.0f };
	}

	inline ID3D11ShaderResourceView* GetSRV()
	{
		return SRV;
	}

	inline ID3D11DepthStencilView* GetDSV()
	{
		return DSV;
	}

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);

	GameEngineColor GetColor(const float4& _Pos, GameEngineColor _DefaultColor)
	{
		return GetColor(_Pos.iX(), _Pos.iY(), _DefaultColor);
	}

	GameEngineColor GetColor(unsigned int _X, unsigned int _Y, GameEngineColor _DefaultColor);

	std::shared_ptr<GameEngineSampler> GetBaseSampler()
	{
		return Sampler;
	}

	// 랜더타겟 세팅용
	void CreateRenderTargetView();
	// 쉐이더 세팅용
	void CreateShaderResourceView();
	// 깊이버퍼 세팅용
	void CreateDepthStencilView();
protected:

private:
	D3D11_TEXTURE2D_DESC Desc; 

	ID3D11Texture2D* Texture2D = nullptr;
	ID3D11RenderTargetView* RTV = nullptr;
	ID3D11ShaderResourceView* SRV = nullptr;
	ID3D11DepthStencilView* DSV = nullptr;

	DirectX::TexMetadata Data;
	DirectX::ScratchImage Image;

	std::shared_ptr<GameEngineSampler> Sampler;
	void ResLoad(std::string_view _Path);
	void ResCreate(const D3D11_TEXTURE2D_DESC& Desc);
	void ResCreate(ID3D11Texture2D* _Res);
};

