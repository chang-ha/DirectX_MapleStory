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
	SetCameraOrder(ECAMERAORDER::Main);

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

	if (nullptr != Camera)
	{
		Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
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
	RenderBaseInfoValue.RendererScreenPos = GetScreenPosition();
	for (size_t i = 0; i < Units.size(); i++)
	{
		Units[i]->ResSetting();
		Units[i]->Draw();
	}
}

void GameEngineRenderer::Update(float _Delta)
{
	RenderBaseInfoValue.DeltaTime = _Delta;
	RenderBaseInfoValue.AccDeltaTime += _Delta;
}

std::shared_ptr<GameEngineRenderUnit> GameEngineRenderer::CreateAndFindRenderUnit(int _Index)
{
	Units.resize(_Index + 1);

	// 있으면
	if (nullptr != Units[_Index])
	{
		//리턴
		return Units[_Index];
	}

	// 없으면 만든다.
	Units[_Index] = std::make_shared<GameEngineRenderUnit>();
	Units[_Index]->SetParentRenderer(this);
	return Units[_Index];
}

// 이제 RenderUnit에서 ResSetting담당
//void GameEngineRenderer::ResSetting()
//{
//	Mesh->InputAssembler1();
//	Material->VertexShader();
//	LayOut->Setting();
//	Mesh->InputAssembler2();
//	Material->Rasterizer();
//	Material->PixelShader();
//	Material->Blend();
//	ShaderResHelper.AllShaderResourcesSetting();
//
//	// 애는 솔직히 랜더 타겟이 가져가야 합니다.
//	D3D11_VIEWPORT ViewPort = {};
//	ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
//	ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
//	ViewPort.MinDepth = 0.0f;
//	ViewPort.MaxDepth = 1.0f;
//	ViewPort.TopLeftX = 0.0f;
//	ViewPort.TopLeftY = 0.0f;
//	GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);
//
//	//////////////// BackBufferRenderTarget <- 실제 윈도우창에 보이게 하는 RenderTarget(스왑체인에서 Texture를 통해 얻어낸 RenderTarget)
//	std::shared_ptr<GameEngineRenderTarget> BackBufferRenderTarget = GameEngineCore::GetBackBufferRenderTarget();
//	if (nullptr != BackBufferRenderTarget)
//	{
//		BackBufferRenderTarget->Setting();
//	}
//
//	//float4x4 WorldViewProjection = Transform.GetWorldViewProjectionMatrix();
//
//	////////////////// VertexBuffer
//	//std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Find("Rect");
//	//if (nullptr != VertexBuffer)
//	//{
//	//	VertexBuffer->Setting();
//	//}
//	//////////////////
//
//	////////////////// VertexShader
//	//std::shared_ptr<GameEngineVertexShader> VertexShader = GameEngineVertexShader::Find("TextureShader_VS");
//	//if (nullptr != VertexShader && nullptr != VertexBuffer && nullptr == LayOut)
//	//{
//	//	LayOut = std::make_shared<GameEngineInputLayOut>();
//	//	LayOut->ResCreate(VertexBuffer, VertexShader);
//	//}
//
//	//if (nullptr != LayOut)
//	//{
//	//	LayOut->Setting();
//	//}
//
//	//if (nullptr != VertexShader)
//	//{
//	//	VertexShader->Setting();
//	//}
//	//////////////////
//
//	//////////////////// ConstantBuffer
//	////std::shared_ptr<GameEngineConstantBuffer> ConstantBuffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData");
//
//	////const TransformData& Data = Transform.GetConstTransformDataRef();
//
//	////if (nullptr != ConstantBuffer)
//	////{
//	////	const TransformData& Data = DataTransform->GetConstTransformDataRef();
//	////	ConstantBuffer->ChangeData(Data);
//	////	ConstantBuffer->Setting(0);
//	////}
//
//	////////////////////
//
//	////////////////// IndexBuffer
//	//std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Find("Rect");
//	//if (nullptr != IndexBuffer)
//	//{
//	//	IndexBuffer->Setting();
//	//}
//
//	//GameEngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//	//////////////////
//
//	////////////////// VierPort
//	//D3D11_VIEWPORT ViewPort = {};
//
//	//// DirectX에서 자동으로 X, Y값에 /2를 해줌
//	//ViewPort.Width = GameEngineCore::MainWindow.GetScale().X;
//	//ViewPort.Height = GameEngineCore::MainWindow.GetScale().Y;
//	//ViewPort.MinDepth = 0.0f;
//	//ViewPort.MaxDepth = 1.0f;
//	//ViewPort.TopLeftX = 0.0f;
//	//ViewPort.TopLeftY = 0.0f;
//
//	//GameEngineCore::GetContext()->RSSetViewports(1, &ViewPort);
//	//////////////////
//
//	////////////////// Rasterizer 
//	//std::shared_ptr<GameEngineRasterizer> Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
//	//if (nullptr != Rasterizer)
//	//{
//	//	Rasterizer->Setting();
//	//}
//	//////////////////
//
//	////////////////// PixelShader
//	//std::shared_ptr<GameEnginePixelShader> PixelShader = GameEnginePixelShader::Find("TextureShader_PS");
//	//if (nullptr != PixelShader)
//	//{
//	//	PixelShader->Setting();
//	//}
//	//////////////////
//
//	////////////////// Blending
//	//std::shared_ptr<class GameEngineBlend> Blend = GameEngineBlend::Find("EngineBlend");
//	//if (nullptr != Blend)
//	//{
//	//	Blend->Setting();
//	//}
//	//////////////////
//
//	////////////////// BackBufferRenderTarget <- 실제 윈도우창에 보이게 하는 RenderTarget(스왑체인에서 Texture를 통해 얻어낸 RenderTarget)
//	//std::shared_ptr<GameEngineRenderTarget> BackBufferRenderTarget = GameEngineCore::GetBackBufferRenderTarget();
//	//if (nullptr != BackBufferRenderTarget)
//	//{
//	//	BackBufferRenderTarget->Setting();
//	//}
//}

void GameEngineRenderer::SetMesh(std::string_view _Name, int _Index /*= 0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit->SetMesh(_Name);
}

void GameEngineRenderer::SetMaterial(std::string_view _Name, int _Index /*= 0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	Unit->SetMaterial(_Name);

	if (Unit->ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		Unit->ShaderResHelper.SetConstantBufferLink("TransformData", Transform.GetConstTransformDataRef());
	}

	if (Unit->ShaderResHelper.IsConstantBuffer("RenderBaseInfo"))
	{
		Unit->ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	}

	SetMaterialEvent(_Name, _Index);
}

GameEngineShaderResHelper& GameEngineRenderer::GetShaderResHelper(int _Index /*= 0*/)
{
	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(_Index);
	return Unit->ShaderResHelper;
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

void GameEngineRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
{

}

float4 GameEngineRenderer::GetScreenPosition()
{
	float4x4 ViewPort;
	float4 ScreenPos = Transform.GetWorldPosition();
	float4 Scale = GameEngineCore::MainWindow.GetScale();
	ViewPort.ViewPort(Scale.X, Scale.Y, 0, 0);
	ScreenPos *= ViewPort.InverseReturn();
	ScreenPos *= Transform.GetConstTransformDataRef().ProjectionMatrix.InverseReturn();
	ScreenPos *= Transform.GetConstTransformDataRef().ViewMatrix.InverseReturn();
	return ScreenPos;
}