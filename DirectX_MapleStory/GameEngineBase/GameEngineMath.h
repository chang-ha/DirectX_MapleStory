#pragma once
#include "GameEngineDebug.h"
#include <Windows.h>

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

// 설명 :
class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;

	static const float D2R;
	static const float R2D;

	// 3.14 => 180도
	// float R = 3.14;
	// float Result = R * (180.0f / 3.14);

};

class float4
{
public:
	static const float4 ZERO;
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;

	union 
	{
		struct 
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		float Arr1D[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float Arr2D[1][4];
	};

	inline int iX() const
	{
		return static_cast<int>(X);
	}

	inline int iY() const
	{
		return static_cast<int>(Y);
	}

	inline float hX() const
	{
		return X * 0.5f;
	}

	inline float hY() const
	{
		return Y * 0.5f;
	}


	inline int ihX() const
	{
		return static_cast<int>(hX());
	}

	inline int ihY() const
	{
		return static_cast<int>(hY());
	}

	inline float4 Half() const
	{
		return { hX(), hY(), Z, W };
	}

	float4 operator-() const
	{
		float4 ReturnValue = *this;

		ReturnValue.X = -ReturnValue.X;
		ReturnValue.Y = -ReturnValue.Y;
		ReturnValue.Z = -ReturnValue.Z;
		return ReturnValue;
	}

	float4 operator-(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X - _Other.X;
		ReturnValue.Y = Y - _Other.Y;
		ReturnValue.Z = Z - _Other.Z;

		return ReturnValue;
	}



	float4 operator+(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X + _Other.X;
		ReturnValue.Y = Y + _Other.Y;
		ReturnValue.Z = Z + _Other.Z;

		return ReturnValue;
	}

	float4 operator*(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X * _Other.X;
		ReturnValue.Y = Y * _Other.Y;
		ReturnValue.Z = Z * _Other.Z;

		return ReturnValue;
	}


	float4 operator*(const float _Value) const
	{
		float4 ReturnValue;

		ReturnValue.X = X * _Value;
		ReturnValue.Y = Y * _Value;
		ReturnValue.Z = Z * _Value;

		return ReturnValue;
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}


