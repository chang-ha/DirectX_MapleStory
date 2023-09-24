#pragma once
#include "GameEngineShaderResHelper.h"

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

	static bool AutoCompile(GameEngineFile& _File);

	// 각 쉐이더가 ResHelper를 들고있음
	GameEngineShaderResHelper ResHelper;

	ShaderType GetShaderType()
	{
		return ShaderTypeValue;
	}

protected:
	void CreateVersion(ShaderType _Type, UINT _VersionHigh, UINT _VersionLow);
	std::string Version;

	// 쉐이더의 바이너리 코드에 대한 포인터 (쉐이더 코드를 관리하기 위한 컴파일 포인터이다)
	ID3DBlob* BinaryCode = nullptr;

	std::string EntryName = "";

	void ShaderResCheck();
private:
	ShaderType ShaderTypeValue = ShaderType::None;
};

