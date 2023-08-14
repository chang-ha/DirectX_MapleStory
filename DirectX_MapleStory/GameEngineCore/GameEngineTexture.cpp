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
		MsgBoxAssert("만들어지지 않은 텍스처로 랜더타겟뷰를 생성하려고 했습니다.");
		return;
	}

	// 이미지를 수정할수 있는 권한을 '만든다'

	HRESULT Result = GameEngineCore::MainDevice.GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("랜더타겟뷰 생성에 실패했습니다.");
		return;
	}

}