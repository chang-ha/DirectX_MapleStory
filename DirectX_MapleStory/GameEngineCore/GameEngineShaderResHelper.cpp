#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineShader.h"

void GameEngineConstantBufferSetter::Setting()
{
	// CBuffer 세팅안해주면 터트림
	if (nullptr == CPUDataPtr)
	{
		MsgBoxAssert(Name + "상수버퍼를 세팅해주지 않았습니다.");
	}

	// CPU에 있는 Data의 포인터와 사이즈로 세팅해줌
	Res->ChangeData(CPUDataPtr, DataSize);

	// 쉐이더 타입에 따라 VertexShader에 세팅할지 PixelShader에 세팅할지 결정 
	ShaderType Type = ParentShader->GetShaderType();
	switch (Type)
	{
	case ShaderType::Vertex:
		Res->VSSetting(BindPoint);
		break;
	case ShaderType::Pixel:
		Res->PSSetting(BindPoint);
		break;
	default:
		MsgBoxAssert("처리할수 없는 쉐이더 세팅 유형입니다.");
		break;
	}
}

void GameEngineConstantBufferSetter::Reset()
{

}

void GameEngineTextureSetter::Setting()
{
	ShaderType Type = ParentShader->GetShaderType();

	switch (Type)
	{
	case ShaderType::Vertex:
		Res->VSSetting(BindPoint);
		break;
	case ShaderType::Pixel:
		Res->PSSetting(BindPoint);
		break;
	default:
		MsgBoxAssert("처리할수 없는 쉐이더 세팅 유형입니다.");
		break;
	}
}

void GameEngineTextureSetter::Reset()
{

}

void GameEngineSamplerSetter::Setting()
{
	ShaderType Type = ParentShader->GetShaderType();

	switch (Type)
	{
	case ShaderType::Vertex:
		Res->VSSetting(BindPoint);
		break;
	case ShaderType::Pixel:
		Res->PSSetting(BindPoint);
		break;
	default:
		MsgBoxAssert("처리할수 없는 쉐이더 세팅 유형입니다.");
		break;
	}
}

void GameEngineSamplerSetter::Reset()
{

}

GameEngineShaderResHelper::GameEngineShaderResHelper()
{

}

GameEngineShaderResHelper::~GameEngineShaderResHelper()
{

}

