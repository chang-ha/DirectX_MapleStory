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


void GameEngineConstantBuffer::Setting(UINT _Slot)
{
	GameEngineCore::GetContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
}

void GameEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
	if (nullptr == _Data)
	{
		std::string Name = Name;
		MsgBoxAssert(Name + "nullptr�� �����͸� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// CPU ����Ʈ�е��� GPU����Ʈ�е� ó����� ���̷� ���� ����Ʈ ���̰� ����� Errorâ ���	
	if (_Size != BufferInfo.ByteWidth)
	{
		std::string Name = Name;
		MsgBoxAssert(Name + "ũ�Ⱑ �ٸ� �����ͷ� ������۸� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE Data = {};

	// �� ���۸� ��� ������ ��� ������ �����Ұž�. -> �׷���ī�忡�� Rendering�� ��� ����(������)
	// �׷��� ���� ���� ������ Map�� 1���� ȣ���ϴ� ���ε� �̷��� �ϸ� �ʹ� ���Ǽ��� ������
	// �׷��� �׳� �� ����
	GameEngineCore::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

	// Map�� ȣ���ϸ� Data�����Ϳ� �׷���ī�忡 ���� �����͸� ������ �� �ִ� �ּҰ��� �ش�.
	// pData�� nullptr�̸� �ּҰ��� �� ���� ��
	if (Data.pData == nullptr)
	{
		std::string Name = Name;
		MsgBoxAssert(Name + "���� ���� ������ ���� ���߽��ϴ�.");
		return;
	}

	memcpy_s(Data.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);

	// �� ���������� ���� ���۸� �ᵵ �ȴٰ� ���������
	// �ƴ� ���۸� ��� �Ⱦ��� Rendering�� ����
	GameEngineCore::GetContext()->Unmap(Buffer, 0);
}
