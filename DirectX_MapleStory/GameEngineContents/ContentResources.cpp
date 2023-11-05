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
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineContentsShader");
		Dir.MoveChild("GameEngineContentsShader");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineShader::AutoCompile(File);
		}
	}

	{
		D3D11_DEPTH_STENCIL_DESC Desc = { 0, };
		Desc.DepthEnable = true;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		Desc.StencilEnable = false;
		std::shared_ptr<GameEngineDepthStencil> DepthStencil = GameEngineDepthStencil::Create("LessEqualDepth", Desc);
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FadeObjectEffect");
		Mat->SetVertexShader("FadeObjectEffect_VS");
		Mat->SetPixelShader("FadeObjectEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}
}
