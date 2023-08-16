#include "PreCompile.h"
#include "GameEngineDevice.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")


GameEngineDevice::GameEngineDevice() 
{
}

GameEngineDevice::~GameEngineDevice() 
{
	if (nullptr != SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}

	if (nullptr != Context)
	{
		Context->Release();
		Context = nullptr;
	}

	if (nullptr != Device)
	{
		Device->Release();
		Device = nullptr;
	}
}


void GameEngineDevice::Initiallize(const GameEngineWindow& _Window)
{
	if (nullptr == _Window.GetHWND())
	{
		MsgBoxAssert("윈도우가 만들어지지 않았는데 디바이스를 초기화 할수는 없습니다.");
		return;
	} 

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 다이렉트x 버전 몇까지원해를 알아내기 위한 변수.
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// 그래픽카드의 기본정보를 알려주고 제어할수 있는 인터페이스.
	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		Adapter->Release();
		MsgBoxAssert("그래픽카드가 없는 컴퓨터입니다.");
		return;
	}

	// D11디바이스는 그래픽카드 랜더링 메모리를 제어할수 있는 인터페이스입니다.
	// 최중요 인터페이스 => 메모리 

	// 이 장치의 IDXGIAdapter* Adapter
	// 메모리에 접근하는 권한과 ID3D11Device* Device
	// 그림을 그릴수 있는 권한을 만들어줘. ID3D11DeviceContext* Context

	// 0넣으면 기본으로 해줘.

	HRESULT Result = D3D11CreateDevice(
		Adapter, // 장치 <= 
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, // 이 장치의 하드웨어로 만들어달라인데.
		nullptr, // 뭔지모름
		iFlag, // 초기화 옵션
		nullptr, // 사용할수 있는 펙처레벨
		0, // 그중에서 내가 원하는 펙처레벨 할수 있는 
		D3D11_SDK_VERSION, // 지금 윈도우 버전으로 해줘.
		&Device, 
		&Level,
		&Context
	);

	if (nullptr != Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}

	if (S_OK != Result)
	{
		MsgBoxAssert("디바이스 생성에 실패했습니다.");
		return;
	}

	if (D3D_FEATURE_LEVEL_11_0 != Level)
	{
		MsgBoxAssert("다이렉트 11을 지원하지 않는 그래픽카드 입니다.");
		return;
	}

	// 멀티 쓰레드를 사용하는 모드로 변경
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (0 == Result)
	{
		MsgBoxAssert("멀티쓰레드 모드로 그래픽카드를 이용할수 없습니다.");
		return;
	}

	// 이러고나면
	// 랜더링 이라고 하는건 바뀐적이 없다.
	// 다이렉트 3D나 winAPI나 다를게 없다.

	// 아예 화면에 출력을 위한 더블버퍼링까지 지원하는 화면출력용 이미지 + 더블버퍼링 인터페이스를 
	// 모니터에 출력하는 기능 자체를 지원합니다.
	// 그걸 스왑체인이라고 한다.

	Window = &_Window;

	CreateSwapChain();
	ResourcesInit();
}

IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// 운영체제에게부탁해서 하드웨어 관련 기능을 이용할수 있는
	// IDXGIFactory를 얻어오는 것.
	// 내가 이해할수 없는 영역의 함수
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (nullptr == Factory)
	{
		MsgBoxAssert("그래픽 카드에서 팩토리 인터페이스를 생성하지 못했습니다.");
		return nullptr;
	}

	SIZE_T VideoMemory = 0;

	for (UINT Index = 0 ;; ++Index)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		Factory->EnumAdapters(Index, &CurAdapter);

		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (VideoMemory <= Desc.DedicatedVideoMemory)
		{
			// 더 큰 비디오 메모리.
			VideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				// 내부에 있는 메모리를 정리해준다.
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();
 	return Adapter;
}

