#pragma once
#include "GameEngineShader.h"
#include "GameEngineResources.h"

// Ό³Έν :
class GameEngineGeometryShader : public GameEngineResources<GameEngineGeometryShader> , public GameEngineShader
{
	friend class GameEngineInputLayOut;

public:
	// constrcuter destructer
	GameEngineGeometryShader();
	~GameEngineGeometryShader();

	// delete Function
	GameEngineGeometryShader(const GameEngineGeometryShader& _Other) = delete;
	GameEngineGeometryShader(GameEngineGeometryShader&& _Other) noexcept = delete;
	GameEngineGeometryShader& operator=(const GameEngineGeometryShader& _Other) = delete;
	GameEngineGeometryShader& operator=(GameEngineGeometryShader&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineGeometryShader> Load(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		return Load(_Path, _EntryPoint, _EntryPoint, _VersionHight, _VersionLow);
	}

	static std::shared_ptr<GameEngineGeometryShader> Load(std::string_view _Path, std::string_view _Name, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEngineGeometryShader> Res = GameEngineGeometryShader::CreateRes(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHight, _VersionLow);
		return Res;
	}

	void Setting();

protected:

private:
	ID3D11PixelShader* ShaderPtr = nullptr;

	void ShaderLoad(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0);

};

