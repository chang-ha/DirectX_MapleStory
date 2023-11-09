#pragma once

class GameEngineStructuredBuffer
{
public:
	// constructer destructer
	GameEngineStructuredBuffer();
	~GameEngineStructuredBuffer();

	// delete function
	GameEngineStructuredBuffer(const GameEngineStructuredBuffer& _Ohter) = delete;
	GameEngineStructuredBuffer(GameEngineStructuredBuffer&& _Ohter) noexcept = delete;
	GameEngineStructuredBuffer& operator=(const GameEngineStructuredBuffer& _Other) = delete;
	GameEngineStructuredBuffer& operator=(GameEngineStructuredBuffer&& _Other) noexcept = delete;

protected:

private:

};

