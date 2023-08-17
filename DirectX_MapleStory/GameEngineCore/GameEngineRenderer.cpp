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
	// 메인카메라에 들어갔다.
	SetViewCameraSelect(0);

	// 카메라를 찾아서 들어가야 합니다.
	// 카메를 찾으려면? GameEngineLevel
	// Level부터 찾아야해.
	// Level누가 들고 있죠? 나를 들고 있는 Actor가 들고 있어.
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	std::shared_ptr<GameEngineCamera> Camera = Level->GetCamera(_Order);

	if (nullptr == Camera)
	{
		MsgBoxAssert("카메라가 존재하지 않는데 랜더러를 넣으려고 했습니다.");
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
				// 0바이트부터 시작하는
				Data.AlignedByteOffset = 0;
				// 16바이트짜리 자료형이야.
				Data.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				// 버텍스 데이터용 레이아웃이야
				// 점세팅의 구조를 설명하기 위한 레이아웃이야.
				Data.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

				// 지금은 알아도 크게 의미 없음
				Data.SemanticIndex = 0;
				Data.InputSlot = 0;
				Data.InstanceDataStepRate = 0;
				ArrLayOutInfo.push_back(Data);
			}

			{
				D3D11_INPUT_ELEMENT_DESC Data;
				Data.SemanticName = "COLOR";
				// 16바이트부터 시작하는
				Data.AlignedByteOffset = 16;
				// 16바이트짜리 자료형이야.
				Data.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				// 버텍스 데이터용 레이아웃이야
				// 점세팅의 구조를 설명하기 위한 레이아웃이야.
				Data.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;

				// 지금은 알아도 크게 의미 없음
				Data.SemanticIndex = 0;
				Data.InputSlot = 0;
				Data.InstanceDataStepRate = 0;
				ArrLayOutInfo.push_back(Data);
			}

			LayOut->ResCreate(ArrLayOutInfo, VertexShader);

			// 레이아웃
		}

		if (nullptr != VertexShader)
		{
			VertexShader->Setting();
		}
	}
}