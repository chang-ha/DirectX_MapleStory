#pragma once

class GameEngineShaderResources
{
public:
	std::string Name = ""; // 쉐이더에서 사용하는 리소스 이름 ex) TransformData
	class GameEngineShader* ParentShader = nullptr; // 해당 리소스를 사용하는 쉐이더가 누군지
	int BindPoint = -1; // b0 t0 s0 ... b1 s1 등 몇 번쨰 상수버퍼인지 (몇 번째 슬롯 사용)

public:
	virtual void Setting() = 0; // 순수 가상 함수
	virtual void Reset() = 0;
};

class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	void Setting() override;
	void Reset() override;
};

class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	void Setting() override;
	void Reset() override;
};

class GameEngineSamplerSetter : public GameEngineShaderResources
{
public:
	void Setting() override;
	void Reset() override;
};

// 설명 : 쉐이더 리소스 헬퍼는 2가지 역할을 한다.
//       1. 특정 쉐이더가 어떤 리소스들을 가지고 있느냐를 조사를 해주는 역할을
//       2. 특정 랜더러가 어떤 리소스들을 세팅해야하는지에 대한 역할 <= 멀티맵으로 해야한다.

class GameEngineShaderResHelper
{
public:
	// constructer destructer
	GameEngineShaderResHelper();
	~GameEngineShaderResHelper();

	// delete function
	GameEngineShaderResHelper(const GameEngineShaderResHelper& _Ohter) = delete;
	GameEngineShaderResHelper(GameEngineShaderResHelper&& _Ohter) noexcept = delete;
	GameEngineShaderResHelper& operator=(const GameEngineShaderResHelper& _Other) = delete;
	GameEngineShaderResHelper& operator=(GameEngineShaderResHelper&& _Other) noexcept = delete;

	void ShaderResCheck(std::string _FunctionName, ID3DBlob* _CompileCode);

protected:

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSetters;
};

