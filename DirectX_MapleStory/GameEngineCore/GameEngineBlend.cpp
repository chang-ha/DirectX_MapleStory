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
		MsgBoxAssert("블랜드 세팅을 만드는데 실패했습니다.");
	}
}

void GameEngineBlend::Setting()
{
	if (nullptr == State)
	{
		MsgBoxAssert("블랜드 세팅이 존재하지 앟는데 세팅하려고 했습니다.");
	}

	GameEngineCore::GetContext()->OMSetBlendState(State, Factor.Arr1D, Mask);
}