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
		MsgBoxAssert("레스터라이저 세팅을 만드는데 실패했습니다.");
	}
}

void GameEngineDepthStencil::Setting()
{
	if (nullptr == State)
	{
		MsgBoxAssert("레스터 라이저 세팅이 존재하지 앟는데 세팅하려고 했습니다.");
	}

	GameEngineCore::GetContext()->OMSetDepthStencilState(State, 0);
}