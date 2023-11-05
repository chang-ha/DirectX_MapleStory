#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

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
	// AutoCompile하면서 만든 ConstantBuffer을 들고있음
	std::shared_ptr<GameEngineConstantBuffer> Res;

	// GPU에서는 데이터를 순차적으로 더해주거나 하지 못하기 때문에 (+= 같은거??)
	// 따로 CPU로 가져와서 +=같은 연산을 해줘야함
	// 그래서 데이터에 대한 포인터를 들고있게 만듦
	const void* CPUDataPtr = nullptr;
	// 상수버퍼의 사이즈
	UINT DataSize = -1;

	void Setting() override;
	void Reset() override;
};

class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	// AutoCompile하면서 만든 Texture을 들고있음
	std::shared_ptr<GameEngineTexture> Res;
	void Setting() override;
	void Reset() override;
};

class GameEngineSamplerSetter : public GameEngineShaderResources
{
public:
	// AutoCompile하면서 만든 Sampler을 들고있음
	std::shared_ptr<GameEngineSampler> Res;
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

	// 여기에 값형만 들어갑니다.
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

