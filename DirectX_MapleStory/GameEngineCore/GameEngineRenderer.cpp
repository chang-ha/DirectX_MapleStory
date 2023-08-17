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
		std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Find("Rect");
		if (nullptr != VertexBuffer)
		{
			VertexBuffer->Setting();
		}

		std::shared_ptr<GameEngineVertexShader> VertexShader = GameEngineVertexShader::Find("ColorShader_VS");
		if (nullptr != VertexShader && nullptr != VertexBuffer && nullptr == LayOut)
		{
			LayOut = std::make_shared<GameEngineInputLayOut>();

			std::vector<D3D11_INPUT_ELEMENT_DESC> ArrLayOutInfo;

			{
				D3D11_INPUT_ELEMENT_DESC Data;
				Data.SemanticName = "POSITION";
				// 0����Ʈ���� �����ϴ�
				Data.AlignedByteOffset = 0;
				// 16����Ʈ¥�� �ڷ����̾�.
				Data.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				// ���ؽ� �����Ϳ� ���̾ƿ��̾�
				// �������� ������ �����ϱ� ���� ���̾ƿ��̾�.
				Data.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

				// ������ �˾Ƶ� ũ�� �ǹ� ����
				Data.SemanticIndex = 0;
				Data.InputSlot = 0;
				Data.InstanceDataStepRate = 0;
				ArrLayOutInfo.push_back(Data);
			}

			{
				D3D11_INPUT_ELEMENT_DESC Data;
				Data.SemanticName = "COLOR";
				// 16����Ʈ���� �����ϴ�
				Data.AlignedByteOffset = 16;
				// 16����Ʈ¥�� �ڷ����̾�.
				Data.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				// ���ؽ� �����Ϳ� ���̾ƿ��̾�
				// �������� ������ �����ϱ� ���� ���̾ƿ��̾�.
				Data.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

				// ������ �˾Ƶ� ũ�� �ǹ� ����
				Data.SemanticIndex = 0;
				Data.InputSlot = 0;
				Data.InstanceDataStepRate = 0;
				ArrLayOutInfo.push_back(Data);
			}

			LayOut->ResCreate(ArrLayOutInfo, VertexShader);

			// ���̾ƿ�
		}

		if (nullptr != VertexShader)
		{
			VertexShader->Setting();
		}
	}
}