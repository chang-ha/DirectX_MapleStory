#include "PreCompile.h"
#include "GameEngineTexture.h"
#include "GameEngineCore.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Release\\DirectXTex.lib")
#endif

const GameEngineColor GameEngineColor::RED = { 255, 0, 0, 255 };

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

// 쉐이더 세팅용
void GameEngineTexture::CreateShaderResourceView()
{
	if (nullptr != SRV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 쉐이더 리소스 뷰 생성하려고 했습니다.");
		return;
	}

	HRESULT Result = GameEngineCore::GetDevice()->CreateShaderResourceView(Texture2D, nullptr, &SRV);

	if (S_OK != Result)
	{
		MsgBoxAssert("쉐이더 리소스 뷰 생성에 실패했습니다.");
		return;
	}

}

// 깊이버퍼 세팅용
void GameEngineTexture::CreateDepthStencilView()
{
	if (nullptr != DSV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 깊이버퍼를 생성하려고 했습니다.");
		return;
	}

	HRESULT Result = GameEngineCore::GetDevice()->CreateDepthStencilView(Texture2D, nullptr, &DSV);

	if (S_OK != Result)
	{
		MsgBoxAssert("깊이버퍼 생성에 실패했습니다.");
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

void GameEngineTexture::ResCreate(ID3D11Texture2D* _Res)
{
	Texture2D = _Res;
	Texture2D->GetDesc(&Desc);
	CreateRenderTargetView();
}

void GameEngineTexture::ResCreate(const D3D11_TEXTURE2D_DESC& _Desc)
{
	Desc = _Desc;

	if (S_OK != GameEngineCore::GetDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D))
	{
		MsgBoxAssert("if (S_OK != GameEngineCore::GetDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D))");
	}

	if (D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET & Desc.BindFlags)
	{
		CreateRenderTargetView();
	}

	if (D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE & Desc.BindFlags)
	{
		CreateShaderResourceView();
	}

	if (D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL & Desc.BindFlags)
	{
		CreateDepthStencilView();
	}
}

GameEngineColor GameEngineTexture::GetColor(unsigned int _X, unsigned int _Y, GameEngineColor _DefaultColor)
{
	if (0 > _X)
	{
		return _DefaultColor;
	}

	if (0 > _Y)
	{
		return _DefaultColor;
	}

	if (_X >= GetScale().uiX())
	{
		return _DefaultColor;
	}

	if (_Y >= GetScale().uiY())
	{
		return _DefaultColor;
	}

	// GetPixels함수는 이미지의 첫번째 픽셀칸의 1바이트 포인터로 줌(유저가 무슨 포맷을 쓸 지 모르니까 알아서 변형해서 써야함)
	// 내가 4바이트 짜리 이미지 포맷을 쓸지, 8바이트 이미지 포맷을 쓸지 모르니 1바이트 포인터로 줌 (1번째 픽셀의 첫번쨰 Color값, R8G8B8A8 -> 4바이트 포맷에서 R이 맨 앞이니 R의 주소값)
	unsigned char* Ptr = Image.GetPixels();
	DXGI_FORMAT Fmt = Image.GetMetadata().format;

	switch (Fmt)
	{
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	{
		GameEngineColor ResultColor;
		Ptr += ((_Y * GetScale().iX()) + _X) * 4;
		ResultColor.B = Ptr[0];
		ResultColor.G = Ptr[1];
		ResultColor.R = Ptr[2];
		ResultColor.A = Ptr[3];
		return ResultColor;
	}
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UINT:
	case DXGI_FORMAT_R8G8B8A8_SNORM:
	case DXGI_FORMAT_R8G8B8A8_SINT:
	{
		GameEngineColor ResultColor;
		Ptr += ((_Y * GetScale().iX()) + _X) * 4; // 4바이트 포맷이라서 *4
		ResultColor.R = Ptr[0];
		ResultColor.G = Ptr[1];
		ResultColor.B = Ptr[2];
		ResultColor.A = Ptr[3];
		return ResultColor;
	}
	default:
		MsgBoxAssert("색깔을 처리하는 함수를 만들지 없는 포맷입니다");
		break;
	}

	return _DefaultColor;
}