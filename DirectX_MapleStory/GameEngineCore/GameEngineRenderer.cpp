#include "PreCompile.h"
#include "GameEngineRenderer.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"

#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

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

void GameEngineRenderer::Render(float _Delta)
{

	{
		// 로컬과 월드의 차이입니다.
		// 사각형을 만들기 위해서 점을 4개 만들었습니다.
		// 바로 월드로 바로만든것
		// 로컬이 존재하지 않는다.

		// 다이렉트 x로

		// 로컬상태
		std::vector<float4> Vertex;
		Vertex.resize(4 * 6);

		float4 BaseVertexs[4];

		BaseVertexs[0] = { -0.5f, -0.5f, -0.5f, 1.0f };
		BaseVertexs[1] = { 0.5f, -0.5f, -0.5f, 1.0f };
		BaseVertexs[2] = { 0.5f, 0.5f, -0.5f, 1.0f };
		BaseVertexs[3] = { -0.5f, 0.5f, -0.5f, 1.0f };

		// 앞면
		Vertex[0] = BaseVertexs[0];
		Vertex[1] = BaseVertexs[1];
		Vertex[2] = BaseVertexs[2];
		Vertex[3] = BaseVertexs[3];

		// 뒷면
		Vertex[4] = float4::VectorRotationToDegX(BaseVertexs[0], 180.0f);
		Vertex[5] = float4::VectorRotationToDegX(BaseVertexs[1], 180.0f);
		Vertex[6] = float4::VectorRotationToDegX(BaseVertexs[2], 180.0f);
		Vertex[7] = float4::VectorRotationToDegX(BaseVertexs[3], 180.0f);

		// 왼쪽이나 오른쪽
		Vertex[8] = float4::VectorRotationToDegY(BaseVertexs[0], 90.0f);
		Vertex[9] = float4::VectorRotationToDegY(BaseVertexs[1], 90.0f);
		Vertex[10] = float4::VectorRotationToDegY(BaseVertexs[2], 90.0f);
		Vertex[11] = float4::VectorRotationToDegY(BaseVertexs[3], 90.0f);

		// 왼쪽이나 오른쪽
		Vertex[12] = float4::VectorRotationToDegY(BaseVertexs[0], -90.0f);
		Vertex[13] = float4::VectorRotationToDegY(BaseVertexs[1], -90.0f);
		Vertex[14] = float4::VectorRotationToDegY(BaseVertexs[2], -90.0f);
		Vertex[15] = float4::VectorRotationToDegY(BaseVertexs[3], -90.0f);

		// 위거나 아래
		Vertex[16] = float4::VectorRotationToDegX(BaseVertexs[0], 90.0f);
		Vertex[17] = float4::VectorRotationToDegX(BaseVertexs[1], 90.0f);
		Vertex[18] = float4::VectorRotationToDegX(BaseVertexs[2], 90.0f);
		Vertex[19] = float4::VectorRotationToDegX(BaseVertexs[3], 90.0f);

		Vertex[20] = float4::VectorRotationToDegX(BaseVertexs[0], -90.0f);
		Vertex[21] = float4::VectorRotationToDegX(BaseVertexs[1], -90.0f);
		Vertex[22] = float4::VectorRotationToDegX(BaseVertexs[2], -90.0f);
		Vertex[23] = float4::VectorRotationToDegX(BaseVertexs[3], -90.0f);



		std::vector<int> Index = 
		{
			0, 1, 2, 
			0, 2, 3,
			0 + 4, 1 + 4, 2 + 4,
			0 + 4, 2 + 4, 3 + 4,
			0 + 8, 1 + 8, 2 + 8,
			0 + 8, 2 + 8, 3 + 8,
			0 + 12, 1 + 12, 2 + 12,
			0 + 12, 2 + 12, 3 + 12,
			0 + 16, 1 + 16, 2 + 16,
			0 + 16, 2 + 16, 3 + 16,
			0 + 20, 1 + 20, 2 + 20,
			0 + 20, 2 + 20, 3 + 20,
		};

		// 0   1
		// 3   2


		// 첫번째 방법
		// Vertex[0] = { -0.5f, -0.5f }; 16
		// Vertex[1] = { 0.5f, -0.5f }; 16
		// Vertex[2] = { 0.5f, 0.5f }; 16
		// 
		// Vertex1[0] = { -0.5f, -0.5f }; 16
		// Vertex1[1] = { 0.5f, -0.5f }; 16
		// Vertex1[2] = { 0.5f, 0.5f }; 16 
		// 
		// 두번째 방법
		// Vertex[0] = { -0.5f, -0.5f }; 16
		// Vertex[1] = { 0.5f, -0.5f }; 16
		// Vertex[2] = { 0.5f, 0.5f }; 16
		// Vertex[3] = { -0.5f, 0.5f }; 16
		// 
		// short Arr[2][3] = {{0, 1, 2}, {0, 2, 3}}; 24


		// 월드의 영역
		static float4 Scale = { 100.0f, 100.0f, 100.0f }; // 크기
		static float4 Rotation = { 0, 0, 0 }; // 회전
		static float4 Position = { 0.0f, 0.0f, 0.0f }; // 이동


		float CamSpeed = 300.0f;
		if (GameEngineInput::IsPress('A'))
		{
			Position += float4::LEFT * _Delta * CamSpeed;
		}

		if (GameEngineInput::IsPress('D'))
		{
			Position += float4::RIGHT * _Delta * CamSpeed;
		}

		if (GameEngineInput::IsPress('W'))
		{
			Position += float4::UP * _Delta * CamSpeed;
		}

		if (GameEngineInput::IsPress('S'))
		{
			Position += float4::DOWN * _Delta * CamSpeed;
		}

		if (GameEngineInput::IsPress('Q'))
		{
			Rotation.Z += 360.0f * _Delta;
		}

		if (GameEngineInput::IsPress('E'))
		{
			Rotation.Z -= 360.0f * _Delta;
		}

		float4x4 Scale4x4;
		float4x4 Rotation4x4X;
		float4x4 Rotation4x4Y;
		float4x4 Rotation4x4Z;
		float4x4 Rotation4x4;
		float4x4 Position4x4;


		Scale4x4.Scale(Scale);

		Rotation4x4X.RotationXDeg(Rotation.X);
		Rotation4x4Y.RotationYDeg(Rotation.Y);
		Rotation4x4Z.RotationZDeg(Rotation.Z);
		Rotation4x4 = Rotation4x4X * Rotation4x4Y * Rotation4x4Z;

		Position4x4.Position(Position);

		// 행렬의 곱샘은 교환법칙이 성립하지 않습니다.
		float4x4 World4x4 = Scale4x4 * Rotation4x4 * Position4x4;


		// 카메라의 영역

		static float4 EyePos = {0.0f, 0.0f, -500.0f, 1.0f};
		static float4 EyeDir = { 0.0f, 0.0f, 1.0f, 1.0f };
		// View4x4.LookToLH
		// float4 EyeLookPos = { 0.0f, 0.0f, 0.0f, 1.0f };
		// 내부에서 계산된다.
		// float4 EyeDir = EyePos - EyeLookPos;
		static float4 EyeUp = { 0.0f, 1.0f, 0.0f, 1.0f };

		float MoveSpeed = 300.0f;
		if (GameEngineInput::IsPress(VK_NUMPAD4))
		{
			EyePos += float4::LEFT * _Delta * MoveSpeed;
		}

		if (GameEngineInput::IsPress(VK_NUMPAD6))
		{
			EyePos += float4::RIGHT * _Delta * MoveSpeed;
		}

		if (GameEngineInput::IsPress(VK_NUMPAD8))
		{
			EyePos += float4::FORWARD * _Delta * MoveSpeed;
		}

		if (GameEngineInput::IsPress(VK_NUMPAD5))
		{
			EyePos += float4::BACKWARD * _Delta * MoveSpeed;
		}

		if (GameEngineInput::IsPress(VK_NUMPAD7))
		{
			EyeDir.VectorRotationToDegY(360.0f * _Delta);
		}

		if (GameEngineInput::IsPress(VK_NUMPAD9))
		{
			EyeDir.VectorRotationToDegY(-360.0f * _Delta);
		}

		float4x4 View4x4;
		View4x4.LookToLH(EyePos, EyeDir, EyeUp);

		float4x4 Projection4x4;
		Projection4x4.OrthographicLH(1280.0f, 720.0f, 1000.0f, 0.1f);

		float4x4 ViewPort4x4;
		ViewPort4x4.ViewPort(1280.0f, 720.0f, 0.0f, 0.0f);

		float4x4 WorldViewProjection4x4 = World4x4 * View4x4 * Projection4x4;

		HDC DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();

		for (size_t indexCount = 0; indexCount < Index.size() / 3; indexCount++)
		{
			int ArrIndex[3];
			ArrIndex[0] = Index[indexCount * 3 + 0];
			ArrIndex[1] = Index[indexCount * 3 + 1];
			ArrIndex[2] = Index[indexCount * 3 + 2];

			float4 Trifloat4[3];
			std::vector<POINT> Tri;
			Tri.resize(3);
			for (size_t VertexCount = 0; VertexCount < Tri.size(); VertexCount++)
			{
				// 위치를 더해줌으로해서 월드 상태로 이전시켰다고 한다.
				float4 WorldPoint = Vertex[ArrIndex[VertexCount]];

				//변환식은 이제 딱 한가지 인것.
				WorldPoint = WorldPoint * WorldViewProjection4x4;

				WorldPoint /= WorldPoint.W;
				WorldPoint.W = 1.0f;

				WorldPoint = WorldPoint * ViewPort4x4;

				Trifloat4[VertexCount] = WorldPoint;


				Tri[VertexCount] = WorldPoint.WindowPOINT();
			}
			float4 Dir0 = Trifloat4[0] - Trifloat4[1];
			float4 Dir1 = Trifloat4[1] - Trifloat4[2];
			float4 Check = float4::Cross3D(Dir1, Dir0);
			if (Check.Z < 1.0f)
			{
				continue;
			}
			Polygon(DC, &Tri[0], static_cast<int>(Tri.size()));
		}

		// 화면에 3d물체를 구별하고 선별하기 위한 변환은 다 끝났고
		// 어떤 모니터에 뿌릴까만이 남게 된다. 최종적으로 화면에 어떻게 뿌릴것인가만이 남아있다.

	}
}