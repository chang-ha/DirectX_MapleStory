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

	// Transform데이터를 매 프레임마다 계속 값을 바꿔줘야 하기 때문에 WRITE, DYNAMIC
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	if (S_OK != GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgBoxAssert("Constant 버퍼 생성에 실패했습니다.");
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
		MsgBoxAssert(Name + "nullptr인 데이터를 세팅하려고 했습니다.");
		return;
	}

	// CPU 바이트패딩과 GPU바이트패딩 처리방식 차이로 인해 바이트 차이가 생기면 Error창 띄움	
	if (_Size != BufferInfo.ByteWidth)
	{
		std::string Name = Name;
		MsgBoxAssert(Name + "크기가 다른 데이터로 상수버퍼를 세팅하려고 했습니다.");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE Data = {};

	// 이 버퍼를 잠깐 쓰지마 잠궈 데이터 변경할거야. -> 그래픽카드에서 Rendering을 잠시 멈춤(느려짐)
	// 그래서 가장 좋은 구조는 Map을 1번만 호출하는 것인데 이렇게 하면 너무 편의성이 떨어짐
	// 그래서 그냥 쓸 것임
	GameEngineCore::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

	// Map을 호출하면 Data포인터에 그래픽카드에 직접 데이터를 수정할 수 있는 주소값을 준다.
	// pData가 nullptr이면 주소값을 못 받은 것
	if (Data.pData == nullptr)
	{
		std::string Name = Name;
		MsgBoxAssert(Name + "버퍼 수정 권한을 얻어내지 못했습니다.");
		return;
	}

	memcpy_s(Data.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);

	// 다 수정했으면 이제 버퍼를 써도 된다고 말해줘야함
	// 아님 버퍼를 계속 안쓰고 Rendering을 멈춤
	GameEngineCore::GetContext()->Unmap(Buffer, 0);
}
