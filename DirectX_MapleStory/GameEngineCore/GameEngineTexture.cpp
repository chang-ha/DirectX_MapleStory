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
		MsgBoxAssert("��������� ���� �ؽ�ó�� ����Ÿ�ٺ並 �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// �̹����� �����Ҽ� �ִ� ������ '�����'

	HRESULT Result = GameEngineCore::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("����Ÿ�ٺ� ������ �����߽��ϴ�.");
		return;
	}

}

void GameEngineTexture::ResLoad(std::string_view _Path)
{
	GameEnginePath NewPath = _Path;

	std::string Ext = GameEngineString::ToUpperReturn(NewPath.GetExtension());

	std::wstring wPath = GameEngineString::AnsiToUnicode(_Path);

	// �׷��� 
	if (Ext == ".DDS")
	{
		if (S_OK != DirectX::LoadFromDDSFile(wPath.c_str(), DirectX::DDS_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("�ؽ�ó �ε忡 �����߽��ϴ�." + std::string(_Path.data()));
		}
	}
	else if (Ext == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wPath.c_str(), DirectX::TGA_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("�ؽ�ó �ε忡 �����߽��ϴ�." + std::string(_Path.data()));
		}

	}
	else if (S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
	{
		MsgBoxAssert("�ؽ�ó �ε忡 �����߽��ϴ�." + std::string(_Path.data()));
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
		MsgBoxAssert("�ؽ�ó �ε忡 �����߽��ϴ�." + std::string(_Path.data()));
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

	// GetPixels�Լ��� �̹����� ù��° �ȼ�ĭ�� 1����Ʈ �����ͷ� ��(������ ���� ������ �� �� �𸣴ϱ� �˾Ƽ� �����ؼ� �����)
	// ���� 4����Ʈ ¥�� �̹��� ������ ����, 8����Ʈ �̹��� ������ ���� �𸣴� 1����Ʈ �����ͷ� �� (1��° �ȼ��� ù���� Color��, R8G8B8A8 -> 4����Ʈ ���˿��� R�� �� ���̴� R�� �ּҰ�)
	unsigned char* Ptr = Image.GetPixels();
	DXGI_FORMAT Fmt = Image.GetMetadata().format;

	switch (Fmt)
	{
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UINT:
	case DXGI_FORMAT_R8G8B8A8_SNORM:
	case DXGI_FORMAT_R8G8B8A8_SINT:
	{
		GameEngineColor ResultColor;
		Ptr += ((_Y * GetScale().iX()) + _X) * 4; // 4����Ʈ �����̶� *4
		ResultColor.R = Ptr[0];
		ResultColor.G = Ptr[1];
		ResultColor.B = Ptr[2];
		ResultColor.A = Ptr[3];
		return ResultColor;
	}
	default:
		MsgBoxAssert("������ ó���ϴ� �Լ��� ������ ���� �����Դϴ�");
		break;
	}

	return _DefaultColor;
}