#include "PreCompile.h"
#include "GameEngineDepthStencil.h"

GameEngineDepthStencil::GameEngineDepthStencil()
{
}

GameEngineDepthStencil::~GameEngineDepthStencil()
{
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}
}

void GameEngineDepthStencil::ResCreate(const D3D11_DEPTH_STENCIL_DESC& _Desc)
{
	Desc = _Desc;
	if (S_OK != GameEngineCore::GetDevice()->CreateDepthStencilState(&Desc, &State))
	{
		MsgBoxAssert("�����Ͷ����� ������ ����µ� �����߽��ϴ�.");
	}
}

void GameEngineDepthStencil::Setting()
{
	if (nullptr == State)
	{
		MsgBoxAssert("������ ������ ������ �������� �۴µ� �����Ϸ��� �߽��ϴ�.");
	}

	GameEngineCore::GetContext()->OMSetDepthStencilState(State, 0);
}