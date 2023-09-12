#include "PreCompile.h"
#include "GameEngineBlend.h"

GameEngineBlend::GameEngineBlend()
{
	
}

GameEngineBlend::~GameEngineBlend()
{
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}
}

void GameEngineBlend::ResCreate(const D3D11_BLEND_DESC& _Desc)
{
	Desc = _Desc;
	if (S_OK != GameEngineCore::GetDevice()->CreateBlendState(&_Desc, &State))
	{
		MsgBoxAssert("���� ������ ����µ� �����߽��ϴ�.");
	}
}

void GameEngineBlend::Setting()
{
	if (nullptr == State)
	{
		MsgBoxAssert("���� ������ �������� �۴µ� �����Ϸ��� �߽��ϴ�.");
	}

	GameEngineCore::GetContext()->OMSetBlendState(State, Factor.Arr1D, Mask);
}