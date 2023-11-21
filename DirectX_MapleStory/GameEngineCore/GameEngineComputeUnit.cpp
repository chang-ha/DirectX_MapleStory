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
		MsgBoxAssert(std::string(_Name) + "�������� �ʴ� ��ǻƮ ���̴��� �����Ϸ��� �߽��ϴ�");
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
