#include "PreCompile.h"
#include "GameEngineComputeUnit.h"
#include "GameEngineComputeShader.h"

GameEngineComputeUnit::GameEngineComputeUnit()
{

}

GameEngineComputeUnit::~GameEngineComputeUnit()
{

}

void GameEngineComputeUnit::SetComputeShader(std::string_view _Name)
{
	ComputeShader = GameEngineComputeShader::Find(_Name);

	if (nullptr == ComputeShader)
	{
		MsgBoxAssert(std::string(_Name) + "존재하지 않는 컴퓨트 쉐이더를 세팅하려고 했습니다");
	}

	ShaderResHelper.ShaderResCopy(ComputeShader.get());
}

void GameEngineComputeUnit::Excute()
{
	ShaderResHelper.AllShaderResourcesSetting();

	ComputeShader->Setting();
	GameEngineCore::GetContext()->Dispatch(GroupX, GroupY, GroupZ);

	ShaderResHelper.AllShaderResourcesReset();
}
