#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
// #include "GameEngineShader.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineSprite.h"
#include "GameEngineBlend.h"

void GameEngineDevice::ResourcesInit()
{
	// �������ؿ��� �������ִ� ���� �������� ���ҽ����� ���⿡�� ������� �̴ϴ�.
	// �⺻ �Ž�
	// �⺻ �ؽ�ó

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineCoreShader");
		Dir.MoveChild("GameEngineCoreShader");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });
		for (size_t i = 0; i < Files.size(); i++)
		{
			// GameEngineVertexShader::Load(Files[i].GetStringPath(), "ColorShader_VS");
			GameEngineFile& File = Files[i];
			GameEngineShader::AutoCompile(File);
		}
	}

	{
		// ������ ���̴��� ���δ� ���δ� �ε��ϴ� �ڵ带 ģ��.
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("GameEngineResources");
		Dir.MoveChild("GameEngineResources");
		Dir.MoveChild("Textrure");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
		GameEngineSprite::CreateSingle("NSet.png");
	}

	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4);

		Vertex[0] = { { -0.5f, 0.5f, 0.0f, 1.0f }, {0.0f, 0.0f} };
		Vertex[1] = { { 0.5f, 0.5f, 0.0f, 1.0f } , {1.0f, 0.0f} };
		Vertex[2] = { { 0.5f, -0.5f, 0.0f, 1.0f }  , {1.0f, 1.0f} };
		Vertex[3] = { { -0.5f, -0.5f, 0.0f, 1.0f } , {0.0f, 1.0f} };

		GameEngineVertexBuffer::Create("Rect", Vertex);

		std::vector<unsigned int> Index =
		{
			0, 1, 2,
			0, 2, 3
		};

		GameEngineIndexBuffer::Create("Rect", Index);
	}

	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4);

		Vertex[0] = { { -1.0f, 1.0f, 0.0f, 1.0f }, {0.0f, 0.0f} };
		Vertex[1] = { { 1.0f, 1.0f, 0.0f, 1.0f },  {1.0f, 0.0f} };
		Vertex[2] = { { 1.0f, -1.0f, 0.0f, 1.0f },   {1.0f, 1.0f} };
		Vertex[3] = { { -1.0f, -1.0f, 0.0f, 1.0f },  {0.0f, 1.0f} };

		GameEngineVertexBuffer::Create("FullRect", Vertex);

		std::vector<unsigned int> Index =
		{
			0, 1, 2,
			0, 2, 3
		};

		GameEngineIndexBuffer::Create("FullRect", Index);
	}

	{
		// BytePadding����� CPU�� GPU���� ���̰� ���� �� ������ �̻��ϸ� ���� üũ
		GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", ShaderType::Vertex, 0);
	}

	{
		D3D11_RASTERIZER_DESC Desc = {};
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		// Desc.DepthClipEnable = TRUE;
		std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Create("EngineRasterizer", Desc);
	}

	{
		D3D11_BLEND_DESC Desc = {};
		// ���̹��۶�� �Ͱ� ������ �ֽ��ϴ�. << �� ����
		// ���� ���̹��� �߰��Ǹ� ���
		// Desc.AlphaToCoverageEnable
		
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // src����
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("EngineBlend", Desc);
	}

	{
		D3D11_SAMPLER_DESC Desc = {};
		// �Ϲ����� �������� <= ��������.
		// D3D11_FILTER_MIN_MAG_MIP_
		// �� �Ӹʿ��� �������ö� �� ������ ������� �������ڴ�.
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> Rasterizer = GameEngineSampler::Create("LINEAR", Desc);
	}


	{
		D3D11_SAMPLER_DESC Desc = {};
		// �ִ��������
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		std::shared_ptr<GameEngineSampler> Rasterizer = GameEngineSampler::Create("POINT", Desc);
	}
}