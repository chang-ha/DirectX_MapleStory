#pragma once
#include "GameEngineTexture.h"

// ���� :
class GameEngineRenderTarget : public GameEngineResources<GameEngineRenderTarget>
{
public:
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
		_Texture->CreateRenderTargetView();
		NewRes->RTV.push_back(_Texture->GetRTV());
		return NewRes;
	}

	void Clear();
	void Setting();

	void SetClearColor(const float4& _Color, int _Index = 0)
	{
		ClearColor[_Index] = _Color;
	}

protected:

private:
	std::vector<std::shared_ptr<GameEngineTexture>> Textures;
	std::vector<ID3D11RenderTargetView*> RTV; // <= �ؽ�ó�� ����Ÿ������ ������ �ְ� ����� ����
	std::vector<float4> ClearColor; // <= �ؽ�ó�� ����Ÿ������ ������ �ְ� ����� ����
};