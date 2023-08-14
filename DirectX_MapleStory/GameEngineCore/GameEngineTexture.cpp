#include "PreCompile.h"
#include "GameEngineTexture.h"
#include "GameEngineCore.h"

GameEngineTexture::GameEngineTexture() 
{
}

GameEngineTexture::~GameEngineTexture() 
{
	if (nullptr != RTV)
	{
		RTV->Release();
		RTV = nullptr;
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
	}
}

void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RTV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("��������� ���� �ؽ�ó�� ����Ÿ�ٺ並 �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// �̹����� �����Ҽ� �ִ� ������ '�����'

	HRESULT Result = GameEngineCore::MainDevice.GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("����Ÿ�ٺ� ������ �����߽��ϴ�.");
		return;
	}

}