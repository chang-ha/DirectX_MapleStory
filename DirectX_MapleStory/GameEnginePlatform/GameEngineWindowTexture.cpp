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
	// 단순히 비트맵만 로드하는 함수가 아니라서 우리에게 그냥 HANDLE을 준다
	// 선생님 기억으로는 커서 아이콘등도 이녀석으로 로드할수 있었나? 하는데 그래서 

	// LoadBitmapA()

	// LPCSTR == const char*

	HANDLE ImageHandle = LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("이미지 로드에 실패했습니다." + _Path);
		return;
	}

	// 이미지의 핸들일 뿐이고.
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// 없던 권한을 새롭게 만들어야 한다.
	// Window에서 얻어온 DC
	ImageDC = CreateCompatibleDC(nullptr);
	// 이미지의 수정 권한을 만들어 내고

	// ImageDC 권한에
	// BitMap 2차원의 색깔 집합을 연결해라.
	// 사실 이미 만들어지자마자 내부에 1,1 이미지와 연결되어있고
	// 내가 로드한 이미지를 그 1,1짜리를 밀어내고 교체하는 작업을 하는데.
	// 이 함수의 리턴값이 기존에 연결되어있던 애를 리턴해주는것.
	OldBitMap = static_cast<HBITMAP>(SelectObject(ImageDC, BitMap));

	ScaleCheck();
}

void GameEngineWindowTexture::ResCreate(HDC _HDC, const float4& _Scale)
{
	// 그냥 비어있는 흰색 이미지를 하나 만드는 함수인거에요.
	HANDLE ImageHandle = CreateCompatibleBitmap(_HDC, _Scale.iX(), _Scale.iY());

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다.");
		return;
	}

	// 이미지의 핸들일 뿐이고.
	BitMap = static_cast<HBITMAP>(ImageHandle);

	// 없던 권한을 새롭게 만들어야 한다.
	// Window에서 얻어온 DC
	ImageDC = CreateCompatibleDC(nullptr);
	// 이미지의 수정 권한을 만들어 내고

	// ImageDC 권한에
	// BitMap 2차원의 색깔 집합을 연결해라.
	// 사실 이미 만들어지자마자 내부에 1,1 이미지와 연결되어있고
	// 내가 로드한 이미지를 그 1,1짜리를 밀어내고 교체하는 작업을 하는데.
	// 이 함수의 리턴값이 기존에 연결되어있던 애를 리턴해주는것.
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

	//// 특정 DC에 연결된 색상을
	//// 특정 DC에 고속복사하는 함수입니다.
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
		MsgBoxAssert("카피할 텍스처가 세팅되지 않았습니다.");
	}

	HDC CopyImageDC = _CopyTexture->GetImageDC();

	//// 특정 DC에 연결된 색상을
	//// 특정 DC에 고속복사하는 함수입니다.
	TransparentBlt(ImageDC,
		_Pos.iX() - _Scale.ihX(),
		_Pos.iY() - _Scale.ihY(),
		_Scale.iX(), 
		_Scale.iY(), 
		CopyImageDC,
		_OtherPos.iX(), // 카피하려는 이미지의 왼쪽위 x
		_OtherPos.iY(), // 카피하려는 이미지의 왼쪽위 y
		_OtherScale.iX(), // 그부분부터 사이즈  x
		_OtherScale.iY(), // 그부분부터 사이즈  y
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
	// float절대로 오차가 없을수 없다.

	// 아래와 같은 왠만하면 하면 안되요.
	//if (a == 30.0f)
	//if (a == 0.0f) <= 같다를 할거면 요런건 허용된다.
	//{
	//}

	// float ==

	// 점의 회전을 만들어야 한다.

	if (nullptr == _CopyTexture)
	{
		MsgBoxAssert("카피할 텍스처가 세팅되지 않았습니다.");
	}

	if (nullptr == _MaskTexture)
	{
		MsgBoxAssert("마스크 텍스처가 없이 이미지 회전을 시킬수는 없습니다.");
	}

	if (_Angle == 180.0f)
	{
		// 완전히 반전되었을때만 에러가 좀 있어서
		_Angle = 180.000001f;
	}

	POINT ArrPoint[3];

	// _Scale화면에 그리고자 하는 크기
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
		_OtherPos.iX(), // 카피하려는 이미지의 왼쪽위 x
		_OtherPos.iY(), // 카피하려는 이미지의 왼쪽위 y
		_OtherScale.iX(), // 그부분부터 사이즈  x
		_OtherScale.iY(), // 그부분부터 사이즈  y
		_MaskTexture->BitMap,
		_OtherPos.iX(), // 카피하려는 이미지의 왼쪽위 x
		_OtherPos.iY()
	);

}

void GameEngineWindowTexture::AlphaCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, unsigned char _Alpha)
{
	if (nullptr == _CopyTexture)
	{
		MsgBoxAssert("카피할 텍스처가 세팅되지 않았습니다.");
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
		_OtherPos.iX(), // 카피하려는 이미지의 왼쪽위 x
		_OtherPos.iY(), // 카피하려는 이미지의 왼쪽위 y
		_OtherScale.iX(), // 그부분부터 사이즈  x
		_OtherScale.iY(), // 그부분부터 사이즈  y
		Function
	);
}