#pragma once

enum class ShaderType
{
	None, // None�� ���� üũ��
	Vertex, // �ʼ�
	Hull,
	Tessellator,
	Domain,
	Geometry,
	Pixel, // �ʼ�
	Max, // Max�� for�� üũ��
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

