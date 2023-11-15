#include "PreCompile.h"
#include "GameEngineStructuredBuffer.h"

std::map<int, std::shared_ptr<GameEngineStructuredBuffer>> GameEngineStructuredBuffer::StructuredBufferRes;

GameEngineStructuredBuffer::GameEngineStructuredBuffer()
{
}

GameEngineStructuredBuffer::~GameEngineStructuredBuffer()
{
	Release();
}


void GameEngineStructuredBuffer::VSSetting(UINT _Slot)
{
	// 스트럭처드 버퍼를 만들면 SRV
	// 무슨 슬롯을 t슬롯을 차지하고 있었다.
	GameEngineCore::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}
void GameEngineStructuredBuffer::PSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->PSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineStructuredBuffer::VSReset(UINT _Slot)
{
	ID3D11ShaderResourceView* NullSRV = nullptr;

	// 스트럭처드 버퍼를 만들면 SRV
	// 무슨 슬롯을 t슬롯을 차지하고 있었다.
	GameEngineCore::GetContext()->VSSetShaderResources(_Slot, 1, &NullSRV);
}
void GameEngineStructuredBuffer::PSReset(UINT _Slot)
{
	ID3D11ShaderResourceView* NullSRV = nullptr;

	GameEngineCore::GetContext()->PSSetShaderResources(_Slot, 1, &NullSRV);
}

void GameEngineStructuredBuffer::Release()
{
	if (nullptr != UAV)
	{
		UAV->Release();
		UAV = nullptr;
	}

	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}
	BufferRelease();
}

void GameEngineStructuredBuffer::CreateResize(int _Byte, int _Count, StructuredBufferType _Type, const void* _StartData/* = nullptr*/)
{
	if (DataCount == _Count)
	{
		return;
	}

	if (DataCount < _Count)
	{
		Release();
	}

	if (0 >= _Byte)
	{
		MsgBoxAssert("크기가 0인 스트럭처드 버퍼를 만들 수는 없습니다.");
	}

	if (DataSize != _Byte)
	{
		MsgBoxAssert("if (DataSize != _Byte) 스트럭처드 버퍼 세팅 크기가 다릅니다.");
	}

	DataCount = _Count;

	D3D11_BUFFER_DESC Desc;

	Desc.ByteWidth = DataSize * DataCount;
	// 1개 크기
	Desc.StructureByteStride = DataSize;
	BufferInfo = Desc;

	Desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	// 메모리 관련으로 굉장히 중요한 옵션
	Desc.Usage = D3D11_USAGE_DEFAULT;

	Type = _Type;

	switch (_Type)
	{
		// 데이터 전송 용도로 사용하려는 것
	case StructuredBufferType::SRV_ONLY:
		Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Desc.Usage = D3D11_USAGE_DYNAMIC;
		break;
		// 컴퓨트쉐이더에 데이터 전송 용도및 데이터를 받아오는 용도로 사용
	case StructuredBufferType::UAV_INC:
		// D3D11_BIND_UNORDERED_ACCESS 컴퓨트 쉐이더 전용.
		Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		// GPU에서 계산한 결과를 받아와요.
		// GPU에게 계산을 맡겼으니 믿고 사용하는것.
		// 내가 왜 바꿔?
		Desc.CPUAccessFlags = 0;
		Desc.Usage = D3D11_USAGE_DEFAULT;
		break;
	default:
		break;
	}

	D3D11_SUBRESOURCE_DATA* StartDataPtr = nullptr;
	D3D11_SUBRESOURCE_DATA StartData = { 0 };
	if (nullptr != _StartData)
	{
		StartData.SysMemPitch = 0;
		StartData.SysMemSlicePitch = 0;
		StartData.pSysMem = _StartData;
		StartDataPtr = &StartData;
	}

	BufferInfo = Desc;

	if (S_OK != GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, StartDataPtr, &Buffer))
	{
		MsgBoxAssert("스트럭처드 버퍼 생성에 실패했습니다");
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDecs = {};
	// 쉐이더 리소스 뷰를 텍스처가 아닌 일반 버퍼에서 생성하겠다.
	SRVDecs.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	SRVDecs.Format = DXGI_FORMAT_UNKNOWN;
	// 버퍼의 시작점을 어디서부터 볼것이냐?
	SRVDecs.BufferEx.FirstElement = 0;
	SRVDecs.BufferEx.Flags = 0;
	SRVDecs.BufferEx.NumElements = DataCount;

	if (S_OK != GameEngineCore::GetDevice()->CreateShaderResourceView(Buffer, &SRVDecs, &SRV))
	{
		MsgBoxAssert("스트럭처드 버퍼 생성도중 쉐이더 리소스 뷰 생성에 실패했습니다");
	}

	if (_Type == StructuredBufferType::UAV_INC)
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC UVADesc = {};
		UVADesc.Buffer.NumElements = DataCount;
		UVADesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

		if (S_OK != GameEngineCore::GetDevice()->CreateUnorderedAccessView(Buffer, &UVADesc, &UAV))
		{
			MsgBoxAssert("스트럭처드 버퍼 생성도중 언 오더드 액세스 뷰 생성에 실패했습니다.");
		}
	}

	// 결과 받아오기용 추가 버퍼를 만들 생각인데.
	// 안만들면 안됨.
	if (true)
	{

	}


}

void GameEngineStructuredBuffer::ChangeData(const void* _Data, size_t _Size)
{
	// 많이 사용하면 안좋다.
	// 이제부터 수정을 들어갈것이다. == 해당 데이터를 쓰던 녀석들은 일시정지 == 느려짐
	// 그래픽카드에서 이 데이터를 보거나 이 데이터와 관련된 병렬처리 되던 픽셀이든 버텍스든 모든 쉐이더가 정리하는것
	GameEngineCore::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResources);
	// SettingResources 이게 그래픽카드의 메모리 그자체가 아니다 거기에 수정하라고 보낼 일이다.

	if (nullptr == SettingResources.pData)
	{
		MsgBoxAssert("스트럭처드 버퍼의 GPU 메모리를 얻어오지 못했습니다");
		GameEngineCore::GetContext()->Unmap(Buffer, 0);
		return;
	}
	memcpy_s(SettingResources.pData, BufferInfo.ByteWidth, _Data, _Size);
	GameEngineCore::GetContext()->Unmap(Buffer, 0);
}