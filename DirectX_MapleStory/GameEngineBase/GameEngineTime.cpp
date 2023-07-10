#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime GameEngineTime::MainTimer;

GameEngineTime::GameEngineTime() 
{
	QueryPerformanceFrequency(&Count);
	Reset();
}

GameEngineTime::~GameEngineTime() 
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Cur);
	Prev = Cur;
}

// 프레임 사이에서 실행되어야할 함수들은 다 업데이트라고 이름을 지을 것이다.
void GameEngineTime::Update() 
{
	QueryPerformanceCounter(&Cur);
	Tick = Cur.QuadPart - Prev.QuadPart;

	// 8바이트 실수형                  사이값        /          셀수있는 시간
	DoubleDelta = static_cast<double>(Tick) / static_cast<double>(Count.QuadPart);
	Prev.QuadPart = Cur.QuadPart;
	FloatDelta = static_cast<float>(DoubleDelta);
}