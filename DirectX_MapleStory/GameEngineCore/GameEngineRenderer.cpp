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

int A = 0;

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	{
		// �Ʒ��ִ� �̳༮���� ���ҽ����
		// �̳༮���� ����

		std::vector<float4> Vertex;
		Vertex.resize(4 * 6);

		float4 BaseVertexs[4];

		BaseVertexs[0] = { -0.5f, -0.5f, -0.5f, 1.0f };
		BaseVertexs[1] = { 0.5f, -0.5f, -0.5f, 1.0f };
		BaseVertexs[2] = { 0.5f, 0.5f, -0.5f, 1.0f };
		BaseVertexs[3] = { -0.5f, 0.5f, -0.5f, 1.0f };

		// �ո�
		Vertex[0] = BaseVertexs[0];
		Vertex[1] = BaseVertexs[1];
		Vertex[2] = BaseVertexs[2];
		Vertex[3] = BaseVertexs[3];

		// �޸�
		Vertex[4] = float4::VectorRotationToDegX(BaseVertexs[0], 180.0f);
		Vertex[5] = float4::VectorRotationToDegX(BaseVertexs[1], 180.0f);
		Vertex[6] = float4::VectorRotationToDegX(BaseVertexs[2], 180.0f);
		Vertex[7] = float4::VectorRotationToDegX(BaseVertexs[3], 180.0f);

		// �����̳� ������
		Vertex[8] = float4::VectorRotationToDegY(BaseVertexs[0], 90.0f);
		Vertex[9] = float4::VectorRotationToDegY(BaseVertexs[1], 90.0f);
		Vertex[10] = float4::VectorRotationToDegY(BaseVertexs[2], 90.0f);
		Vertex[11] = float4::VectorRotationToDegY(BaseVertexs[3], 90.0f);

		// �����̳� ������
		Vertex[12] = float4::VectorRotationToDegY(BaseVertexs[0], -90.0f);
		Vertex[13] = float4::VectorRotationToDegY(BaseVertexs[1], -90.0f);
		Vertex[14] = float4::VectorRotationToDegY(BaseVertexs[2], -90.0f);
		Vertex[15] = float4::VectorRotationToDegY(BaseVertexs[3], -90.0f);

		// ���ų� �Ʒ�
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

		float4x4 ViewPort4x4;
		ViewPort4x4.ViewPort(1280.0f, 720.0f, 0.0f, 0.0f);


		HDC DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();

		for (size_t indexCount = 0; indexCount < Index.size() / 3; indexCount++)
		{
			int ArrIndex[3];
			ArrIndex[0] = Index[indexCount * 3 + 0];
			ArrIndex[1] = Index[indexCount * 3 + 1];
			ArrIndex[2] = Index[indexCount * 3 + 2];

			const TransformData& TransDataRef = Transform.GetConstTransformDataRef();

			float4 Trifloat4[3];
			std::vector<POINT> Tri;
			Tri.resize(3);
			for (size_t VertexCount = 0; VertexCount < Tri.size(); VertexCount++)
			{
				// ��ġ�� �����������ؼ� ���� ���·� �������״ٰ� �Ѵ�.
				float4 WorldPoint = Vertex[ArrIndex[VertexCount]];

				//��ȯ���� ���� �� �Ѱ��� �ΰ�.
				WorldPoint = WorldPoint * TransDataRef.WorldViewPorjectionMatrix;

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
	}
}