void GameEngineShaderResHelper::ShaderResCheck(std::string _FunctionName, GameEngineShader* _Shader, ID3DBlob* _CompileCode)
{
	// 이 함수에서 이제 쉐이더 자동화를 할 것임
	// 여기서 쉐이더 코드들을 보면서 필요한 상수버퍼, Texture, Sampler등등을 만들어 줄 것임

	// _CompileCode == Shader에서의 BinaryCode (VertexShader)
	if (nullptr == _CompileCode)
	{
		MsgBoxAssert("컴파일 되지 않은 코드로는 쉐이더의 리소스를 조사할수가 없습니다.");
		return;
	}

	ID3DBlob* BinaryCode = _CompileCode;
	// 리플렉션을 통해서 얻어내는 것은 코드 그자체의 정보를 의미한다.
	// 클래스 개수
	// 함수
	// 클래스의 타입
	// 상속은 받았느니? 
	// 등등 해당 쉐이더 코드가 어떻게 구성되어 있는지에 대한 정보가 들어있다.
	ID3D11ShaderReflection* CompileInfo = nullptr;
	if (S_OK != D3DReflect(BinaryCode->GetBufferPointer(), BinaryCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgBoxAssert("쉐이더 정보수집에 실패했습니다.");
		return;
	}

	// 해당 Shader의 통합 정보를 컴파일 인포에서 받았음
	D3D11_SHADER_DESC Info;
	CompileInfo->GetDesc(&Info);

	// 해당 Shader에서 사용한 리소스들의 Desc값을 받는다
	D3D11_SHADER_INPUT_BIND_DESC ResDesc;

	// 컴파일 인포에서 확인한 사용된 리소스들의 갯수만큼 for문을 돌면서
	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		// i번째 리소스의 Desc정보를 받음
		CompileInfo->GetResourceBindingDesc(i, &ResDesc);
		// 해당 리소스의 이름을 받음
		std::string UpperName = GameEngineString::ToUpperReturn(ResDesc.Name);
		// 해당 리소스의 타입을 받음 (우리가 현재 사용중인 것은 상수버퍼, Texture, Sampler)
		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			// 해당 리소스 타입이 상수버퍼면 상수버퍼의 정보를 가져옴
			ID3D11ShaderReflectionConstantBuffer* BufferInfo = CompileInfo->GetConstantBufferByName(ResDesc.Name);
			// 해당 상수버퍼의 Desc를 가져옴
			D3D11_SHADER_BUFFER_DESC BufferDesc;
			BufferInfo->GetDesc(&BufferDesc);
			// 해당 정보로 ConstantBuffer를 만듦
			std::shared_ptr<GameEngineConstantBuffer> CBuffer = GameEngineConstantBuffer::CreateAndFind(BufferDesc.Size, UpperName, BufferDesc);

			// 새로운 ShaderResHelper의 ConstantBufferSetter를 만듦
			GameEngineConstantBufferSetter NewSetter;
			// 나를 사용한 Shader가 누군지를 알고 있음
			NewSetter.ParentShader = _Shader;
			// 새로 만든 ConstantBuffer를 들고 있음
			NewSetter.Res = CBuffer;
			NewSetter.Name = UpperName;
			NewSetter.BindPoint = ResDesc.BindPoint;
			NewSetter.DataSize = BufferDesc.Size;
			ConstantBufferSetters.insert(std::make_pair(UpperName, NewSetter));
			break;
		}
		case D3D_SIT_TEXTURE:
		{
			// 여기서 Texture를 기본 Texture인 NSet.png로 세팅하지만 밖에서 따로 또 Texture를 바꿔줄수 있음
			// == 내가 Texture를 새로 세팅하지 않으면 기본 이미지가 출력되게 만듦
			std::shared_ptr<GameEngineTexture> Res = GameEngineTexture::Find("NSet.png");

			GameEngineTextureSetter NewSetter;
			NewSetter.ParentShader = _Shader;
			NewSetter.Res = Res;
			NewSetter.Name = UpperName;
			NewSetter.BindPoint = ResDesc.BindPoint;
			TextureSetters.insert(std::make_pair(UpperName, NewSetter));
			break;
		}
		case D3D_SIT_SAMPLER:
		{
			// 샘플러는 최초에 기본 Sampler로 세팅됨 (Texture를 세팅하면 자동으로 Sampler가 바뀜) 
			// == 각 Texture내부에 Sampler를 들고있음
			// std::shared_ptr<GameEngineSampler> Res = GameEngineSampler::Find("EngineBaseSampler");

			GameEngineSamplerSetter NewSetter;
			NewSetter.ParentShader = _Shader;
			// Sampler는 Texture가 Load될 떄 자동으로 세팅되지만 만약 세팅되지 않으면 터지도록 만듦
			NewSetter.Res = nullptr;
			NewSetter.Name = UpperName;
			NewSetter.BindPoint = ResDesc.BindPoint;
			SamplerSetters.insert(std::make_pair(UpperName, NewSetter));
			break;
		}
		default:
			break;
		}
	}
}

void GameEngineShaderResHelper::ShaderResCopy(GameEngineShader* _Shader)
{
	// 해당 Shader를 조사한 ResHelper에 있는 정보들을 Renderer가 SetMaterial을 할 떄 값들을 복사해옴
	std::multimap<std::string, GameEngineConstantBufferSetter>& OtherConstantBufferSetters = _Shader->ResHelper.ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter>& OtherTextureSetters = _Shader->ResHelper.TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter>& OtherSamplerSetters = _Shader->ResHelper.SamplerSetters;

	for (std::pair<const std::string, GameEngineConstantBufferSetter>& Pair : OtherConstantBufferSetters)
	{
		ConstantBufferSetters.insert(std::make_pair(Pair.first, Pair.second));
	}

	for (std::pair<const std::string, GameEngineTextureSetter>& Pair : OtherTextureSetters)
	{
		TextureSetters.insert(std::make_pair(Pair.first, Pair.second));
	}

	for (std::pair<const std::string, GameEngineSamplerSetter>& Pair : OtherSamplerSetters)
	{
		SamplerSetters.insert(std::make_pair(Pair.first, Pair.second));
	}

	// 방어코드
	// 기본 샘플러로 세팅해줘야할 녀석들이 있는지 확인한다.
	for (std::pair<const std::string, GameEngineTextureSetter>& Pair : OtherTextureSetters)
	{
		std::string SamplerName = Pair.first + "SAMPLER";

		if (true == IsSampler(SamplerName))
		{
			std::shared_ptr<GameEngineSampler> Sampler = Pair.second.Res->GetBaseSampler();

			SetSampler(SamplerName, Sampler);
		}
	}
}

