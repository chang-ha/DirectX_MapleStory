#pragma comment(lib, "GameEngineContents.lib")

#include <iostream>
#include <Windows.h>

#include <GameEngineCore/GameEngineCore.h>

#include <GameEngineContents/MapleStoryCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::EngineStart<MapleStoryCore>(hInstance);
}

