#include "PreCompile.h"

#include <GameEngineCore\GameEngineDepthStencil.h>
#include <GameEngineCore\GameEngineVertex.h>
#include "ContentResources.h"

ContentResources::ContentResources()
{

}

ContentResources::~ContentResources()
{

}

void ContentResources::ContentResourcesInit()
{
	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		Desc.StencilEnable = false;
		std::shared_ptr<GameEngineDepthStencil> DepthStencil = GameEngineDepthStencil::Create("LessEqualDepth", Desc);
	}
}
