#include "PreCompile.h"
#include "GameEngineDirectBuffer.h"

GameEngineDirectBuffer::GameEngineDirectBuffer()
{
}

GameEngineDirectBuffer::~GameEngineDirectBuffer()
{
	BufferRelease();
}

void GameEngineDirectBuffer::BufferRelease()
{
	if (nullptr != Buffer)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}