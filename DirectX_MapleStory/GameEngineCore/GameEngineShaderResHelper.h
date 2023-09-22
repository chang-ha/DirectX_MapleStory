#pragma once

class GameEngineShaderResources
{
public:
	std::string Name = ""; // ���̴����� ����ϴ� ���ҽ� �̸� ex) TransformData
	class GameEngineShader* ParentShader = nullptr; // �ش� ���ҽ��� ����ϴ� ���̴��� ������
	int BindPoint = -1; // b0 t0 s0 ... b1 s1 �� �� ���� ����������� (�� ��° ���� ���)

public:
	virtual void Setting() = 0; // ���� ���� �Լ�
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

// ���� : ���̴� ���ҽ� ���۴� 2���� ������ �Ѵ�.
//       1. Ư�� ���̴��� � ���ҽ����� ������ �ִ��ĸ� ���縦 ���ִ� ������
//       2. Ư�� �������� � ���ҽ����� �����ؾ��ϴ����� ���� ���� <= ��Ƽ������ �ؾ��Ѵ�.

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

