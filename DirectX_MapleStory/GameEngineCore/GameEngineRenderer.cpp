#include "PreCompile.h"

#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineCore.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::Start()
{
	// ����ī�޶� ����.
	SetViewCameraSelect(0);

	// ī�޶� ã�Ƽ� ���� �մϴ�.
	// ī�޸� ã������? GameEngineLevel
	// Level���� ã�ƾ���.
	// Level���� ��� ����? ���� ��� �ִ� Actor�� ��� �־�.
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	std::shared_ptr<GameEngineCamera> Camera = Level->GetCamera(_Order);

	if (nullptr == Camera)
	{
		MsgBoxAssert("ī�޶� �������� �ʴµ� �������� �������� �߽��ϴ�.");
		return;
	}

	Camera->Renderers[_Order].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
	ViewInfo[Camera.get()] = _Order;
}

 void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	{
		float4x4 WorldViewProjection = Transform.GetWorldViewPorjectionMatrix();

		//////////////// VertexBuffer
		std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Find("Rect");
		if (nullptr != VertexBuffer)
		{
			VertexBuffer->Setting();
		}
		////////////////

		//////////////// VertexShader
		std::shared_ptr<GameEngineVertexShader> VertexShader = GameEngineVertexShader::Find("ColorShader_VS");
		if (nullptr != VertexShader && nullptr != VertexBuffer && nullptr == LayOut)
		{
			LayOut = std::make_shared<GameEngineInputLayOut>();
			LayOut->ResCreate(VertexBuffer, VertexShader);
		}

		if (nullptr != LayOut)
		{
			LayOut->Setting();
		}

		if (nullptr != VertexShader)
		{
			VertexShader->Setting();
		}
		////////////////
		
		//////////////// IndexBuffer
		std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("Rect");
		if (nullptr != IndexBuffer)
		{
			IndexBuffer->Setting();
		}
		
		GameEngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		////////////////

		//////////////// VierPort
		D3D11_VIEWPORT ViewPort = {};

		// DirectX���� �ڵ����� X, Y���� /2�� ����
		ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
		ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
		ViewPort.MinDepth = 0.0f;
		ViewPort.MaxDepth = 1.0f;
		ViewPort.TopLeftX = 0.0f;
		ViewPort.TopLeftY = 0.0f;

		GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);
		////////////////

		//////////////// Rasterizer 
		std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
		if (nullptr != Rasterizer)
		{
			Rasterizer->Setting();
		}
		////////////////

		//////////////// PixelShader
		std::shared_ptr<GameEnginePixelShader> PixelShader = GameEnginePixelShader::Find("ColorShader_PS");
		if (nullptr != PixelShader)
		{
			PixelShader->Setting();
		}
		////////////////

		//////////////// BackBufferRenderTarget <- ���� ������â�� ���̰� �ϴ� RenderTarget(����ü�ο��� Texture�� ���� �� RenderTarget)
		std::shared_ptr<GameEngineRenderTarget> BackBufferRenderTarget = GameEngineCore::GetBackBufferRenderTarget();
		if (nullptr != BackBufferRenderTarget)
		{
			BackBufferRenderTarget->Setting();
		}
		////////////////	

		//////////////// �׸���
		GameEngineCore::GetContext()->DrawIndexed(6, 0, 0);

	}
}