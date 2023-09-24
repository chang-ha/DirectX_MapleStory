#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineConstantBuffer.h"

void GameEngineConstantBufferSetter::Setting()
{

}

void GameEngineConstantBufferSetter::Reset()
{

}

void GameEngineTextureSetter::Setting()
{

}

void GameEngineTextureSetter::Reset()
{

}

void GameEngineSamplerSetter::Setting()
{

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
			std::shared_ptr<GameEngineSampler> Res = GameEngineSampler::Find("EngineBaseSampler");

			GameEngineSamplerSetter NewSetter;
			NewSetter.ParentShader = _Shader;
			NewSetter.Res = Res;
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