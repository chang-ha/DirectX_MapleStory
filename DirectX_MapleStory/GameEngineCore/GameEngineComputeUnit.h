#pragma once

class GameEngineComputeUnit
{
public:
	// constrcuter destructer
	GameEngineComputeUnit();
	~GameEngineComputeUnit();

	UINT                            GroupX = 1;
	UINT                            GroupY = 1;
	UINT                            GroupZ = 1;
	GameEngineShaderResHelper ShaderResHelper;

	//// 128
	//UINT                      m_iGroupPerThreadX = 1;
	//UINT                      m_iGroupPerThreadY = 1;
	//UINT                      m_iGroupPerThreadZ = 1;

	// delete Function
	GameEngineComputeUnit(const GameEngineComputeUnit& _Other) = delete;
	GameEngineComputeUnit(GameEngineComputeUnit&& _Other) noexcept = delete;
	GameEngineComputeUnit& operator=(const GameEngineComputeUnit& _Other) = delete;
	GameEngineComputeUnit& operator=(GameEngineComputeUnit&& _Other) noexcept = delete;

	void SetComputeShader(std::string_view _Name);

	void Excute();

private:
	std::shared_ptr<class GameEngineComputeShader> ComputeShader = nullptr;
};

