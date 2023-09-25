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
#include "GameEngineConstantBuffer.h"
#include "GameEngineBlend.h"

GameEngineRenderer::GameEngineRenderer()
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::Start()
{
	// DataTransform 에 나의 Transform을 넣어줌 (Pivot기능을 위해 Transform을 2가지 사용하기 위해)
	// DataTransform = &Transform;

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

	std::shared_ptr<GameEngineCamera> FindCamera = Level->GetCamera(_Order);

	if (nullptr == FindCamera)
	{
		MsgBoxAssert("카메라가 존재하지 않는데 랜더러를 넣으려고 했습니다.");
		return;
	}

	Camera = FindCamera.get();
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
}

void GameEngineRenderer::SetRenderOrder(int _Order)
{
	if (nullptr == Camera)
	{
		MsgBoxAssert("카메라가 존재하지 않는 랜더러입니다. 카메라를 먼저 지정해주세요.");
		return;
	}

	Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	GameEngineObject::SetOrder(_Order);
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
}

void GameEngineRenderer::SetCameraOrder(int _Order)
{
	SetViewCameraSelect(_Order);
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	ResSetting();
	Draw();
}

void GameEngineRenderer::ResSetting()
{
	Mesh->InputAssembler1();
	Material->VertexShader();
	LayOut->Setting();
	Mesh->InputAssembler2();
	Material->Rasterizer();
	Material->PixelShader();
	Material->Blend();
	ShaderResHelper.AllShaderResourcesSetting();

	// 애는 솔직히 랜더 타겟이 가져가야 합니다.
	D3D11_VIEWPORT ViewPort = {};
	ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
	ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
	ViewPort.MinDepth = 0.0f;
	ViewPort.MaxDepth = 1.0f;
	ViewPort.TopLeftX = 0.0f;
	ViewPort.TopLeftY = 0.0f;
	GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);

	//////////////// BackBufferRenderTarget <- 실제 윈도우창에 보이게 하는 RenderTarget(스왑체인에서 Texture를 통해 얻어낸 RenderTarget)
	std::shared_ptr<GameEngineRenderTarget> BackBufferRenderTarget = GameEngineCore::GetBackBufferRenderTarget();
	if (nullptr != BackBufferRenderTarget)
	{
		BackBufferRenderTarget->Setting();
	}

	//float4x4 WorldViewProjection = Transform.GetWorldViewProjectionMatrix();

	////////////////// VertexBuffer
	//std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Find("Rect");
	//if (nullptr != VertexBuffer)
	//{
	//	VertexBuffer->Setting();
	//}
	//////////////////

	////////////////// VertexShader
	//std::shared_ptr<GameEngineVertexShader> VertexShader = GameEngineVertexShader::Find("TextureShader_VS");
	//if (nullptr != VertexShader && nullptr != VertexBuffer && nullptr == LayOut)
	//{
	//	LayOut = std::make_shared<GameEngineInputLayOut>();
	//	LayOut->ResCreate(VertexBuffer, VertexShader);
	//}

	//if (nullptr != LayOut)
	//{
	//	LayOut->Setting();
	//}

	//if (nullptr != VertexShader)
	//{
	//	VertexShader->Setting();
	//}
	//////////////////

	//////////////////// ConstantBuffer
	////std::shared_ptr<GameEngineConstantBuffer> ConstantBuffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData");

	////const TransformData& Data = Transform.GetConstTransformDataRef();

	////if (nullptr != ConstantBuffer)
	////{
	////	const TransformData& Data = DataTransform->GetConstTransformDataRef();
	////	ConstantBuffer->ChangeData(Data);
	////	ConstantBuffer->Setting(0);
	////}

	////////////////////

	////////////////// IndexBuffer
	//std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("Rect");
	//if (nullptr != IndexBuffer)
	//{
	//	IndexBuffer->Setting();
	//}

	//GameEngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//////////////////

	////////////////// VierPort
	//D3D11_VIEWPORT ViewPort = {};

	//// DirectX에서 자동으로 X, Y값에 /2를 해줌
	//ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
	//ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
	//ViewPort.MinDepth = 0.0f;
	//ViewPort.MaxDepth = 1.0f;
	//ViewPort.TopLeftX = 0.0f;
	//ViewPort.TopLeftY = 0.0f;

	//GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);
	//////////////////

	////////////////// Rasterizer 
	//std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
	//if (nullptr != Rasterizer)
	//{
	//	Rasterizer->Setting();
	//}
	//////////////////

	////////////////// PixelShader
	//std::shared_ptr<GameEnginePixelShader> PixelShader = GameEnginePixelShader::Find("TextureShader_PS");
	//if (nullptr != PixelShader)
	//{
	//	PixelShader->Setting();
	//}
	//////////////////

	////////////////// Blending
	//std::shared_ptr<class GameEngineBlend> Blend = GameEngineBlend::Find("EngineBlend");
	//if (nullptr != Blend)
	//{
	//	Blend->Setting();
	//}
	//////////////////

	////////////////// BackBufferRenderTarget <- 실제 윈도우창에 보이게 하는 RenderTarget(스왑체인에서 Texture를 통해 얻어낸 RenderTarget)
	//std::shared_ptr<GameEngineRenderTarget> BackBufferRenderTarget = GameEngineCore::GetBackBufferRenderTarget();
	//if (nullptr != BackBufferRenderTarget)
	//{
	//	BackBufferRenderTarget->Setting();
	//}
}

