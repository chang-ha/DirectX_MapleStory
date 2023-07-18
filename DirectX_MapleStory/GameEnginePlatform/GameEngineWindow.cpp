#include "PreCompile.h"
#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <iostream>



HINSTANCE GameEngineWindow::Instance = nullptr;
bool GameEngineWindow::IsWindowUpdate = true;
bool GameEngineWindow::IsFocusValue = false;

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
	if (nullptr != BackBuffer)
	{
		delete BackBuffer;
		BackBuffer = nullptr;
	}


	if (nullptr != WindowBuffer)
	{
		delete WindowBuffer;
		WindowBuffer = nullptr;
	}
}

void GameEngineWindow::ClearBackBuffer()
{
	Rectangle(BackBuffer->GetImageDC(), 0, 0, BackBuffer->GetScale().iX(), BackBuffer->GetScale().iY());
}

void GameEngineWindow::DoubleBuffering()
{
	float4 CopyLeftTop = float4::ZERO;
	float4 CopyRightBot = BackBuffer->GetScale();

	WindowBuffer->TransCopy(BackBuffer, Scale.Half(), BackBuffer->GetScale() * CopyRatio, CopyLeftTop, CopyRightBot);
}

void GameEngineWindow::Open(const std::string& _Title, HINSTANCE _hInstance)
{
	Instance = _hInstance;
	Title = _Title;

	if (nullptr == Instance)
	{
		MsgBoxAssert("HInstance���� �����츦 ������� �����ϴ�.");
		return;
	}

	MyRegisterClass();
	InitInstance();
}


void GameEngineWindow::InitInstance()
{
	//WS_OVERLAPPED | \
    //    WS_CAPTION | \
    //    WS_SYSMENU | \
    //    WS_THICKFRAME | \
    //    WS_MINIMIZEBOX | \
    //    WS_MAXIMIZEBOX


	// int Test = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME ;









	// WS_OVERLAPPEDWINDOW

	hWnd = CreateWindowA("DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);

	if (!hWnd)
	{
		MsgBoxAssert("������ ������ �����߽��ϴ�.");
		return;
	}

	Hdc = ::GetDC(hWnd);

	WindowBuffer = new GameEngineWindowTexture();
	WindowBuffer->ResCreate(Hdc);

	// ���ù��۸��� �ϱ� ���� �̹���
	BackBuffer = new GameEngineWindowTexture();
	BackBuffer->ResCreate(Hdc, WindowBuffer->GetScale());

	// CreateDC()

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

}

LRESULT CALLBACK GameEngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SETFOCUS:
	{
		IsFocusValue = true;
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_KILLFOCUS:
	{
		IsFocusValue = false;
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		IsWindowUpdate = false;
		// PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void GameEngineWindow::MyRegisterClass()
{
	static bool Check = false;

	if (true == Check)
	{
		return;
	}

	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	// LRESULT(CALLBACK* WNDPROC)(HWND, unsigned int, unsigned int, unsigned int);
	wcex.lpfnWndProc = GameEngineWindow::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = Instance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "DefaultWindow";
	wcex.hIconSm = nullptr;

	if (false == RegisterClassExA(&wcex))
	{
		MsgBoxAssert("������ Ŭ���� ���Ͽ� �����߽��ϴ�.");
		return;
	}

	Check = true;
}

void GameEngineWindow::MessageLoop(HINSTANCE _Inst,
	std::function<void()> _Start,
	std::function<void()> _Update,
	std::function<void()> _Release
)
{
	// �����찡 �߱����� �ε��ؾ��� �̹����� ���� ����� ó���ϴ� �ܰ�
	if (nullptr != _Start)
	{
		_Start();
	}

	MSG msg;

	while (IsWindowUpdate)
	{
		// �����쿡 �������� �ִ°� �ƴ϶� �޼����� �ֵ� ����
		// �����Լ� _getch()
		// <= Ű�� ���������� �����
		// (�Լ��� ����� ���������� ��ٸ��� �Լ����� ���� �Լ���� �մϴ�).
		// GetMessage�� ���� �Լ�����. �������� �޼����� �߻��Ҷ����� ��ٸ���.
		// �񵿱� �޼��� �Լ��� �ִ�. 
		// PeekMessage�� ������ �޼����� ������ 0�� ���ϵǰ� �׳� �����մϴ�.

		// �����Ӱ� ����Ÿ���� �ϼ��ƴ�.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//if (nullptr != _Update)
			//{
			//	_Update();
			//}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		// ������ �޼����� ���� �ð��� ����Ÿ���̶�� �մϴ�.
		// ������ ����Ÿ�ӿ� ���ư��°� �����̴�.
		// �����߿� 2���� ������ �ִ�. �����츦 �����̰ų� ũ�⸦ ���̸�
		// ȭ���� �����ϴ� ����. 
		// ���� �׷� ������ �޼����� �߻���Ű�� ���߿��� ������ ��� ���ư��� �����ִ�.

		// �̰� �ѹٲ ���� ���� ������
		// FPS
		// �ʴ� ȭ���� �׷����� Ƚ��
		// �ϵ����͵� ������ �ִ�.
		if (nullptr != _Update)
		{
			_Update();
		}

	}


	if (nullptr != _Release)
	{
		_Release();
	}


	// (int)msg.wParam;

	return;
}

void GameEngineWindow::SetPosAndScale(const float4& _Pos, const float4& _Scale)
{
	// Window���� LP �����Ͷ�� �� Long Pointer
	Scale = _Scale;

	if (nullptr != BackBuffer)
	{
		delete BackBuffer;
		BackBuffer = new GameEngineWindowTexture();
		BackBuffer->ResCreate(Hdc, Scale);
	}

	//                200           200
	RECT Rc = { 0, 0, _Scale.iX(), _Scale.iY() };


	AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW,FALSE);

	//                          100        100         500          500
	SetWindowPos(hWnd, nullptr, _Pos.iX(), _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}

float4 GameEngineWindow::GetMousePos()
{
	POINT MoniterPoint;
	GetCursorPos(&MoniterPoint);
	ScreenToClient(hWnd, &MoniterPoint);

	return float4{ static_cast<float>(MoniterPoint.x), static_cast<float>(MoniterPoint.y) };
}

void GameEngineWindow::CursorOff()
{
	ShowCursor(FALSE);
}