#include "PreCompile.h"
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

// ������ ���̿��� ����Ǿ���� �Լ����� �� ������Ʈ��� �̸��� ���� ���̴�.
void GameEngineTime::Update() 
{
	QueryPerformanceCounter(&Cur);
	Tick = Cur.QuadPart - Prev.QuadPart;

	// 8����Ʈ �Ǽ���                  ���̰�        /          �����ִ� �ð�
	DoubleDelta = static_cast<double>(Tick) / static_cast<double>(Count.QuadPart);
	Prev.QuadPart = Cur.QuadPart;
	FloatDelta = static_cast<float>(DoubleDelta);
}