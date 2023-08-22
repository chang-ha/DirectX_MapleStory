#include "PreCompile.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineVertexShader.h"
#include "GameEngineVertexBuffer.h"

GameEngineInputLayOut::GameEngineInputLayOut() 
{
}

GameEngineInputLayOut::~GameEngineInputLayOut() 
{
	if (nullptr != LayOut)
	{
		LayOut->Release();
		LayOut = nullptr;
	}
}

void GameEngineInputLayOut::ResCreate(std::shared_ptr<class GameEngineVertexBuffer> _Buffer, std::shared_ptr<class GameEngineVertexShader> _Shader)
{
	//const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, 버텍스의 형태정보
	//UINT NumElements, 형태정보의 개수
	//const void* pShaderBytecodeWithInputSignature, // 쉐이더 코드
	//SIZE_T BytecodeLength, 쉐이더 코드 길이
	//ID3D11InputLayout** ppInputLayout // 그렇게 만들어질 포인터

	// D3D11_INPUT_ELEMENT_DESC InputElementDescs[20];
	// pShaderBytecodeWithInputSignature 쉐이더 코드 달라고 하는 겁니다.

	// GameEngineCore::MainDevcie.GetDevice()->CreateInputLayout(InputElementDescs, 20,  &LayOut);

	const std::vector<D3D11_INPUT_ELEMENT_DESC>& Infos = _Buffer->VertexInfoPtr->Infos;
	GameEngineCore::GetDevice()->CreateInputLayout(
		&Infos[0],
		static_cast<UINT>(Infos.size()),
		_Shader->BinaryCode->GetBufferPointer(),
		_Shader->BinaryCode->GetBufferSize(),
		&LayOut);

	if (nullptr == LayOut)
	{
		MsgBoxAssert("레이아웃 생성에 실패했습니다.");
	}
}

void GameEngineInputLayOut::Setting()
{
	if (nullptr == LayOut)
	{
		MsgBoxAssert("만들어지지도 않은 버텍스 버퍼를 세팅할 수는 없습니다.");
	}

	// 버텍스버퍼를 여러개 넣어줄수 있다.
	GameEngineCore::GetContext()->IASetInputLayout(LayOut);
}

void GameEngineInputLayOutInfo::AddInputLayOutDesc(
	LPCSTR _SemanticName, // 내가 포지션이다 내가 컬러다. = "POSITION"
	DXGI_FORMAT _Format, // 내가 n바이트 짜리 정보다 자료형 = DXGI_FORMAT::R32G32 32
	UINT _SemanticIndex/* = 0*/, // POSTION0
	UINT _AlignedByteOffset /*= -1*/, // 0번째 바이트부터 
	D3D11_INPUT_CLASSIFICATION _InputSlotClass /*= D3D11_INPUT_PER_VERTEX_DATA*/, // 버텍스 데이터가 인스턴싱 데이터다 라는걸 표현
	UINT _InputSlot /*= 0*/, // n개의 버텍스 버퍼를 세팅할때 n번째 버텍스 버퍼의 인풋 레이아웃이다 라는걸 표현하는것
	UINT _InstanceDataStepRate /*= 0*/ // 나중에 나중에 인스턴싱이라는 구조를 배울때 쓸때가 있을것이다.
)
{
	D3D11_INPUT_ELEMENT_DESC Desc;

	Desc.SemanticName = _SemanticName;
	Desc.SemanticIndex = _SemanticIndex;
	Desc.Format = _Format;
	Desc.InputSlot = _InputSlot;
	Desc.InputSlotClass = _InputSlotClass;
	Desc.InstanceDataStepRate = _InstanceDataStepRate;

	if (-1 == _AlignedByteOffset)
	{
		Desc.AlignedByteOffset = Offset;
	}
	else
	{
		Desc.AlignedByteOffset = _AlignedByteOffset;
	}
	Offset += FormatSize(_Format);
	Infos.push_back(Desc);
}

