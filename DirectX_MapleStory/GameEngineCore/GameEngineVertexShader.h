#pragma once
#include "GameEngineShader.h"
 
// ���� ������ȯ�ϱ� ���� Shader 
class GameEngineVertexShader 
{
public:
	// constructer destructer
	GameEngineVertexShader();
	~GameEngineVertexShader();

	// delete function
	GameEngineVertexShader(const GameEngineVertexShader& _Ohter) = delete;
	GameEngineVertexShader(GameEngineVertexShader&& _Ohter) noexcept = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader& operator=(GameEngineVertexShader&& _Other) noexcept = delete;

protected:

private:

};

