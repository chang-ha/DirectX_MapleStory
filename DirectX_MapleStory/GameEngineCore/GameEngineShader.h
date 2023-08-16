#pragma once

enum class ShaderType
{
	None, // None은 에러 체크용
	Vertex, // 필수
	Hull,
	Tessellator,
	Domain,
	Geometry,
	Pixel, // 필수
	Max, // Max는 for문 체크용
};

class GameEngineShader
{
public:
	// constructer destructer
	GameEngineShader();
	~GameEngineShader();

	// delete function
	GameEngineShader(const GameEngineShader& _Ohter) = delete;
	GameEngineShader(GameEngineShader&& _Ohter) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _Other) = delete;
	GameEngineShader& operator=(GameEngineShader&& _Other) noexcept = delete;


protected:

private:
	ShaderType ShaderTypeValue = ShaderType::None;
};

