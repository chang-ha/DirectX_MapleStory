#pragma once
#include "GameEngineResources.h"

// 범위가 잡히면
// 범위를 어떻게 잡고 그 범위의 색깔을 어떻게 칠할지에 대한 리소스의 종합 색깔에 관련된 리소스를 모아 놓을것을
// 머티리얼 이라고 합니다.
class GameEngineMaterial : public GameEngineResources<GameEngineMaterial>
{
public:
	// constructer destructer
	GameEngineMaterial();
	~GameEngineMaterial();

	// delete function
	GameEngineMaterial(const GameEngineMaterial& _Ohter) = delete;
	GameEngineMaterial(GameEngineMaterial&& _Ohter) noexcept = delete;
	GameEngineMaterial& operator=(const GameEngineMaterial& _Other) = delete;
	GameEngineMaterial& operator=(GameEngineMaterial&& _Other) noexcept = delete;

	static std::shared_ptr<class GameEngineMaterial> Create(const std::string_view& _Name)
	{
		std::shared_ptr<class GameEngineMaterial> NewRes = GameEngineResources::CreateRes(_Name);
		return NewRes;
	}

	void VertexShader();
	void Rasterizer();
	void PixelShader();
	void Blend();
	void DepthStencil();

	void SetVertexShader(const std::string_view& _Value);
	void SetRasterizer(const std::string_view& _Value);
	void SetPixelShader(const std::string_view& _Value);
	void SetBlendState(const std::string_view& _Value);
	// void SetDepthState(const std::string_view& _Value);

	std::shared_ptr<class GameEngineVertexShader> GetVertexShader()
	{
		return VertexShaderPtr;
	}

	std::shared_ptr<class GameEnginePixelShader> GetPixelShader()
	{
		return PixelShaderPtr;
	}

protected:

private:
	std::shared_ptr<class GameEngineVertexShader> VertexShaderPtr;
	std::shared_ptr<class GameEngineRasterizer> RasterizerPtr;
	std::shared_ptr<class GameEnginePixelShader> PixelShaderPtr;
	std::shared_ptr<class GameEngineBlend> BlendStatePtr;
	std::shared_ptr<class GameEngineDepthStencil> DepthStencilPtr;
};

