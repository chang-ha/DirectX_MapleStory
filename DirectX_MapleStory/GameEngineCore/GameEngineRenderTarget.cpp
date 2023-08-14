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
		MsgBoxAssert("��������� ���� ����Ÿ���� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	GameEngineCore::MainDevice.GetContext()->OMSetRenderTargets(static_cast<UINT>(RTV.size()), &RTV[0], nullptr);
}