UINT GameEngineInputLayOutInfo::FormatSize(DXGI_FORMAT _Format)
{
	switch (_Format)
	{
	case DXGI_FORMAT_UNKNOWN:
		break;
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
	case DXGI_FORMAT_R32G32B32A32_UINT:
	case DXGI_FORMAT_R32G32B32A32_SINT:
		return 16;
	case DXGI_FORMAT_R32G32B32_TYPELESS:
	case DXGI_FORMAT_R32G32B32_FLOAT:
	case DXGI_FORMAT_R32G32B32_UINT:
	case DXGI_FORMAT_R32G32B32_SINT:
		return 12;
	case DXGI_FORMAT_R16G16B16A16_TYPELESS:
		break;
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
		break;
	case DXGI_FORMAT_R16G16B16A16_UNORM:
		break;
	case DXGI_FORMAT_R16G16B16A16_UINT:
		break;
	case DXGI_FORMAT_R16G16B16A16_SNORM:
		break;
	case DXGI_FORMAT_R16G16B16A16_SINT:
		break;
	case DXGI_FORMAT_R32G32_TYPELESS:
		break;
	case DXGI_FORMAT_R32G32_FLOAT:
		break;
	case DXGI_FORMAT_R32G32_UINT:
		break;
	case DXGI_FORMAT_R32G32_SINT:
		break;
	case DXGI_FORMAT_R32G8X24_TYPELESS:
		break;
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		break;
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
		break;
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
		break;
	case DXGI_FORMAT_R10G10B10A2_TYPELESS:
		break;
	case DXGI_FORMAT_R10G10B10A2_UNORM:
		break;
	case DXGI_FORMAT_R10G10B10A2_UINT:
		break;
	case DXGI_FORMAT_R11G11B10_FLOAT:
		break;
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		break;
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		break;
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		break;
	case DXGI_FORMAT_R8G8B8A8_UINT:
		break;
	case DXGI_FORMAT_R8G8B8A8_SNORM:
		break;
	case DXGI_FORMAT_R8G8B8A8_SINT:
		break;
	case DXGI_FORMAT_R16G16_TYPELESS:
		break;
	case DXGI_FORMAT_R16G16_FLOAT:
		break;
	case DXGI_FORMAT_R16G16_UNORM:
		break;
	case DXGI_FORMAT_R16G16_UINT:
		break;
	case DXGI_FORMAT_R16G16_SNORM:
		break;
	case DXGI_FORMAT_R16G16_SINT:
		break;
	case DXGI_FORMAT_R32_TYPELESS:
		break;
	case DXGI_FORMAT_D32_FLOAT:
		break;
	case DXGI_FORMAT_R32_FLOAT:
		break;
	case DXGI_FORMAT_R32_UINT:
		break;
	case DXGI_FORMAT_R32_SINT:
		break;
	case DXGI_FORMAT_R24G8_TYPELESS:
		break;
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		break;
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
		break;
	case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
		break;
	case DXGI_FORMAT_R8G8_TYPELESS:
		break;
	case DXGI_FORMAT_R8G8_UNORM:
		break;
	case DXGI_FORMAT_R8G8_UINT:
		break;
	case DXGI_FORMAT_R8G8_SNORM:
		break;
	case DXGI_FORMAT_R8G8_SINT:
		break;
	case DXGI_FORMAT_R16_TYPELESS:
		break;
	case DXGI_FORMAT_R16_FLOAT:
		break;
	case DXGI_FORMAT_D16_UNORM:
		break;
	case DXGI_FORMAT_R16_UNORM:
		break;
	case DXGI_FORMAT_R16_UINT:
		break;
	case DXGI_FORMAT_R16_SNORM:
		break;
	case DXGI_FORMAT_R16_SINT:
		break;
	case DXGI_FORMAT_R8_TYPELESS:
		break;
	case DXGI_FORMAT_R8_UNORM:
		break;
	case DXGI_FORMAT_R8_UINT:
		break;
	case DXGI_FORMAT_R8_SNORM:
		break;
	case DXGI_FORMAT_R8_SINT:
		break;
	case DXGI_FORMAT_A8_UNORM:
		break;
	case DXGI_FORMAT_R1_UNORM:
		break;
	case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
		break;
	case DXGI_FORMAT_R8G8_B8G8_UNORM:
		break;
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
		break;
	case DXGI_FORMAT_BC1_TYPELESS:
		break;
	case DXGI_FORMAT_BC1_UNORM:
		break;
	case DXGI_FORMAT_BC1_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC2_TYPELESS:
		break;
	case DXGI_FORMAT_BC2_UNORM:
		break;
	case DXGI_FORMAT_BC2_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC3_TYPELESS:
		break;
	case DXGI_FORMAT_BC3_UNORM:
		break;
	case DXGI_FORMAT_BC3_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC4_TYPELESS:
		break;
	case DXGI_FORMAT_BC4_UNORM:
		break;
	case DXGI_FORMAT_BC4_SNORM:
		break;
	case DXGI_FORMAT_BC5_TYPELESS:
		break;
	case DXGI_FORMAT_BC5_UNORM:
		break;
	case DXGI_FORMAT_BC5_SNORM:
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		break;
	case DXGI_FORMAT_B5G5R5A1_UNORM:
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM:
		break;
	case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
		break;
	case DXGI_FORMAT_B8G8R8A8_TYPELESS:
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
		break;
	case DXGI_FORMAT_B8G8R8X8_TYPELESS:
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC6H_TYPELESS:
		break;
	case DXGI_FORMAT_BC6H_UF16:
		break;
	case DXGI_FORMAT_BC6H_SF16:
		break;
	case DXGI_FORMAT_BC7_TYPELESS:
		break;
	case DXGI_FORMAT_BC7_UNORM:
		break;
	case DXGI_FORMAT_BC7_UNORM_SRGB:
		break;
	case DXGI_FORMAT_AYUV:
		break;
	case DXGI_FORMAT_Y410:
		break;
	case DXGI_FORMAT_Y416:
		break;
	case DXGI_FORMAT_NV12:
		break;
	case DXGI_FORMAT_P010:
		break;
	case DXGI_FORMAT_P016:
		break;
	case DXGI_FORMAT_420_OPAQUE:
		break;
	case DXGI_FORMAT_YUY2:
		break;
	case DXGI_FORMAT_Y210:
		break;
	case DXGI_FORMAT_Y216:
		break;
	case DXGI_FORMAT_NV11:
		break;
	case DXGI_FORMAT_AI44:
		break;
	case DXGI_FORMAT_IA44:
		break;
	case DXGI_FORMAT_P8:
		break;
	case DXGI_FORMAT_A8P8:
		break;
	case DXGI_FORMAT_B4G4R4A4_UNORM:
		break;
	case DXGI_FORMAT_P208:
		break;
	case DXGI_FORMAT_V208:
		break;
	case DXGI_FORMAT_V408:
		break;
	case DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE:
		break;
	case DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE:
		break;
	case DXGI_FORMAT_FORCE_UINT:
		break;
	default:
		break;
	}

	MsgBoxAssert("처리할수 없는 포맷을 사용했습니다.");
	return -1;
}