void GameEngineDevice::CreateSwapChain()
{
	// 스왑체인 
	float4 WindowScale = Window->GetScale();

	// _DESC <= 이미
	// TEXTURE_DESC <= 이미지의 크기 이미지의 포맷 이미지의 구조체


	DXGI_SWAP_CHAIN_DESC ScInfo = {0,};

	// 더블버퍼링
	ScInfo.BufferCount = 2;
	ScInfo.BufferDesc.Width = WindowScale.iX();
	ScInfo.BufferDesc.Height = WindowScale.iY();
	ScInfo.OutputWindow = Window->GetHWND();

	// 최소주사율
	ScInfo.BufferDesc.RefreshRate.Denominator = 1;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60;

	// R8G8B8A8
	// 적색 표현하는데 8비트.
	// 녹색 표현하는데 8비트.
	// 청색 표현하는데 8비트.
	// 알파 표현하는데 8비트.
	// 4바이트
	// 이색상에는 보통 큰 의미가 없다.
	// 우리가 32바이트짜리 색상으로 해봐야.
	// HDR이 아니면 이걸 내가봐 
	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// 모니니터를 그릴때 어떤 픽셀부터 갱신할거냐.
	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 무슨용도로 쓸거에요 이 스왑체인
	// DXGI_USAGE_RENDER_TARGET_OUTPUT <= 화면에 보이게 해주세요.
	// 쉐이더에서 쓸수 있게 해주세요. <= 아무도 안씀.
	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	// 이녀석을 쉐이더에서 사용할때
	// 쉐이더에서 이걸 사용하면 이 샘플링 퀄리티가 중요해지는데
	// 이녀석은 쉐이더에서 사용되는 녀석이 아니기 때문에 더더더더더더더욱 중요하지 않다.

	// 그 개수당 퀄리티
	ScInfo.SampleDesc.Quality = 0;
	// 점개수
	ScInfo.SampleDesc.Count = 1;

	// ScInfo.BufferCount = 2;
	// 교체순서와 방식을 정의합니다.
	ScInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;

	// 기억안남.
	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// 전체화면이냐 아니냐.
	// 당연히 그래픽프레임이 더 빨라져야 합니다.
	ScInfo.Windowed = true;

	// 스왑체인을 만들어 내기 위해서는 _Devcie가 필요하다.
	IDXGIDevice* pD = nullptr;
	IDXGIAdapter* pA = nullptr;
	IDXGIFactory* pF = nullptr;

	// 다이렉트 라이브러를 사용하는 객체들을 만들면 그 객체들은 자신을 책임지고 있는
	// 장치와 자신을 만드는데 사용된 객체들을 가지고 있습니다.
	Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pD));
	if (nullptr == pD)
	{
		MsgBoxAssert("디바이스 추출에 실패했습니다.");
		return;
	}

	pD->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pA));
	if (nullptr == pD)
	{
		MsgBoxAssert("어뎁터 추출에 실패했습니다.");
	}

	pA->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));
	if (nullptr == pF)
	{
		MsgBoxAssert("팩토리 추출에 실패했습니다.");
	}

	// 이 장치와 관련된 요소들을 만들수 있는 기능을 가지고 있다.
	pF->CreateSwapChain(Device, &ScInfo, &SwapChain);

	pF->Release();
	pA->Release();
	pD->Release();

	// 배열로 보고 있다는것을 알수가 있다.

	ID3D11Texture2D* DXBackBufferTexture = nullptr;
	if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&DXBackBufferTexture)))
	{
		MsgBoxAssert("백버퍼 텍스처를 얻어오지 못했습니다.");
	}

	// 다이렉트x는 무언가 그릴수 있는 권한을 
	// 
	
	// 텍스처로는 안됩니다.
	BackBufferTexture = GameEngineTexture::Create(DXBackBufferTexture);
	BackBufferRenderTarget = GameEngineRenderTarget::Create(BackBufferTexture);

	// 랜더타겟을 만들어야 한다.

	// BackBufferTexture->Release();

	// 스왑체인이지 텍스처가 아니다.
	// 뭔가를 그리려면 텍스처가 존재해야 하는데.
	// 그 텍스처를 
}

void GameEngineDevice::RenderStart()
{
	if (nullptr == Device)
	{
		return;
	}

	// 도화지를 한번 싹 지워요.
	BackBufferRenderTarget->Clear();

	// 이 도화지를 세팅합니다.
	BackBufferRenderTarget->Setting();
}

void GameEngineDevice::RenderEnd()
{
	if (nullptr == Device)
	{
		return;
	}

	// 스왑체인에 연결된 텍스처에 그려져있는 색상을 화면에 출력하라는것.
	HRESULT Result = SwapChain->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgBoxAssert("전체화면에서 창모드로 변경했습니다.");
		return;
	}
}