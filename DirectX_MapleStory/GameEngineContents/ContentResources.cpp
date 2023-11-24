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
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FadeInObjectEffect");
		Mat->SetVertexShader("FadeObjectEffect_VS");
		Mat->SetPixelShader("FadeInObjectEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("FadeOutObjectEffect");
		Mat->SetVertexShader("FadeObjectEffect_VS");
		Mat->SetPixelShader("FadeOutObjectEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("DamageSkinTexture");
		Mat->SetVertexShader("DamageSkinShader_VS");
		Mat->SetPixelShader("DamageSkinShader_PS");
		Mat->SetDepthState("AlwaysDepth");
		Mat->SetRasterizer("EngineRasterizer");
	}

	//{
	//	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("BackGroundActor");
	//	Mat->SetVertexShader("BackGroundShader_VS");
	//	Mat->SetPixelShader("BackGroundShader_PS");
	//	// Mat->SetDepthState("AlwaysDepth");
	//	// Mat->SetRasterizer("EngineRasterizer");
	//}
}
