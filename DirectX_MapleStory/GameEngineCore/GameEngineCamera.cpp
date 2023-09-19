#include "PreCompile.h"
#include "GameEngineCamera.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"
#include "GameEngineCore.h"

GameEngineCamera::GameEngineCamera() 
{
}

GameEngineCamera::~GameEngineCamera() 
{
}

void GameEngineCamera::Start()
{
	GameEngineActor::Start();

	GameEngineLevel* Level = GetLevel();

	if (nullptr == Level)
	{
		MsgBoxAssert("Level이 nullptr입니다");
		return;
	}

	// Level->Cameras[CameraOrder] = GetDynamic_Cast_This<GameEngineCamera>();
}

void GameEngineCamera::Update(float _Delta)
{
	GameEngineActor::Update(_Delta);

	float4 Position = Transform.GetWorldPosition();
	float4 Forward = Transform.GetWorldForwardVector();
	float4 Up = Transform.GetWorldUpVector();

	Transform.LookToLH(Position, Forward, Up);

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	switch (ProjectionType)
	{
	case Perspective:
		Transform.PerspectiveFovLHDeg(FOV, WindowScale.X, WindowScale.Y, Near, Far);
		break;
	case Orthographic:
		Transform.OrthographicLH(WindowScale.X, WindowScale.Y, Near, Far);
		break;
	default:
		break;
	}
}

void GameEngineCamera::SetCameraOrder(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	if (nullptr == Level)
	{
		MsgBoxAssert("Level이 nullptr입니다");
		return;
	}

	if (Level->Cameras[CameraOrder] == shared_from_this())
	{
		Level->Cameras[CameraOrder] = nullptr;
	}
	CameraOrder = _Order;
	Level->Cameras[CameraOrder] = GetDynamic_Cast_This<GameEngineCamera>();
}

void GameEngineCamera::Render(float _DeltaTime)
{
	//  랜더러가 없으면 continue;
	if (true == Renderers.empty())
	{
		return;
	}

	//x + 1;
	//y + 1;
	//z + 1;

	//for (size_t i = 0; i < 1280 * 720; i++)
	//{
	//	GameEngineCore::MainWindow.GetBackBuffer()->GetColor(0, {0, 0});
	//}

	for (std::pair<const int, std::list<std::shared_ptr<class GameEngineRenderer>>>& RendererPair : Renderers)
	{
		std::list<std::shared_ptr<class GameEngineRenderer>>& RendererList = RendererPair.second;

		for (std::shared_ptr<class GameEngineRenderer> & Renderer : RendererList)
		{
			if (false == Renderer->IsUpdate())
			{
				continue;
			}

			Renderer->Transform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());
			Renderer->Render(this, _DeltaTime);
		}
	}
}

void GameEngineCamera::AllReleaseCheck()
{
	// Map자료구조에 아무것도 안들어있으면 Release를 할 필요가 없음
	if (true == Renderers.empty())
	{
		return;
	}

	for (std::pair<const int, std::list<std::shared_ptr<GameEngineRenderer>>>& _Pair : Renderers)
	{
		std::list<std::shared_ptr<GameEngineRenderer>>& Group = _Pair.second;

		std::list<std::shared_ptr<GameEngineRenderer>>::iterator Start = Group.begin();
		std::list<std::shared_ptr<GameEngineRenderer>>::iterator End = Group.end();

		for (; Start != End;)
		{
			if (false == (*Start)->IsDeath())
			{
				(*Start)->AllReleaseCheck();
				++Start;
				continue;
			}

			Start = Group.erase(Start);
		}
	}
}

float4 GameEngineCamera::GetWorldMousePos2D()
{
	// 월드라고 하는 세상은 화면과 관련이 없었다.
	// 그런데 관련있게 됐다.
	// 로컬 => 월드(크자이공부) => 뷰 => 프로젝션 => 뷰포트(스크린좌표)
	// 역행렬을 곱하면 이전 차원으로 돌아갈 수 있다
	float4 MousePos = GameEngineCore::MainWindow.GetMousePos();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	float4x4 ViewPort;
	ViewPort.ViewPort(WinScale.X, WinScale.Y, 0, 0);

	// 스크린 => 프로젝션으로 이동
	MousePos *= ViewPort.InverseReturn();

	// 프로젝션 => 뷰로 이동
	MousePos *= Transform.GetConstTransformDataRef().ProjectionMatrix.InverseReturn();

	// 뷰 => 월드로
	MousePos *= Transform.GetConstTransformDataRef().ViewMatrix.InverseReturn();

	return MousePos;
}
