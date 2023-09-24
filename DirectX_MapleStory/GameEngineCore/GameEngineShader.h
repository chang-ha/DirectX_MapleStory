#pragma once
#include "GameEngineShaderResHelper.h"

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

	static bool AutoCompile(GameEngineFile& _File);

	// �� ���̴��� ResHelper�� �������
	GameEngineShaderResHelper ResHelper;

	ShaderType GetShaderType()
	{
		return ShaderTypeValue;
	}

protected:
	void CreateVersion(ShaderType _Type, UINT _VersionHigh, UINT _VersionLow);
	std::string Version;

	// ���̴��� ���̳ʸ� �ڵ忡 ���� ������ (���̴� �ڵ带 �����ϱ� ���� ������ �������̴�)
	ID3DBlob* BinaryCode = nullptr;

	std::string EntryName = "";

	void ShaderResCheck();
private:
	ShaderType ShaderTypeValue = ShaderType::None;
};

