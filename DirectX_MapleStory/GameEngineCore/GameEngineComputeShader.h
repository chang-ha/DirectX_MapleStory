#pragma once
#include "GameEngineShader.h"
#include "GameEngineResources.h"

// Ό³Έν :
class GameEngineComputeShader : public GameEngineResources<GameEngineComputeShader> , public GameEngineShader
{
	friend class GameEngineInputLayOut;

public:
	// constrcuter destructer
	GameEngineComputeShader();
	~GameEngineComputeShader();

	// delete Function
	GameEngineComputeShader(const GameEngineComputeShader& _Other) = delete;
	GameEngineComputeShader(GameEngineComputeShader&& _Other) noexcept = delete;
	GameEngineComputeShader& operator=(const GameEngineComputeShader& _Other) = delete;
	GameEngineComputeShader& operator=(GameEngineComputeShader&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineComputeShader> Load(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		return Load(_Path, _EntryPoint, _EntryPoint, _VersionHight, _VersionLow);
	}

	static std::shared_ptr<GameEngineComputeShader> Load(std::string_view _Path, std::string_view _Name, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0)
	{
		std::shared_ptr<GameEngineComputeShader> Res = GameEngineComputeShader::CreateRes(_Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHight, _VersionLow);
		return Res;
	}

	void Setting();

protected:

private:
	ID3D11ComputeShader* ShaderPtr = nullptr;

	void ShaderLoad(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHight = 5, UINT _VersionLow = 0);

};

