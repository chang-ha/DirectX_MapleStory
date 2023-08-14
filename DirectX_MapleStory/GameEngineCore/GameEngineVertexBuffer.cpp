#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBuffer::GameEngineVertexBuffer()
{
}

GameEngineVertexBuffer::~GameEngineVertexBuffer()
{
}

void GameEngineVertexBuffer::Setting()
{
	// ID3D11Buffer* Arr[1];

	if (nullptr == Buffer)
	{
		MsgBoxAssert("����������� ���� ���ؽ� ���۸� ������ ���� �����ϴ�.");
	}


	// ���ؽ����۸� ������ �־��ټ� �ִ�.
	GameEngineCore::MainDevice.GetContext()->IASetVertexBuffers(0, 1, &Buffer, &VertexSize, &Offset);
}

void GameEngineVertexBuffer::ResCreate(const void* _Data, size_t _VertexSize, size_t _VertexCount)
{
	size_t VertexSize = _VertexSize;
	size_t VertexCount = _VertexCount;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferInfo.ByteWidth = static_cast<UINT>(VertexSize * VertexCount);
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	if (S_OK != GameEngineCore::MainDevice.GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgBoxAssert("���ؽ� ���� ������ �����߽��ϴ�.");
		return;
	}
}