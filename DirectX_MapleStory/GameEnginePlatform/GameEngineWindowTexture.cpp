#include "PreCompile.h"
#include "GameEngineWindowTexture.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineWindow.h"

#pragma comment(lib, "gdiplus")
#pragma comment(lib, "msimg32.lib")

ULONG_PTR GameEngineWindowTexture::Token;
Gdiplus::GdiplusStartupInput GameEngineWindowTexture::Input;

class GDIPlusInit 
{
public:
	GDIPlusInit() 
	{
		Gdiplus::Status Result = Gdiplus::GdiplusStartup(&GameEngineWindowTexture::Token, &GameEngineWindowTexture::Input, nullptr);

		if (Result != Gdiplus::Status::Ok)
		{
			int a = 0;
		}
	}
	~GDIPlusInit() 
	{
		Gdiplus::GdiplusShutdown(GameEngineWindowTexture::Token);
	}
};

GDIPlusInit InitInstance;

/////////////////////// GIDPLUSInit


GameEngineWindowTexture::GameEngineWindowTexture() 
{
}

GameEngineWindowTexture::~GameEngineWindowTexture() 
{
}

void GameEngineWindowTexture::ResLoad(const std::string& _Path)
{
	// �ܼ��� ��Ʈ�ʸ� �ε��ϴ� �Լ��� �ƴ϶� �츮���� �׳� HANDLE�� �ش�
	// ������ ������δ� Ŀ�� �����ܵ �̳༮���� �ε��Ҽ� �־���? �ϴµ� �׷��� 

	// LoadBitmapA()

	// LPCSTR == const char*

	HANDLE ImageHandle = LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("�̹��� �ε忡 �����߽��ϴ�." + _Path);
		return;
	}

	// �̹����� �ڵ��� ���̰�.
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// ���� ������ ���Ӱ� ������ �Ѵ�.
	// Window���� ���� DC
	ImageDC = CreateCompatibleDC(nullptr);
	// �̹����� ���� ������ ����� ����

	// ImageDC ���ѿ�
	// BitMap 2������ ���� ������ �����ض�.
	// ��� �̹� ��������ڸ��� ���ο� 1,1 �̹����� ����Ǿ��ְ�
	// ���� �ε��� �̹����� �� 1,1¥���� �о�� ��ü�ϴ� �۾��� �ϴµ�.
	// �� �Լ��� ���ϰ��� ������ ����Ǿ��ִ� �ָ� �������ִ°�.
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}

void GameEngineWindowTexture::ResCreate(HDC _HDC, const float4& _Scale)
{
	// �׳� ����ִ� ��� �̹����� �ϳ� ����� �Լ��ΰſ���.
	HANDLE ImageHandle = CreateCompatibleBitmap(_HDC, _Scale.iX(), _Scale.iY());

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("�̹��� ������ �����߽��ϴ�.");
		return;
	}

	// �̹����� �ڵ��� ���̰�.
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// ���� ������ ���Ӱ� ������ �Ѵ�.
	// Window���� ���� DC
	ImageDC = CreateCompatibleDC(nullptr);
	// �̹����� ���� ������ ����� ����

	// ImageDC ���ѿ�
	// BitMap 2������ ���� ������ �����ض�.
	// ��� �̹� ��������ڸ��� ���ο� 1,1 �̹����� ����Ǿ��ְ�
	// ���� �ε��� �̹����� �� 1,1¥���� �о�� ��ü�ϴ� �۾��� �ϴµ�.
	// �� �Լ��� ���ϰ��� ������ ����Ǿ��ִ� �ָ� �������ִ°�.
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}

void GameEngineWindowTexture::ScaleCheck()
{
	GetObject(BitMap, sizeof(BITMAP), &Info);

	BITMAP OldInfo;

	GetObject(OldBitMap, sizeof(BITMAP), &OldInfo);
}

float4 GameEngineWindowTexture::GetScale()
{
	
	return { static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
}



void GameEngineWindowTexture::BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos)
{
	BitCopy(_CopyTexture, _Pos, _CopyTexture->GetScale());
}

void GameEngineWindowTexture::BitCopy(
	GameEngineWindowTexture* _CopyTexture, 
	const float4& _Pos, 
	const float4& _Scale)
{
	HDC CopyImageDC = _CopyTexture->GetImageDC();

	//// Ư�� DC�� ����� ������
	//// Ư�� DC�� ��Ӻ����ϴ� �Լ��Դϴ�.
	BitBlt(ImageDC, 
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		CopyImageDC,
		0, 
		0, 
		SRCCOPY);

}

