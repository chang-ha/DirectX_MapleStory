#include "PreCompile.h"
#include "GameEngineCamera.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"
#include "GameEngineCore.h"
#include "GameEngineRenderTarget.h"

float GameEngineCamera::FreeRotSpeed = 180.0f;
float GameEngineCamera::FreeSpeed = 200.0f;

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
	ZoomValue = 1.0f;

	if (nullptr == Level)
	{
		MsgBoxAssert("Level�� nullptr�Դϴ�");
		return;
	}

	IsFreeCameraValue = false;
}

void GameEngineCamera::Update(float _Delta)
{
	GameEngineActor::Update(_Delta);

	// ��ũ�� ��ǥ�迡���� ���콺 ��ġ�� ���� ����ī�޶� �þ߹����� �ٲ�
	ScreenMousePos = GameEngineCore::MainWindow.GetMousePos();
	ScreenMouseDir = ScreenMousePrevPos - ScreenMousePos;
	ScreenMouseDirNormal = ScreenMouseDir.NormalizeReturn();
	ScreenMousePrevPos = ScreenMousePos;

	if (false == IsFreeCameraValue)
	{
		return;
	}

	if (GameEngineInput::IsDown('O', this))
	{
		switch (ProjectionType)
		{
		case EPROJECTIONTYPE::Perspective:
			ProjectionType = EPROJECTIONTYPE::Orthographic;
			break;
		case EPROJECTIONTYPE::Orthographic:
			ProjectionType = EPROJECTIONTYPE::Perspective;
			break;
		default:
			break;
		}
	}

	float Speed = FreeSpeed;

	if (GameEngineInput::IsPress(VK_LSHIFT, this))
	{
		Speed *= 5.0f;
	}

	if (GameEngineInput::IsPress('A', this))
	{
		Transform.AddLocalPosition(Transform.GetWorldLeftVector() * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D', this))
	{
		Transform.AddLocalPosition(Transform.GetWorldRightVector() * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W', this))
	{
		Transform.AddLocalPosition(Transform.GetWorldForwardVector() * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S', this))
	{
		Transform.AddLocalPosition(Transform.GetWorldBackVector() * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q', this))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('E', this))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress(VK_RBUTTON, this))
	{
		float4 Dir = ScreenMouseDirNormal;

		Transform.AddWorldRotation({ -Dir.Y, -Dir.X });
	}
}

void GameEngineCamera::SetCameraOrder(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	if (nullptr == Level)
	{
		MsgBoxAssert("Level�� nullptr�Դϴ�");
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
	CameraUpdate(_DeltaTime);

	//  �������� ������ continue;
	if (true == Renderers.empty())
	{
		return;
	}

	GameEngineCore::GetBackBufferRenderTarget()->Setting();

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

		if (true == ZSortMap.contains(RendererPair.first))
		{
			RendererList.sort([](std::shared_ptr<class GameEngineRenderer> _Left, std::shared_ptr<class GameEngineRenderer> _Right)
				{
					return _Left->Transform.GetWorldPosition().Z > _Right->Transform.GetWorldPosition().Z;
				});
		}

		if (true == YSortMap.contains(RendererPair.first))
		{
			RendererList.sort([](std::shared_ptr<class GameEngineRenderer> _Left, std::shared_ptr<class GameEngineRenderer> _Right)
				{
					return _Left->Transform.GetWorldPosition().Y > _Right->Transform.GetWorldPosition().Y;
				});
		}

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
	// Map�ڷᱸ���� �ƹ��͵� �ȵ�������� Release�� �� �ʿ䰡 ����
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
	// ������ �ϴ� ������ ȭ��� ������ ������.
	// �׷��� �����ְ� �ƴ�.
	// ���� => ����(ũ���̰���) => �� => �������� => ����Ʈ(��ũ����ǥ)
	// ������� ���ϸ� ���� �������� ���ư� �� �ִ�
	float4 MousePos = GameEngineCore::MainWindow.GetMousePos();
	float4 WinScale = GameEngineCore::MainWindow.GetScale();

	float4x4 ViewPort;
	ViewPort.ViewPort(WinScale.X, WinScale.Y, 0, 0);

	// ��ũ�� => ������������ �̵�
	MousePos *= ViewPort.InverseReturn();

	// �������� => ��� �̵�
	MousePos *= Transform.GetConstTransformDataRef().ProjectionMatrix.InverseReturn();

	// �� => �����
	MousePos *= Transform.GetConstTransformDataRef().ViewMatrix.InverseReturn();

	return MousePos;
}

void GameEngineCamera::CameraUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsDown(VK_OEM_4, this)) // '['
	{
		IsFreeCameraValue = !IsFreeCameraValue;

		if (true == IsFreeCameraValue)
		{
			GameEngineInput::IsOnlyInputObject(this);
			PrevProjectionType = ProjectionType;
			ProjectionType = EPROJECTIONTYPE::Perspective;
			OriginData = Transform.GetConstTransformDataRef();
		}
		else
		{
			GameEngineInput::IsObjectAllInputOn();
			ProjectionType = PrevProjectionType;
			Transform.SetTransformData(OriginData);
		}
	}

	if (true == IsFreeCameraValue)
	{
		// �����ൿ ī�޶�� �ൿ
	}
	else if (nullptr != Target)
	{
		// ���� ����ٴϴ� �༮�� �ִٸ�
		Transform.SetWorldPosition(Target->GetWorldPosition() + Pivot);
	}

	// ī�޶� �� ����� �ڿ� ������� ����

	float4 Position = Transform.GetWorldPosition();
	float4 Forward = Transform.GetWorldForwardVector();
	float4 Up = Transform.GetWorldUpVector();

	Transform.LookToLH(Position, Forward, Up);

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	WindowScale *= ZoomValue;

	switch (ProjectionType)
	{
	case EPROJECTIONTYPE::Perspective:
		Transform.PerspectiveFovLHDeg(FOV, WindowScale.X, WindowScale.Y, Near, Far);
		break;
	case EPROJECTIONTYPE::Orthographic:
		Transform.OrthographicLH(WindowScale.X, WindowScale.Y, Near, Far);
		break;
	default:
		break;
	}

}
