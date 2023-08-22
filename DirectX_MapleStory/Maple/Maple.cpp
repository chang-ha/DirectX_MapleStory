#include <GameEngineContents/PreCompile.h>

#pragma comment(lib, "GameEngineContents.lib")

#include <iostream>
#include <Windows.h>
#include <memory>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContents/MapleStoryCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::EngineStart<MapleStoryCore>(hInstance);
}

// 예외 발생(0x00007FFCC08FCF19, Maple.exe): Microsoft C++ 예외: Poco::NotFoundException, 메모리 위치 0x000000835D0F2370. << 이런 에러가 SwapChain에서 계속 발생
// 모든 코드를 헤집어도 해결되지 않음
// 결론 : 실행파일을 만드는 프로젝트의 이름이 너무 길면 나오는 에러임;;;
// 프로젝트명을 MapleStory -> Maple로 줄였더니 해결;;