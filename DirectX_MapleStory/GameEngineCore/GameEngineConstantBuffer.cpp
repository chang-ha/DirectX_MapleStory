#include "PreCompile.h"
#include "GameEngineConstantBuffer.h"

std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> GameEngineConstantBuffer::ConstantBuffers;

GameEngineConstantBuffer::GameEngineConstantBuffer()
{
}

GameEngineConstantBuffer::~GameEngineConstantBuffer()
{
}

void GameEngineConstantBuffer::ResCreate(int _ByteSize)
{
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferInfo.ByteWidth = _ByteSize;

	// Transform�����͸� �� �����Ӹ��� ��� ���� �ٲ���� �ϱ� ������ WRITE, DYNAMIC
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	if (S_OK != GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgBoxAssert("Constant ���� ������ �����߽��ϴ�.");
		return;
	}
}


void GameEngineConstantBuffer::Setting()
{
	switch (Type)
	{
	case ShaderType::None:
		break;
	case ShaderType::Vertex:
		GameEngineCore::GetContext()->VSSetConstantBuffers(Slot, 1, &Buffer);
		break;
	case ShaderType::Hull:
		break;
	case ShaderType::Tessellator:
		break;
	case ShaderType::Domain:
		break;
	case ShaderType::Geometry:
		break;
	case ShaderType::Pixel:
		GameEngineCore::GetContext()->PSSetConstantBuffers(Slot, 1, &Buffer);
		break;
	case ShaderType::Max:
		break;
	default:
		break;
	}

	// GameEngineCore::GetContext()->VSSetConstantBuffers()
}