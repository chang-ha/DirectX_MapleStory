#pragma once
#include "GameEngineShader.h"
#include "GameEngineResources.h"
 
// 점을 공간변환하기 위한 Shader 
class GameEngineVertexShader : public GameEngineResources<GameEngineVertexShader> , public GameEngineShader
{
	friend class GameEngineInputLayOut;
public:
	// constructer destructer
	GameEngineVertexShader();
	~GameEngineVertexShader();

	// delete function
	GameEngineVertexShader(const GameEngineVertexShader& _Ohter) = delete;
	GameEngineVertexShader(GameEngineVertexShader&& _Ohter) noexcept = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader& operator=(GameEngineVertexShader&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineVertexShader> Load(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		return Load(_Path, _EntryPoint, _EntryPoint, _VersionHight, _VersionLow);
	}

	static std::shared_ptr<GameEngineVertexShader> Load(std::string_view _Path, std::string_view _Name, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEngineVertexShader> Res = GameEngineVertexShader::CreateRes(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHight, _VersionLow);
		return Res;
	}

	void Setting();
protected:

private:
	ID3D11VertexShader* ShaderPtr = nullptr;

	void ShaderLoad(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0);
};

