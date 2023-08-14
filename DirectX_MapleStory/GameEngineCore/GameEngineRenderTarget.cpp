#include "PreCompile.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineCore.h"

GameEngineRenderTarget::GameEngineRenderTarget()
{
}

GameEngineRenderTarget::~GameEngineRenderTarget()
{
}

void GameEngineRenderTarget::Clear()
{
	for (size_t i = 0; i < RTV.size(); i++)
	{
		GameEngineCore::MainDevice.GetContext()->ClearRenderTargetView(RTV[i], ClearColor[i].Arr1D);
	}
}

void GameEngineRenderTarget::Setting()
{
	if (0 >= RTV.size())
	{
		MsgBoxAssert("만들어지지 않은 랜더타겟을 세팅하려고 했습니다.");
		return;
	}

	GameEngineCore::MainDevice.GetContext()->OMSetRenderTargets(static_cast<UINT>(RTV.size()), &RTV[0], nullptr);
}
