#pragma once
#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
class GameEngineWindowTexture
{
	friend class GDIPlusInit;

private:
	static ULONG_PTR Token;
	static Gdiplus::GdiplusStartupInput Input;

public:
	// constrcuter destructer
	GameEngineWindowTexture();
	~GameEngineWindowTexture();

	// delete Function
	GameEngineWindowTexture(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture(GameEngineWindowTexture&& _Other) noexcept = delete;
	GameEngineWindowTexture& operator=(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture& operator=(GameEngineWindowTexture&& _Other) noexcept = delete;

	void ResLoad(const std::string& _Path);
	void ResCreate(HDC  _ImageDC) 
	{
		ImageDC = _ImageDC;
		ScaleCheck();
	}

	void ResCreate(HDC _HDC, const float4& _Scale);


	HDC GetImageDC() 
	{
		return ImageDC;
	}

	float4 GetScale();

	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos);
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale);

	void TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, int _TransColor = RGB(255, 0, 255));

	// 반투명용 카피
	// void AlphaCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale);

	// 회전용 카피
	void PlgCopy(GameEngineWindowTexture* _CopyTexture, GameEngineWindowTexture* _MaskTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, float _Angle);

	void AlphaCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, const float4& _OtherPos, const float4& _OtherScale, unsigned char _Alpha);

	unsigned int GetColor(unsigned int _DefaultColor, float4 _Pos);

	void FillTexture(unsigned int _Color);

protected:

private:
	HBITMAP BitMap;
	HBITMAP OldBitMap;
	HDC ImageDC;

	BITMAP Info;

	void ScaleCheck();
};

