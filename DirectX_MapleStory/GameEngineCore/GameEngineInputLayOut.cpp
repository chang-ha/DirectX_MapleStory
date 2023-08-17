#include "PreCompile.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineVertexShader.h"

GameEngineInputLayOut::GameEngineInputLayOut() 
{
}

GameEngineInputLayOut::~GameEngineInputLayOut() 
{
	if (nullptr != LayOut)
	{
		LayOut->Release();
		LayOut = nullptr;
	}
}

void GameEngineInputLayOut::ResCreate(const std::vector<D3D11_INPUT_ELEMENT_DESC>& _ArrLayOutInfo, std::shared_ptr<class GameEngineVertexShader> _Shader)
{
	//const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, 버텍스의 형태정보
	//UINT NumElements, 형태정보의 개수
	//const void* pShaderBytecodeWithInputSignature, // 쉐이더 코드
	//SIZE_T BytecodeLength, 쉐이더 코드 길이
	//ID3D11InputLayout** ppInputLayout // 그렇게 만들어질 포인터

	// D3D11_INPUT_ELEMENT_DESC InputElementDescs[20];
	// pShaderBytecodeWithInputSignature 쉐이더 코드 달라고 하는 겁니다.

	// GameEngineCore::MainDevcie.GetDevice()->CreateInputLayout(InputElementDescs, 20,  &LayOut);

	GameEngineCore::MainDevice.GetDevice()->CreateInputLayout(
		&_ArrLayOutInfo[0],
		_ArrLayOutInfo.size(),
		_Shader->BinaryCode->GetBufferPointer(),
		_Shader->BinaryCode->GetBufferSize(),
		&LayOut);
}

void GameEngineInputLayOut::Setting()
{
	if (nullptr == LayOut)
	{
		MsgBoxAssert("만들어지지도 않은 버텍스 버퍼를 세팅할 수는 없습니다.");
	}

	// 버텍스버퍼를 여러개 넣어줄수 있다.
	GameEngineCore::MainDevice.GetContext()->IASetInputLayout(LayOut);
}