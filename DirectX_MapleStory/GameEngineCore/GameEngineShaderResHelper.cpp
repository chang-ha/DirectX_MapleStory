#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"

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

void GameEngineShaderResHelper::ShaderResCheck(std::string _FunctionName, ID3DBlob* _CompileCode)
{
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
}