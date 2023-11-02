#pragma once
#include "GameEngineTexture.h"
#include "GameEngineRenderer.h"

// 설명 :
class GameEngineRenderTarget : public GameEngineResources<GameEngineRenderTarget>
{
public:
	friend GameEngineDevice;
	static bool IsDepth;

	// constrcuter destructer
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	// delete Function
	GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineRenderTarget> Create(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color = float4::BLUE)
	{
		std::shared_ptr<GameEngineRenderTarget> NewRes = GameEngineResources::CreateRes();
		NewRes->AddNewTexture(_Texture, _Color);
		return NewRes;
	}

	static std::shared_ptr<GameEngineRenderTarget> Create()
	{
		std::shared_ptr<GameEngineRenderTarget> NewRes = GameEngineResources::CreateRes();
		return NewRes;
	}

	void Clear();
	void Setting();

	void SetClearColor(const float4& _Color, int _Index = 0)
	{
		ClearColor[_Index] = _Color;
	}

	void CreateDepthTexture(int _Index = 0);

	void AddNewTexture(DXGI_FORMAT _Format, float4 _Scale, float4 _Color);

	void AddNewTexture(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color);

	void Copy(unsigned int ThisTarget, std::shared_ptr<GameEngineRenderTarget> _Target, unsigned int _CopyTarget = 0);

	void Merge(unsigned int ThisTarget, std::shared_ptr<GameEngineRenderTarget> _Target, unsigned int _CopyTarget = 0);

protected:

private:
	static GameEngineRenderUnit MergeUnit;
	static void MergeRenderUnitInit();

	std::vector<std::shared_ptr<GameEngineTexture>> Textures;
	std::vector<ID3D11RenderTargetView*> RTV; // <= 텍스처를 랜더타겟으로 삼을수 있게 만드는 권한
	std::vector<ID3D11ShaderResourceView*> SRV; // <= 텍스처를 리소스로 사용할수 있는 권한
	std::vector<float4> ClearColor; // <= 텍스처를 랜더타겟으로 삼을수 있게 만드는 권한
	std::vector<D3D11_VIEWPORT> ViewPorts;

	std::shared_ptr<GameEngineTexture> DepthTexture;
};