#pragma once
#include "GameEngineResources.h"
#include "GameEngineShader.h"

class GameEnginePixelShader : public GameEngineResources<GameEnginePixelShader>, public GameEngineShader
{
public:
	// constructer destructer
	GameEnginePixelShader();
	~GameEnginePixelShader();

	// delete function
	GameEnginePixelShader(const GameEnginePixelShader& _Ohter) = delete;
	GameEnginePixelShader(GameEnginePixelShader&& _Ohter) noexcept = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _Other) = delete;
	GameEnginePixelShader& operator=(GameEnginePixelShader&& _Other) noexcept = delete;

	static std::shared_ptr<GameEnginePixelShader> Load(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		return Load(_Path, _EntryPoint, _EntryPoint, _VersionHight, _VersionLow);
	}

	static std::shared_ptr<GameEnginePixelShader> Load(const std::string_view& _Path, const std::string_view& _Name, const std::string_view& _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		// std::shared_ptr<GameEnginePixelShader> Res = GameEnginePixelShader::CreateRes(_Name);
		std::shared_ptr<GameEnginePixelShader> Res = GameEngineResources::CreateRes(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHight, _VersionLow);
		return Res;
	}

	void Setting();
protected:

private:
	std::string EntryName = "";
	ID3D11PixelShader* ShaderPtr = nullptr;

	void ShaderLoad(const std::string_view& _Path, const std::string_view& _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0);
};