	float4& operator-=(const float4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		Z -= _Other.Z;

		return *this;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4& operator*=(const float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	bool operator==(const float4 _Value) const
	{
		return X == _Value.X &&
			Y == _Value.Y &&
			Z == _Value.Z;
	}

	inline void Normalize()
	{
		// 길이를 1로 만드는 함수입니다.
		float Len = Size();

		if (0.0f == Len)
		{
			// MsgBoxAssert("0으로 나누려고 했습니다.");
			return;
		}

		X /= Len;
		Y /= Len;
		Z /= Len;
	}

	inline float4 NormalizeReturn()
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	inline float Size()
	{
		float Value = X * X + Y * Y; // == 빗변 * 빗변

		// 제곱수이다.
		// 제곱을 풀어서 제곱근이라고 합니다.
		Value; // 빗변 * 빗변 => 빗변

		return sqrtf(Value);
	}

	float Max2D() const
	{
		return X > Y ? X : Y;
	}

	POINT WindowPOINT()
	{
		return POINT{ iX(), iY() };
	}



public:
	inline float AngleDeg()
	{
		return AngleRad() * GameEngineMath::R2D;
	}

	inline float AngleRad()
	{
		float4 AngleVector = NormalizeReturn();

		// 라디안 각도만 나오게 된다. = acosf(AngleVector.X);

		float Angle = acosf(AngleVector.X);

		if (0 >= AngleVector.Y)
		{
			Angle = GameEngineMath::PI + GameEngineMath::PI - Angle;
		}

		return Angle;
	}


	float4 VectorRotationToDegX(const float _Deg)
	{
		return VectorRotationToDegX(*this, _Deg);
	}

	static float4 Cross3D(const float4& _Left, const float4& _Right)
	{
		float4 Result;
		Result.X = (_Left.Y * _Right.Z) - (_Left.Z * _Right.Y);
		Result.Y = (_Left.Z * _Right.X) - (_Left.X * _Right.Z);
		Result.Z = (_Left.X * _Right.Y) - (_Left.Y * _Right.X);
		return Result;
	}

	static float4 VectorRotationToDegX(const float4& _Value, const float _Deg)
	{
		return VectorRotationToRadX(_Value, _Deg * GameEngineMath::D2R);
	}

	static float4 VectorRotationToRadX(const float4& _Value, const float _Rad)
	{
		//Rot.X = _Value.X * cosf(_Rad) - _Value.Y * sinf(_Rad);
		//Rot.Y = _Value.X * sinf(_Rad) + _Value.Y * cosf(_Rad);


		// 왜 이 공식인지를 이해해야 합니다.
		float4 Rot;
		Rot.X = _Value.X;
		Rot.Y = _Value.Z * sinf(_Rad) + _Value.Y * cosf(_Rad);
		Rot.Z = _Value.Z * cosf(_Rad) - _Value.Y * sinf(_Rad);
		return Rot;
	}

	float4 VectorRotationToDegY(const float _Deg)
	{
		return VectorRotationToDegY(*this, _Deg);
	}


	static float4 VectorRotationToDegY(const float4& _Value, const float _Deg)
	{
		return VectorRotationToRadY(_Value, _Deg * GameEngineMath::D2R);
	}

	static float4 VectorRotationToRadY(const float4& _Value, const float _Rad)
	{
		// 왜 이 공식인지를 이해해야 합니다.
		float4 Rot;
		Rot.X = _Value.X * cosf(_Rad) - _Value.Z * sinf(_Rad);
		Rot.Y = _Value.Y;
		Rot.Z = _Value.X * sinf(_Rad) + _Value.Z * cosf(_Rad);
		return Rot;
	}

	float4 VectorRotationToDegZ(const float _Deg)
	{
		return VectorRotationToDegZ(*this, _Deg);
	}

	static float4 VectorRotationToDegZ(const float4& _Value, const float _Deg)
	{
		return VectorRotationToRadZ(_Value, _Deg * GameEngineMath::D2R);
	}

	static float4 VectorRotationToRadZ(const float4& _Value, const float _Rad)
	{
		// 왜 이 공식인지를 이해해야 합니다.
		float4 Rot;
		Rot.X = _Value.X * cosf(_Rad) - _Value.Y * sinf(_Rad);
		Rot.Y = _Value.X * sinf(_Rad) + _Value.Y * cosf(_Rad);
		Rot.Z = _Value.Z;
		return Rot;
	}


	//                                       90.0f
	static float4 GetUnitVectorFromRad(const float _Rad)
	{
		// cosf(_Rad)반지름의 길이 1일때의 cosf값이 구해집니다.
		// sinf(_Rad)반지름의 길이 1일때의 sinf값이 구해집니다.
		// => 빗변의 길이가 1일때의 결과가 나온다.

		// 
		// 1.57
		return { cosf(_Rad) , sinf(_Rad) };
	}

	// GetUnitVectorFromDeg(45)

	static float4 LerpClimp(const float4& Start, const float4& _End, float _Ratio)
	{

		if (1.0f <= _Ratio)
		{
			_Ratio = 1.0f;
		}

		return (Start * (1.0f - _Ratio)) + (_End * _Ratio);
	}


	static float4 GetUnitVectorFromDeg(const float _Degree)
	{
		// 90 => 1.57
		return GetUnitVectorFromRad(_Degree * GameEngineMath::D2R);
	}

	float4 operator*(const class float4x4& _Other);
};

class GameEngineRect
{
public:
	float4 Pos;
	float4 Scale;

public:
	float4 CenterLeftTop()
	{
		return { CenterLeft(), CenterTop() };
	}

	float4 CenterRightTop()
	{
		return{ CenterRight(), CenterTop() };
	}

	float4 CenterLeftBot()
	{
		return{ CenterLeft(), CenterBot() };
	}

	float4 CenterRightBot()
	{
		return{ CenterRight(), CenterBot() };
	}

	float CenterLeft()
	{
		return Pos.X - Scale.hX();
	}

	float CenterRight()
	{
		return Pos.X + Scale.hX();
	}

	float CenterTop()
	{
		return Pos.Y - Scale.hY();
	}

	float CenterBot()
	{
		return Pos.Y + Scale.hY();
	}

	int iCenterLeft()
	{
		return Pos.iX() - Scale.ihX();
	}

	int iCenterRight()
	{
		return Pos.iX() + Scale.ihX();
	}

	int iCenterTop()
	{
		return Pos.iY() - Scale.ihY();
	}

	int iCenterBot()
	{
		return Pos.iY() + Scale.ihY();
	}
};

class float4x4
{
public:
	union
	{
		float Arr2D[4][4] =
		{
			// 00   01   02    03
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};

		struct
		{
			float _00;
			float _01;
			float _02;
			float _03;

			float _10;
			float _11;
			float _12;
			float _13;

			float _20;
			float _21;
			float _22;
			float _23;

			float _30;
			float _31;
			float _32;
			float _33;
		};

		float Arr1D[16];

	};

	float4x4() 
	{
		Identity();
	}

	void Identity() 
	{
		memset(&Arr1D, 0, sizeof(Arr1D));

		Arr2D[0][0] = 1.0f;
		Arr2D[1][1] = 1.0f;
		Arr2D[2][2] = 1.0f;
		Arr2D[3][3] = 1.0f;

		return;
	}

	void Scale(const float4& _Value)
	{
		Identity();

		Arr2D[0][0] = _Value.X;
		Arr2D[1][1] = _Value.Y;
		Arr2D[2][2] = _Value.Z;
	}

	void Pos(const float4& _Value)
	{
		Identity();

		Arr2D[3][0] = _Value.X;
		Arr2D[3][1] = _Value.Y;
		Arr2D[3][2] = _Value.Z;
	}


	void RotationXDegs(const float _Value)
	{
		RotationXRad(_Value * GameEngineMath::D2R);
	}

	void RotationXRad(const float _Value)
	{
		Identity();
		// DirectX::XMMatrixRotationX
		float CosValue = cosf(_Value);
		float SinValue = sinf(_Value);
		Arr2D[1][1] = CosValue;
		Arr2D[1][2] = SinValue;
		Arr2D[2][1] = -SinValue;
		Arr2D[2][2] = CosValue;
	}

	void RotationYDegs(const float _Value)
	{
		RotationYRad(_Value * GameEngineMath::D2R);
	}

	void RotationYRad(const float _Value)
	{
		Identity();


		// DirectX::XMMatrixRotationY
		float CosValue = cosf(_Value);
		float SinValue = sinf(_Value);
		Arr2D[0][0] = CosValue;
		Arr2D[0][2] = -SinValue;
		Arr2D[2][0] = SinValue;
		Arr2D[2][2] = CosValue;
	}

	void RotationZDegs(const float _Value)
	{
		RotationZRad(_Value * GameEngineMath::D2R);
	}

	void RotationZRad(const float _Value)
	{
		Identity();


		// DirectX::XMMatrixRotationZ
		float CosValue = cosf(_Value);
		float SinValue = sinf(_Value);
		Arr2D[0][0] = CosValue;
		Arr2D[0][1] = SinValue;
		Arr2D[1][0] = -SinValue;
		Arr2D[1][1] = CosValue;


		//					    [cosf(_Rad)][sinf(_Rad)][02][03]
		//					    [-sinf(_Rad)][cosf(_Rad)][12][13]
		//					    [20][21][22][23]
		//					    [30][31][32][33]
		// [x][y][z][w]        = rx  ry  rz  rw
		
		// [x]*[00] + [y] *[10] + [z] * [20] + [w] * [30]

		//float4 Rot * 행렬;
		
		//Rot.X = _Value.X * cosf(_Rad) - _Value.Y * sinf(_Rad);
		//Rot.Y = _Value.X * sinf(_Rad) + _Value.Y * cosf(_Rad);
		//Rot.Z = _Value.Z;


		// 회전을 시킬수 있는 행렬이 되어야 할거빈다.

	}

	float4x4 operator*(const float4x4& _Other)
	{
		float4x4 Result;
		const float4x4& A = *this;
		const float4x4& B = _Other;

		Result.Arr2D[0][0] = (A.Arr2D[0][0] * B.Arr2D[0][0]) + (A.Arr2D[0][1] * B.Arr2D[1][0]) + (A.Arr2D[0][2] * B.Arr2D[2][0]) + (A.Arr2D[0][3] * B.Arr2D[3][0]);
		Result.Arr2D[0][1] = (A.Arr2D[0][0] * B.Arr2D[0][1]) + (A.Arr2D[0][1] * B.Arr2D[1][1]) + (A.Arr2D[0][2] * B.Arr2D[2][1]) + (A.Arr2D[0][3] * B.Arr2D[3][1]);
		Result.Arr2D[0][2] = (A.Arr2D[0][0] * B.Arr2D[0][2]) + (A.Arr2D[0][1] * B.Arr2D[1][2]) + (A.Arr2D[0][2] * B.Arr2D[2][2]) + (A.Arr2D[0][3] * B.Arr2D[3][2]);
		Result.Arr2D[0][3] = (A.Arr2D[0][0] * B.Arr2D[0][3]) + (A.Arr2D[0][1] * B.Arr2D[1][3]) + (A.Arr2D[0][2] * B.Arr2D[2][3]) + (A.Arr2D[0][3] * B.Arr2D[3][3]);

		Result.Arr2D[1][0] = (A.Arr2D[1][0] * B.Arr2D[0][0]) + (A.Arr2D[1][1] * B.Arr2D[1][0]) + (A.Arr2D[1][2] * B.Arr2D[2][0]) + (A.Arr2D[1][3] * B.Arr2D[3][0]);
		Result.Arr2D[1][1] = (A.Arr2D[1][0] * B.Arr2D[0][1]) + (A.Arr2D[1][1] * B.Arr2D[1][1]) + (A.Arr2D[1][2] * B.Arr2D[2][1]) + (A.Arr2D[1][3] * B.Arr2D[3][1]);
		Result.Arr2D[1][2] = (A.Arr2D[1][0] * B.Arr2D[0][2]) + (A.Arr2D[1][1] * B.Arr2D[1][2]) + (A.Arr2D[1][2] * B.Arr2D[2][2]) + (A.Arr2D[1][3] * B.Arr2D[3][2]);
		Result.Arr2D[1][3] = (A.Arr2D[1][0] * B.Arr2D[0][3]) + (A.Arr2D[1][1] * B.Arr2D[1][3]) + (A.Arr2D[1][2] * B.Arr2D[2][3]) + (A.Arr2D[1][3] * B.Arr2D[3][3]);

		Result.Arr2D[2][0] = (A.Arr2D[2][0] * B.Arr2D[0][0]) + (A.Arr2D[2][1] * B.Arr2D[1][0]) + (A.Arr2D[2][2] * B.Arr2D[2][0]) + (A.Arr2D[2][3] * B.Arr2D[3][0]);
		Result.Arr2D[2][1] = (A.Arr2D[2][0] * B.Arr2D[0][1]) + (A.Arr2D[2][1] * B.Arr2D[1][1]) + (A.Arr2D[2][2] * B.Arr2D[2][1]) + (A.Arr2D[2][3] * B.Arr2D[3][1]);
		Result.Arr2D[2][2] = (A.Arr2D[2][0] * B.Arr2D[0][2]) + (A.Arr2D[2][1] * B.Arr2D[1][2]) + (A.Arr2D[2][2] * B.Arr2D[2][2]) + (A.Arr2D[2][3] * B.Arr2D[3][2]);
		Result.Arr2D[2][3] = (A.Arr2D[2][0] * B.Arr2D[0][3]) + (A.Arr2D[2][1] * B.Arr2D[1][3]) + (A.Arr2D[2][2] * B.Arr2D[2][3]) + (A.Arr2D[2][3] * B.Arr2D[3][3]);

		Result.Arr2D[3][0] = (A.Arr2D[3][0] * B.Arr2D[0][0]) + (A.Arr2D[3][1] * B.Arr2D[1][0]) + (A.Arr2D[3][2] * B.Arr2D[2][0]) + (A.Arr2D[3][3] * B.Arr2D[3][0]);
		Result.Arr2D[3][1] = (A.Arr2D[3][0] * B.Arr2D[0][1]) + (A.Arr2D[3][1] * B.Arr2D[1][1]) + (A.Arr2D[3][2] * B.Arr2D[2][1]) + (A.Arr2D[3][3] * B.Arr2D[3][1]);
		Result.Arr2D[3][2] = (A.Arr2D[3][0] * B.Arr2D[0][2]) + (A.Arr2D[3][1] * B.Arr2D[1][2]) + (A.Arr2D[3][2] * B.Arr2D[2][2]) + (A.Arr2D[3][3] * B.Arr2D[3][2]);
		Result.Arr2D[3][3] = (A.Arr2D[3][0] * B.Arr2D[0][3]) + (A.Arr2D[3][1] * B.Arr2D[1][3]) + (A.Arr2D[3][2] * B.Arr2D[2][3]) + (A.Arr2D[3][3] * B.Arr2D[3][3]);

		return Result;
	}
};