void GameEngineWindowTexture::TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, int _TransColor/* = RGB(255, 0, 255)*/)
{
	if (nullptr == _CopyTexture)
	{
		MsgBoxAssert("ī���� �ؽ�ó�� ���õ��� �ʾҽ��ϴ�.");
	}

	HDC CopyImageDC = _CopyTexture->GetImageDC();

	//// Ư�� DC�� ����� ������
	//// Ư�� DC�� ��Ӻ����ϴ� �Լ��Դϴ�.
	TransparentBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(), 
		_Scale.iY(), 
		CopyImageDC,
		_OtherPos.iX(), // ī���Ϸ��� �̹����� ������ x
		_OtherPos.iY(), // ī���Ϸ��� �̹����� ������ y
		_OtherScale.iX(), // �׺κк��� ������  x
		_OtherScale.iY(), // �׺κк��� ������  y
		_TransColor
	);

}

unsigned int GameEngineWindowTexture::GetColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (0 > _Pos.iX() )
	{
		return _DefaultColor;
	}

	if (0 > _Pos.iY())
	{
		return _DefaultColor;
	}

	if (GetScale().iX() <= _Pos.iX())
	{
		return _DefaultColor;
	}

	if (GetScale().iX() <= _Pos.iY())
	{
		return _DefaultColor;
	}

	return GetPixel(ImageDC, _Pos.iX(), _Pos.iY());
}

void GameEngineWindowTexture::FillTexture(unsigned int _Color)
{
	RECT Rc; 
	Rc.left = 0;
	Rc.top = 0;
	Rc.right = GetScale().iX();
	Rc.bottom = GetScale().iY();

	HBRUSH brh = CreateSolidBrush(_Color);

	FillRect(ImageDC, &Rc, brh);

	DeleteObject(brh);
}

void GameEngineWindowTexture::PlgCopy(GameEngineWindowTexture* _CopyTexture
	, GameEngineWindowTexture* _MaskTexture
	, const float4& _Pos
	, const float4& _Scale
	, const float4& _OtherPos
	, const float4& _OtherScale
	, float _Angle
)
{
	// float����� ������ ������ ����.

	// �Ʒ��� ���� �ظ��ϸ� �ϸ� �ȵǿ�.
	//if (a == 30.0f)
	//if (a == 0.0f) <= ���ٸ� �ҰŸ� �䷱�� ���ȴ�.
	//{
	//}

	// float ==

	// ���� ȸ���� ������ �Ѵ�.

	if (nullptr == _CopyTexture)
	{
		MsgBoxAssert("ī���� �ؽ�ó�� ���õ��� �ʾҽ��ϴ�.");
	}

	if (nullptr == _MaskTexture)
	{
		MsgBoxAssert("����ũ �ؽ�ó�� ���� �̹��� ȸ���� ��ų���� �����ϴ�.");
	}

	if (_Angle == 180.0f)
	{
		// ������ �����Ǿ������� ������ �� �־
		_Angle = 180.000001f;
	}

	POINT ArrPoint[3];

	// _Scaleȭ�鿡 �׸����� �ϴ� ũ��
	GameEngineRect Rect = GameEngineRect(float4::ZERO, _Scale);

	float4 LeftTop = Rect.CenterLeftTop();
	float4 RightTop = Rect.CenterRightTop();
	float4 LeftBot = Rect.CenterLeftBot();
	// float4 RightBot = Rect.CenterRightBot();

	ArrPoint[0] = (LeftTop.VectorRotationToDegZReturn(_Angle) + _Pos).WindowPOINT();
	ArrPoint[1] = (RightTop.VectorRotationToDegZReturn(_Angle) + _Pos).WindowPOINT();
	ArrPoint[2] = (LeftBot.VectorRotationToDegZReturn(_Angle) + _Pos).WindowPOINT();

	HDC CopyImageDC = _CopyTexture->GetImageDC();

	PlgBlt(ImageDC,
		ArrPoint,
		CopyImageDC,
		_OtherPos.iX(), // ī���Ϸ��� �̹����� ������ x
		_OtherPos.iY(), // ī���Ϸ��� �̹����� ������ y
		_OtherScale.iX(), // �׺κк��� ������  x
		_OtherScale.iY(), // �׺κк��� ������  y
		_MaskTexture->BitMap,
		_OtherPos.iX(), // ī���Ϸ��� �̹����� ������ x
		_OtherPos.iY()
	);

}

void GameEngineWindowTexture::AlphaCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, unsigned char _Alpha)
{
	if (nullptr == _CopyTexture)
	{
		MsgBoxAssert("ī���� �ؽ�ó�� ���õ��� �ʾҽ��ϴ�.");
	}

	HDC CopyImageDC = _CopyTexture->GetImageDC();

	BLENDFUNCTION Function;

	Function.BlendOp = AC_SRC_OVER;
	Function.BlendFlags = 0;
	Function.SourceConstantAlpha = _Alpha;
	Function.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(
		ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(),
		_Scale.iY(),
		CopyImageDC,
		_OtherPos.iX(), // ī���Ϸ��� �̹����� ������ x
		_OtherPos.iY(), // ī���Ϸ��� �̹����� ������ y
		_OtherScale.iX(), // �׺κк��� ������  x
		_OtherScale.iY(), // �׺κк��� ������  y
		Function
	);
}