void GameEngineRenderer::SetMesh(std::string_view _Name)
{
	Mesh = GameEngineMesh::Find(_Name);

	if (nullptr == Mesh)
	{
		MsgBoxAssert("존재하지 않는 매쉬를 세팅하려고 했습니다.");
	}

	// LayOut은 VertexBuffer와 VertexShader가 필요한데 각각 매쉬와 머티리얼이 들고있기 때문에
	// 아래와 같이 LayOut은 따로 만들어줌
	if (nullptr == LayOut && nullptr != Material)
	{
		LayOut = std::make_shared<GameEngineInputLayOut>();
		LayOut->ResCreate(Mesh->GetVertexBuffer(), Material->GetVertexShader());
	}
}

void GameEngineRenderer::SetMaterial(std::string_view _Name)
{
	Material = GameEngineMaterial::Find(_Name);

	if (nullptr == Material)
	{
		MsgBoxAssert("존재하지 않는 매쉬를 세팅하려고 했습니다.");
	}

	if (nullptr == LayOut && nullptr != Mesh)
	{
		LayOut = std::make_shared<GameEngineInputLayOut>();
		LayOut->ResCreate(Mesh->GetVertexBuffer(), Material->GetVertexShader());
	}

	// 버텍스 쉐이더와 픽셀쉐이더가 다 들어있는 상태다.

	// 랜더러의 쉐이더 리소스 헬퍼에
	// 버텍스와 픽셀쉐이더의 리소스정보들을 복사 받습니다.
	ShaderResHelper.ShaderResCopy(Material->GetVertexShader().get());
	ShaderResHelper.ShaderResCopy(Material->GetPixelShader().get());

	// 이걸 회사의 약속.

	if (ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		const TransformData& Data = Transform.GetConstTransformDataRef();
		ShaderResHelper.SetConstantBufferLink("TransformData", Data);
	}
}


void GameEngineRenderer::Draw()
{
	Mesh->Draw();
}

//void GameEngineRenderer::Draw()
//{
//	////////////////	
//	std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("Rect");
//	if (nullptr == IndexBuffer)
//	{
//		return;
//	}
//
//	GameEngineCore::GetContext()->DrawIndexed(IndexBuffer->GetIndexCount(), 0, 0);
//	//////////////// 그리기
//}


