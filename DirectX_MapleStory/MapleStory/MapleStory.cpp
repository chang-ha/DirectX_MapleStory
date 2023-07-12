#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEnginePlatform.lib")

#include <iostream>
#include <Windows.h>
#include <GameEnginePlatform/GameEngineWindow.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineWindow::MainWindow.Open("TestWindow", hInstance);
	GameEngineWindow::MainWindow.SetPosAndScale({ 50, 50 }, { 1366, 789 });

	GameEngineWindow::MessageLoop(hInstance, nullptr, nullptr, nullptr);
}

