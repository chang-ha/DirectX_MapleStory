#include "PreCompile.h"
#include "GameEngineMaterial.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRasterizer.h"
#include "GameEngineBlend.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineRenderTarget.h"

GameEngineMaterial::GameEngineMaterial()
{
	// 레스터라이저나 Belnd는 보통 기본 레스터라이저나 Belnd를 많이 쓰기 때문에 일단 만들면 세팅
	RasterizerPtr = GameEngineRasterizer::Find("EngineRasterizer");
	BlendStatePtr = GameEngineBlend::Find("AlphaBlend");
	DepthStencilPtr = GameEngineDepthStencil::Find("EngineDepth");
}

GameEngineMaterial::~GameEngineMaterial()
{

}


void GameEngineMaterial::VertexShader()
{
	if (nullptr == VertexShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}

	VertexShaderPtr->Setting();
}

void GameEngineMaterial::Rasterizer()
{
	if (nullptr == RasterizerPtr)
	{
		MsgBoxAssert("존재하지 않는 레스터 라이저를 세팅하려고 했습니다.");
	}

	RasterizerPtr->Setting();
}

void GameEngineMaterial::PixelShader()
{
	if (nullptr == PixelShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 픽셀 쉐이더를 세팅하려고 했습니다.");
	}

	PixelShaderPtr->Setting();
}

void GameEngineMaterial::Blend()
{
	if (nullptr == BlendStatePtr)
	{
		MsgBoxAssert("존재하지 않는 블랜드를 세팅하려고 했습니다.");
	}

	BlendStatePtr->Setting();
}

void GameEngineMaterial::DepthStencil()
{
	if (false == GameEngineRenderTarget::IsDepth)
	{
		GameEngineCore::GetContext()->OMSetDepthStencilState(nullptr, 0);
		return;
	}

	if (nullptr == DepthStencilPtr)
	{
		MsgBoxAssert("존재하지 않는 깊이 체크 세팅을 세팅하려고 했습니다.");
	}

	DepthStencilPtr->Setting();
}

void GameEngineMaterial::SetVertexShader(const std::string_view& _Value)
{
	VertexShaderPtr = GameEngineVertexShader::Find(_Value);

	if (nullptr == VertexShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 버텍스 쉐이더를 세팅하려고 했습니다.");
	}
}

void GameEngineMaterial::SetRasterizer(const std::string_view& _Value)
{
	RasterizerPtr = GameEngineRasterizer::Find(_Value);

	if (nullptr == RasterizerPtr)
	{
		MsgBoxAssert("존재하지 않는 레스터 라이저를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineMaterial::SetPixelShader(const std::string_view& _Value)
{
	PixelShaderPtr = GameEnginePixelShader::Find(_Value);

	if (nullptr == PixelShaderPtr)
	{
		MsgBoxAssert("존재하지 않는 픽셀쉐이더를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineMaterial::SetBlendState(const std::string_view& _Value)
{
	BlendStatePtr = GameEngineBlend::Find(_Value);

	if (nullptr == BlendStatePtr)
	{
		MsgBoxAssert("존재하지 않는 블랜드를 세팅하려고 했습니다.");
		return;
	}
}

void GameEngineMaterial::SetDepthState(const std::string_view& _Value)
{
	DepthStencilPtr = GameEngineDepthStencil::Find(_Value);

	if (nullptr == DepthStencilPtr)
	{
		MsgBoxAssert("존재하지 않는 블랜드를 세팅하려고 했습니다.");
		return;
	}
}