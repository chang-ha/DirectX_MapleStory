#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

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
	// AutoCompile�ϸ鼭 ���� ConstantBuffer�� �������
	std::shared_ptr<GameEngineConstantBuffer> Res;

	// GPU������ �����͸� ���������� �����ְų� ���� ���ϱ� ������ (+= ������??)
	// ���� CPU�� �����ͼ� +=���� ������ �������
	// �׷��� �����Ϳ� ���� �����͸� ����ְ� ����
	const void* CPUDataPtr = nullptr;
	// ��������� ������
	UINT DataSize = -1;

	void Setting() override;
	void Reset() override;
};

class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	// AutoCompile�ϸ鼭 ���� Texture�� �������
	std::shared_ptr<GameEngineTexture> Res;
	void Setting() override;
	void Reset() override;
};

class GameEngineSamplerSetter : public GameEngineShaderResources
{
public:
	// AutoCompile�ϸ鼭 ���� Sampler�� �������
	std::shared_ptr<GameEngineSampler> Res;
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

	void ShaderResCheck(std::string _FunctionName, class GameEngineShader* _Shader, ID3DBlob* _CompileCode);

	bool IsConstantBuffer(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return ConstantBufferSetters.contains(UpperString);
	}

	bool IsTexture(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return TextureSetters.contains(UpperString);
	}

	bool IsSampler(std::string_view _Name)
	{
		std::string UpperString = GameEngineString::ToUpperReturn(_Name);

		return SamplerSetters.contains(UpperString);
	}

	void ShaderResCopy(class GameEngineShader* _Shader);

	void AllShaderResourcesReset();
	void AllShaderResourcesSetting();

	// ���⿡ ������ ���ϴ�.
	template<typename DataType>
	void SetConstantBufferLink(std::string_view _Name, const DataType& _Data)
	{
		SetConstantBufferLink(_Name, &_Data, sizeof(_Data));
	}

	void SetConstantBufferLink(std::string_view _Name, const void* _Data, size_t _Size);

	void SetTexture(std::string_view _Name, std::string_view _TextureName, bool _SamplerCheck = true);

	void SetTexture(std::string_view _Name, std::shared_ptr<GameEngineTexture> _TextureName, bool _SamplerCheck = true);

	void SetSampler(std::string_view _Name, std::string_view _SamplerName);

	void SetSampler(std::string_view _Name, std::shared_ptr<GameEngineSampler> _TextureSampler);

	void ResClear();

protected:

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSetters;
};

