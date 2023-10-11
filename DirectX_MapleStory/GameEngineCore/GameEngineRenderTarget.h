#pragma once
#include "GameEngineTexture.h"

// 설명 :
class GameEngineRenderTarget : public GameEngineResources<GameEngineRenderTarget>
{
public:
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
		NewRes->ClearColor.push_back(_Color);
		NewRes->Textures.push_back(_Texture);

		if (nullptr == _Texture->GetRTV())
		{
			MsgBoxAssert("랜더타겟 뷰가 존재하지 않습니다.");
		}

		NewRes->RTV.push_back(_Texture->GetRTV());
		return NewRes;
	}

	void Clear();
	void Setting();

	void SetClearColor(const float4& _Color, int _Index = 0)
	{
		ClearColor[_Index] = _Color;
	}

	void CreateDepthTexture(int _Index = 0);

protected:

private:
	std::vector<std::shared_ptr<GameEngineTexture>> Textures;
	std::vector<ID3D11RenderTargetView*> RTV; // <= 텍스처를 랜더타겟으로 삼을수 있게 만드는 권한
	std::vector<float4> ClearColor; // <= 텍스처를 랜더타겟으로 삼을수 있게 만드는 권한

	std::shared_ptr<GameEngineTexture> DepthTexture;
};