void GameEngineShaderResHelper::AllShaderResourcesSetting()
{
	// 모든 ConstantBuffer, Texture, Sampler를 돌면서 Setting()함수 호출
	for (std::pair<const std::string, GameEngineConstantBufferSetter>& Pair : ConstantBufferSetters)
	{
		if (nullptr == Pair.second.Res)
		{
			MsgBoxAssert(std::string(Pair.first) + "라는 샘플러가 세팅이 되지 않았습니다.");
			return;
		}

		Pair.second.Setting();
	}

	for (std::pair<const std::string, GameEngineTextureSetter>& Pair : TextureSetters)
	{
		if (nullptr == Pair.second.Res)
		{
			MsgBoxAssert(std::string(Pair.first) + "라는 샘플러가 세팅이 되지 않았습니다.");
			return;
		}

		Pair.second.Setting();
	}

	for (std::pair<const std::string, GameEngineSamplerSetter>& Pair : SamplerSetters)
	{
		if (nullptr == Pair.second.Res)
		{
			MsgBoxAssert(std::string(Pair.first) + "라는 샘플러가 세팅이 되지 않았습니다.");
			return;
		}

		Pair.second.Setting();
	}
}

void GameEngineShaderResHelper::SetConstantBufferLink(std::string_view _Name, const void* _Data, size_t _Size)
{
	if (false == IsConstantBuffer(_Name))
	{
		MsgBoxAssert(std::string(_Name) + "존재하지 않는 상수버퍼에 링크를 걸려고 했습니다.");
		return;
	}

	std::string UpperString = GameEngineString::ToUpperReturn(_Name);

	// 중복되는 이름의 시작 이터레이터와 끝 이터레이터를 찾는법
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameStariter
		= ConstantBufferSetters.lower_bound(UpperString);
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameEnditer
		= ConstantBufferSetters.upper_bound(UpperString);

	for (; NameStariter != NameEnditer; ++NameStariter)
	{
		GameEngineConstantBufferSetter& Setter = NameStariter->second;
		// 세팅하려는 상수버퍼의 크기와 찾은 상수버퍼의 크기가 같아야함
		if (Setter.DataSize != _Size)
		{
			MsgBoxAssert(NameStariter->first + "상수버퍼에 크기가 다른 데이터를 세팅하려고 했습니다.");
		}
		// ShaderResHelper의 상수버퍼에 Data 포인터를 세팅
		Setter.CPUDataPtr = _Data;
	}
}


void GameEngineShaderResHelper::SetTexture(std::string_view _Name, std::string_view _TextureName)
{
	std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Find(_TextureName);
	if (nullptr == Tex)
	{
		MsgBoxAssert("존재하지 않는 텍스처 입니다.");
	}

	SetTexture(_Name, Tex);
}

void GameEngineShaderResHelper::SetTexture(std::string_view _Name, std::shared_ptr<GameEngineTexture> _Texture)
{
	if (false == IsTexture(_Name))
	{
		MsgBoxAssert("존재하지 않는 텍스처를 세팅하려고 했습니다.");
		return;
	}

	std::string UpperString = GameEngineString::ToUpperReturn(_Name);

	std::multimap<std::string, GameEngineTextureSetter>::iterator NameStariter
		= TextureSetters.lower_bound(UpperString);
	std::multimap<std::string, GameEngineTextureSetter>::iterator NameEnditer
		= TextureSetters.upper_bound(UpperString);

	// Shader코드 규칙준수 바람
	std::string SamplerName = NameStariter->first + "SAMPLER";

	for (; NameStariter != NameEnditer; ++NameStariter)
	{
		GameEngineTextureSetter& Setter = NameStariter->second;
		Setter.Res = _Texture;

		if (true == IsSampler(SamplerName))
		{
			// Texture가 세팅될 때 Sampler도 같이 세팅됨
			std::shared_ptr<GameEngineSampler> Sampler = Setter.Res->GetBaseSampler();
			SetSampler(SamplerName, Sampler);
		}
	}
}

void GameEngineShaderResHelper::SetSampler(std::string_view _Name, std::shared_ptr<GameEngineSampler> _TextureSampler)
{
	if (false == IsSampler(_Name))
	{
		MsgBoxAssert("존재하지 않는 샘플러를 세팅하려고 했습니다.");
		return;
	}

	std::string UpperString = GameEngineString::ToUpperReturn(_Name);

	std::multimap<std::string, GameEngineSamplerSetter>::iterator NameStariter
		= SamplerSetters.lower_bound(UpperString);
	std::multimap<std::string, GameEngineSamplerSetter>::iterator NameEnditer
		= SamplerSetters.upper_bound(UpperString);

	for (; NameStariter != NameEnditer; ++NameStariter)
	{
		GameEngineSamplerSetter& Setter = NameStariter->second;
		Setter.Res = _TextureSampler;
	}
}

void GameEngineShaderResHelper::ResClear()
{
	ConstantBufferSetters.clear();
	TextureSetters.clear();
	SamplerSetters.clear();
}