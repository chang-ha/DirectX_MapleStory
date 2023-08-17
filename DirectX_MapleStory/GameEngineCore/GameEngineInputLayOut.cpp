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
	//const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, ���ؽ��� ��������
	//UINT NumElements, ���������� ����
	//const void* pShaderBytecodeWithInputSignature, // ���̴� �ڵ�
	//SIZE_T BytecodeLength, ���̴� �ڵ� ����
	//ID3D11InputLayout** ppInputLayout // �׷��� ������� ������

	// D3D11_INPUT_ELEMENT_DESC InputElementDescs[20];
	// pShaderBytecodeWithInputSignature ���̴� �ڵ� �޶�� �ϴ� �̴ϴ�.

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
		MsgBoxAssert("����������� ���� ���ؽ� ���۸� ������ ���� �����ϴ�.");
	}

	// ���ؽ����۸� ������ �־��ټ� �ִ�.
	GameEngineCore::MainDevice.GetContext()->IASetInputLayout(LayOut);
}