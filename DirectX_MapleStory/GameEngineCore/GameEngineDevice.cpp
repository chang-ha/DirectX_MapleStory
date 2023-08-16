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
		MsgBoxAssert("�����찡 ��������� �ʾҴµ� ����̽��� �ʱ�ȭ �Ҽ��� �����ϴ�.");
		return;
	} 

	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// ���̷�Ʈx ���� ��������ظ� �˾Ƴ��� ���� ����.
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// �׷���ī���� �⺻������ �˷��ְ� �����Ҽ� �ִ� �������̽�.
	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		Adapter->Release();
		MsgBoxAssert("�׷���ī�尡 ���� ��ǻ���Դϴ�.");
		return;
	}

	// D11����̽��� �׷���ī�� ������ �޸𸮸� �����Ҽ� �ִ� �������̽��Դϴ�.
	// ���߿� �������̽� => �޸� 

	// �� ��ġ�� IDXGIAdapter* Adapter
	// �޸𸮿� �����ϴ� ���Ѱ� ID3D11Device* Device
	// �׸��� �׸��� �ִ� ������ �������. ID3D11DeviceContext* Context

	// 0������ �⺻���� ����.

	HRESULT Result = D3D11CreateDevice(
		Adapter, // ��ġ <= 
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, // �� ��ġ�� �ϵ����� �����޶��ε�.
		nullptr, // ������
		iFlag, // �ʱ�ȭ �ɼ�
		nullptr, // ����Ҽ� �ִ� ��ó����
		0, // ���߿��� ���� ���ϴ� ��ó���� �Ҽ� �ִ� 
		D3D11_SDK_VERSION, // ���� ������ �������� ����.
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
		MsgBoxAssert("����̽� ������ �����߽��ϴ�.");
		return;
	}

	if (D3D_FEATURE_LEVEL_11_0 != Level)
	{
		MsgBoxAssert("���̷�Ʈ 11�� �������� �ʴ� �׷���ī�� �Դϴ�.");
		return;
	}

	// ��Ƽ �����带 ����ϴ� ���� ����
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (0 == Result)
	{
		MsgBoxAssert("��Ƽ������ ���� �׷���ī�带 �̿��Ҽ� �����ϴ�.");
		return;
	}

	// �̷�����
	// ������ �̶�� �ϴ°� �ٲ����� ����.
	// ���̷�Ʈ 3D�� winAPI�� �ٸ��� ����.

	// �ƿ� ȭ�鿡 ����� ���� ������۸����� �����ϴ� ȭ����¿� �̹��� + ������۸� �������̽��� 
	// ����Ϳ� ����ϴ� ��� ��ü�� �����մϴ�.
	// �װ� ����ü���̶�� �Ѵ�.

	Window = &_Window;

	CreateSwapChain();
	ResourcesInit();
}

IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// �ü�����Ժ�Ź�ؼ� �ϵ���� ���� ����� �̿��Ҽ� �ִ�
	// IDXGIFactory�� ������ ��.
	// ���� �����Ҽ� ���� ������ �Լ�
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (nullptr == Factory)
	{
		MsgBoxAssert("�׷��� ī�忡�� ���丮 �������̽��� �������� ���߽��ϴ�.");
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
			// �� ū ���� �޸�.
			VideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				// ���ο� �ִ� �޸𸮸� �������ش�.
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
	// ����ü�� 
	float4 WindowScale = Window->GetScale();

	// _DESC <= �̹�
	// TEXTURE_DESC <= �̹����� ũ�� �̹����� ���� �̹����� ����ü


	DXGI_SWAP_CHAIN_DESC ScInfo = {0,};

	// ������۸�
	ScInfo.BufferCount = 2;
	ScInfo.BufferDesc.Width = WindowScale.iX();
	ScInfo.BufferDesc.Height = WindowScale.iY();
	ScInfo.OutputWindow = Window->GetHWND();

	// �ּ��ֻ���
	ScInfo.BufferDesc.RefreshRate.Denominator = 1;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60;

	// R8G8B8A8
	// ���� ǥ���ϴµ� 8��Ʈ.
	// ��� ǥ���ϴµ� 8��Ʈ.
	// û�� ǥ���ϴµ� 8��Ʈ.
	// ���� ǥ���ϴµ� 8��Ʈ.
	// 4����Ʈ
	// �̻��󿡴� ���� ū �ǹ̰� ����.
	// �츮�� 32����Ʈ¥�� �������� �غ���.
	// HDR�� �ƴϸ� �̰� ������ 
	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// ��ϴ��͸� �׸��� � �ȼ����� �����Ұų�.
	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// �����뵵�� ���ſ��� �� ����ü��
	// DXGI_USAGE_RENDER_TARGET_OUTPUT <= ȭ�鿡 ���̰� ���ּ���.
	// ���̴����� ���� �ְ� ���ּ���. <= �ƹ��� �Ⱦ�.
	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	// �̳༮�� ���̴����� ����Ҷ�
	// ���̴����� �̰� ����ϸ� �� ���ø� ����Ƽ�� �߿������µ�
	// �̳༮�� ���̴����� ���Ǵ� �༮�� �ƴϱ� ������ ���������������� �߿����� �ʴ�.

	// �� ������ ����Ƽ
	ScInfo.SampleDesc.Quality = 0;
	// ������
	ScInfo.SampleDesc.Count = 1;

	// ScInfo.BufferCount = 2;
	// ��ü������ ����� �����մϴ�.
	ScInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;

	// ���ȳ�.
	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// ��üȭ���̳� �ƴϳ�.
	// �翬�� �׷����������� �� �������� �մϴ�.
	ScInfo.Windowed = true;

	// ����ü���� ����� ���� ���ؼ��� _Devcie�� �ʿ��ϴ�.
	IDXGIDevice* pD = nullptr;
	IDXGIAdapter* pA = nullptr;
	IDXGIFactory* pF = nullptr;

	// ���̷�Ʈ ���̺귯�� ����ϴ� ��ü���� ����� �� ��ü���� �ڽ��� å������ �ִ�
	// ��ġ�� �ڽ��� ����µ� ���� ��ü���� ������ �ֽ��ϴ�.
	Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pD));
	if (nullptr == pD)
	{
		MsgBoxAssert("����̽� ���⿡ �����߽��ϴ�.");
		return;
	}

	pD->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pA));
	if (nullptr == pD)
	{
		MsgBoxAssert("��� ���⿡ �����߽��ϴ�.");
	}

	pA->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));
	if (nullptr == pF)
	{
		MsgBoxAssert("���丮 ���⿡ �����߽��ϴ�.");
	}

	// �� ��ġ�� ���õ� ��ҵ��� ����� �ִ� ����� ������ �ִ�.
	pF->CreateSwapChain(Device, &ScInfo, &SwapChain);

	pF->Release();
	pA->Release();
	pD->Release();

	// �迭�� ���� �ִٴ°��� �˼��� �ִ�.

	ID3D11Texture2D* DXBackBufferTexture = nullptr;
	if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&DXBackBufferTexture)))
	{
		MsgBoxAssert("����� �ؽ�ó�� ������ ���߽��ϴ�.");
	}

	// ���̷�Ʈx�� ���� �׸��� �ִ� ������ 
	// 
	
	// �ؽ�ó�δ� �ȵ˴ϴ�.
	BackBufferTexture = GameEngineTexture::Create(DXBackBufferTexture);
	BackBufferRenderTarget = GameEngineRenderTarget::Create(BackBufferTexture);

	// ����Ÿ���� ������ �Ѵ�.

	// BackBufferTexture->Release();

	// ����ü������ �ؽ�ó�� �ƴϴ�.
	// ������ �׸����� �ؽ�ó�� �����ؾ� �ϴµ�.
	// �� �ؽ�ó�� 
}

void GameEngineDevice::RenderStart()
{
	if (nullptr == Device)
	{
		return;
	}

	// ��ȭ���� �ѹ� �� ������.
	BackBufferRenderTarget->Clear();

	// �� ��ȭ���� �����մϴ�.
	BackBufferRenderTarget->Setting();
}

void GameEngineDevice::RenderEnd()
{
	if (nullptr == Device)
	{
		return;
	}

	// ����ü�ο� ����� �ؽ�ó�� �׷����ִ� ������ ȭ�鿡 ����϶�°�.
	HRESULT Result = SwapChain->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgBoxAssert("��üȭ�鿡�� â���� �����߽��ϴ�.");
		return;
	}
}