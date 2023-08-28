#include "PreCompile.h"
#include "GameEngineTexture.h"
#include "GameEngineCore.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Release\\DirectXTex.lib")
#endif

GameEngineTexture::GameEngineTexture() 
{
}

GameEngineTexture::~GameEngineTexture() 
{
	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}

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

	HRESULT Result = GameEngineCore::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("랜더타겟뷰 생성에 실패했습니다.");
		return;
	}

}

void GameEngineTexture::ResLoad(std::string_view _Path)
{
	GameEnginePath NewPath = _Path;

	std::string Ext = GameEngineString::ToUpperReturn(NewPath.GetExtension());

	std::wstring wPath = GameEngineString::AnsiToUnicode(_Path);

	// 그래픽 
	if (Ext == ".DDS")
	{
		if (S_OK != DirectX::LoadFromDDSFile(wPath.c_str(), DirectX::DDS_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
		}
	}
	else if (Ext == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wPath.c_str(), DirectX::TGA_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
		}

	}
	else if (S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
	{
		MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
	}

	if (S_OK != DirectX::CreateShaderResourceView
	(
		GameEngineCore::GetDevice(),
		Image.GetImages(),
		Image.GetImageCount(),
		Image.GetMetadata(),
		&SRV
	))
	{
		MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
	}

	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height = static_cast<UINT>(Data.height);
}

void GameEngineTexture::VSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::PSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->PSSetShaderResources(_Slot, 1, &SRV);
}