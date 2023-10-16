#pragma once
#include "GameEngineWindowTexture.h"
#include <functional>

// ���� :
class GameEngineWindow
{
public:
	static std::function<LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)> MsgFunction;

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	void Open(const std::string& _Title, HINSTANCE _hInstance);

	static void MessageLoop(HINSTANCE _Inst, 
		std::function<void()> _Start,
		std::function<void()> _Update,
		std::function<void()> _Release
	);

	HDC GetHDC() 
	{
		return Hdc;
	}

	HWND GetHWND() const
	{
		return hWnd;
	}

	float4 GetScale() const
	{
		return Scale;
	}

	GameEngineWindowTexture* GetWindowBuffer() const
	{
		return WindowBuffer;
	}

	GameEngineWindowTexture* GetBackBuffer() const
	{
		return BackBuffer;
	}

	float4 GetMousePos();

	void SetPosAndScale(const float4& _Pos, const float4& _Scale);

	static void WindowLoopOff() 
	{
		IsWindowUpdate = false;
	}

	void ClearBackBuffer();
	void DoubleBuffering();

	void CursorOff();

	static bool IsFocus() 
	{
		return IsFocusValue;
	}

	float GetDoubleBufferingCopyScaleRatio() const
	{
		return CopyRatio;
	}

	void SetDoubleBufferingCopyScaleRatio(float _Ratio) 
	{
		CopyRatio = _Ratio;
	}

	void AddDoubleBufferingCopyScaleRatio(float _Ratio)
	{
		CopyRatio += _Ratio;
	}

protected:

private:
	static bool IsWindowUpdate;
	static bool IsFocusValue;
	static HINSTANCE Instance;
	std::string Title = "";
	HWND hWnd = nullptr;

	float CopyRatio = 1.0f;

	float4 Scale;
	GameEngineWindowTexture* WindowBuffer = nullptr;

	GameEngineWindowTexture* BackBuffer = nullptr;

	// 2���� �迭 ������ ������� ������ �����ϰ�
	// �ű⿡ �׸��� �׸��ų� �����Ҽ� �ִ� ������ HDC
	HDC Hdc = nullptr;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitInstance();
	void MyRegisterClass();
};

