#include "PreCompile.h"
#include "GameEngineDevice.h"
#include "GameEngineVertex.h"

#include "GameEngineVertexBuffer.h"

void GameEngineDevice::ResourcesInit()
{
	// �������ؿ��� �������ִ� ���� �������� ���ҽ����� ���⿡�� ������� �̴ϴ�.
	// �⺻ �Ž�
	// �⺻ �ؽ�ó
	// ���⿡�� �ڱ� �ؽ�ó �ε�����������.

	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4 * 6);

		GameEngineVertex2D BaseVertexs[4];

		BaseVertexs[0] = { { -0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[1] = { { 0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[2] = { { 0.5f, 0.5f, -0.5f, 1.0f } };
		BaseVertexs[3] = { { -0.5f, 0.5f, -0.5f, 1.0f } };

		// �ո�
		Vertex[0] = BaseVertexs[0];
		Vertex[1] = BaseVertexs[1];
		Vertex[2] = BaseVertexs[2];
		Vertex[3] = BaseVertexs[3];

		// �޸�
		Vertex[4].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 180.0f);
		Vertex[5].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 180.0f);
		Vertex[6].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 180.0f);
		Vertex[7].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 180.0f);

		// �����̳� ������
		Vertex[8].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, 90.0f);
		Vertex[9].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, 90.0f);
		Vertex[10].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, 90.0f);
		Vertex[11].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, 90.0f);

		// �����̳� ������
		Vertex[12].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, -90.0f);
		Vertex[13].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, -90.0f);
		Vertex[14].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, -90.0f);
		Vertex[15].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, -90.0f);

		// ���ų� �Ʒ�
		Vertex[16].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 90.0f);
		Vertex[17].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 90.0f);
		Vertex[18].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 90.0f);
		Vertex[19].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 90.0f);

		Vertex[20].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, -90.0f);
		Vertex[21].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, -90.0f);
		Vertex[22].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, -90.0f);
		Vertex[23].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, -90.0f);

		GameEngineVertexBuffer::Create("Box", Vertex);
	}

	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4);

		GameEngineVertex2D BaseVertexs[4];

		BaseVertexs[0] = { { -0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[1] = { { 0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[2] = { { 0.5f, 0.5f, -0.5f, 1.0f } };
		BaseVertexs[3] = { { -0.5f, 0.5f, -0.5f, 1.0f } };

		GameEngineVertexBuffer::Create("Rect", Vertex);
	}
}