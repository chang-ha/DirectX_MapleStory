#pragma once
#include "GameEngineDebug.h"
#include <Windows.h>

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

// ���� :
class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;

	static const float D2R;
	static const float R2D;

	// 3.14 => 180��
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
	static const float4 FORWARD;
	static const float4 BACKWARD;

	union 
	{
		float Arr1D[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

		struct 
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		float Arr2D[1][4];
	};

	float4(float _X = 0.0f, float _Y = 0.0f, float _Z = 0.0f, float _W = 1.0f)
		: X(_X), Y(_Y), Z(_Z), W(_W)
	{

	}

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

	float4 operator/(const float4& _Other) const
	{
		float4 ReturnValue;

		ReturnValue.X = X / _Other.X;
		ReturnValue.Y = Y / _Other.Y;
		ReturnValue.Z = Z / _Other.Z;

		return ReturnValue;
	}


	float4 operator/(const float _Value) const
	{
		float4 ReturnValue;

		ReturnValue.X = X / _Value;
		ReturnValue.Y = Y / _Value;
		ReturnValue.Z = Z / _Value;

		return ReturnValue;
	}

	float4& operator/=(const float4 _Value)
	{
		X /= _Value.X;
		Y /= _Value.Y;
		Z /= _Value.Z;

		return *this;
	}


	float4& operator/=(const float _Value)
	{
		X /= _Value;
		Y /= _Value;
		Z /= _Value;

		return *this;
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
		// ���̸� 1�� ����� �Լ��Դϴ�.
		float Len = Size();

		if (0.0f == Len)
		{
			// MsgBoxAssert("0���� �������� �߽��ϴ�.");
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
		float Value = X * X + Y * Y; // == ���� * ����

		// �������̴�.
		// ������ Ǯ� �������̶�� �մϴ�.
		Value; // ���� * ���� => ����

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

		// ���� ������ ������ �ȴ�. = acosf(AngleVector.X);

		float Angle = acosf(AngleVector.X);

		if (0 >= AngleVector.Y)
		{
			Angle = GameEngineMath::PI + GameEngineMath::PI - Angle;
		}

		return Angle;
	}


	float4 VectorRotationToDegXReturn(const float _Deg)
	{
		return VectorRotationToDegX(*this, _Deg);
	}

	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		float Result = (_Left.X * _Right.X) + (_Left.Y * _Right.Y) + (_Left.Z * _Right.Z);
		return Result;
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

	static float4 VectorRotationToRadX(const float4& _Value, const float _Rad);

	float4 VectorRotationToDegYReturn(const float _Deg)
	{
		return VectorRotationToDegY(*this, _Deg);
	}


	static float4 VectorRotationToDegY(const float4& _Value, const float _Deg)
	{
		return VectorRotationToRadY(_Value, _Deg * GameEngineMath::D2R);
	}

	static float4 VectorRotationToRadY(const float4& _Value, const float _Rad);

	float4 VectorRotationToDegZReturn(const float _Deg)
	{
		return VectorRotationToDegZ(*this, _Deg);
	}

	static float4 VectorRotationToDegZ(const float4& _Value, const float _Deg)
	{
		return VectorRotationToRadZ(_Value, _Deg * GameEngineMath::D2R);
	}

	static float4 VectorRotationToRadZ(const float4& _Value, const float _Rad);

	void VectorRotationToDegX(const float _Rad)
	{
		*this = VectorRotationToDegX(*this, _Rad);
	}
	void VectorRotationToDegY(const float _Rad)
	{
		*this = VectorRotationToDegY(*this, _Rad);
	}
	void VectorRotationToDegZ(const float _Rad)
	{
		*this = VectorRotationToDegZ(*this, _Rad);
	}

	//                                       90.0f
	static float4 GetUnitVectorFromRad(const float _Rad)
	{
		// cosf(_Rad)�������� ���� 1�϶��� cosf���� �������ϴ�.
		// sinf(_Rad)�������� ���� 1�϶��� sinf���� �������ϴ�.
		// => ������ ���̰� 1�϶��� ����� ���´�.

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

	float4 operator*(const class float4x4& _Other) const;
	float4& operator*=(const class float4x4& _Other);
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
	static const int MatrixYCount = 4;
	static const int MatrixXCount = 4;

	union
	{
		float Arr2D[MatrixYCount][MatrixXCount] =
		{
			// 00   01   02    03
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};

		float4 ArrVector[4];

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

		float Arr1D[MatrixYCount * MatrixXCount];

	};

	float4x4() 
	{
		Identity();
	}

	void Identity() 
	{
		memset(Arr1D, 0, sizeof(Arr1D));

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

		//float4 Rot * ���;
		
		//Rot.X = _Value.X * cosf(_Rad) - _Value.Y * sinf(_Rad);
		//Rot.Y = _Value.X * sinf(_Rad) + _Value.Y * cosf(_Rad);
		//Rot.Z = _Value.Z;


		// ȸ���� ��ų�� �ִ� ����� �Ǿ�� �Ұź��.

	}

	void Pos(const float4& _Value)
	{
		Identity();

		Arr2D[3][0] = _Value.X;
		Arr2D[3][1] = _Value.Y;
		Arr2D[3][2] = _Value.Z;
	}

	void TransPose()
	{
		// [][][][]
		// [][][][]
		// [][][][]
		// [][][][]

		float4x4 This = *this;
		Identity();
		for (size_t y = 0; y < MatrixYCount; ++y)
		{
			for (size_t x = 0; x < MatrixXCount; ++x)
			{
				Arr2D[x][y] = This.Arr2D[y][x];
			}
		}
	}

	void LookAtLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		Identity();

		float4 EyePos = _EyePos;
		float4 EyeForward = _EyeDir;
		float4 EyeUp = _EyeUp;

		// ī�޶��� Z��
		EyeForward.Normalize();
		// ī������ Y�� 
		EyeUp.Normalize();
		// ī������ X�� 
		float4 EyeRight = float4::Cross3D(EyeUp, EyeForward);

		// ȸ������� ���͸����� ����� ���.
		// float4x4 RotMat;
		ArrVector[0] = EyeRight;
		ArrVector[1] = EyeUp;
		ArrVector[2] = EyeForward;

		// 45�� ���ư� ī�޶��� 
		// �ٸ� ��� ��ü�� -45�� ���ƾ� �Ѵ�.
		TransPose();

		// XYZ���Ƽ� � ��ü�� �ٶ󺸰� �ִ� ī�޶�
		// ȸ������� ������ ������ �Ѵ�.
		// -X-Y-Z���Ƽ� � ��ü�� �������� ������ ������ �ϴµ�.
		// ��ġ��� Transpose�� ������ �Ѵ�..

		float4 NegEyePos = -EyePos;

		// ��� ��ü�� �̵��ؾ��� ������ ���ϰ� �ִ�.
		float XValue = float4::DotProduct3D(EyeRight, NegEyePos);
		float YValue = float4::DotProduct3D(EyeUp, NegEyePos);
		float ZValue = float4::DotProduct3D(EyeForward, NegEyePos);

		// ��ġ
		ArrVector[3] = { XValue, YValue, ZValue };
	}

	//               ���� ����� ũ�⸦ �־��ִµ�
	//               �׳� ������� �ʺ�� ������ ��ġ�� �־��ָ� �˴ϴ�.
	//                      1280                 720           5000
	void OrthographicLH(float _Width, float _Height, float _Far, float _Near)
	{
		// DirectX::XMMatrixOrthographicLH
		Identity();
		//                     5000 - 0.1
		float fRange = 1.0f / (_Far - _Near);
		Arr2D[0][0] = 2.0f / _Width;
		Arr2D[1][1] = 2.0f / _Height;
		Arr2D[2][2] = fRange;
		Arr2D[3][2] = -fRange * _Near;
	}

	//      60���� ����.                    200              100
	// ����
	void PerspectiveFovLH(float _FovAngle, float _Width, float _Height, float _Far, float _Near)
	{
		PerspectiveFovLH(_FovAngle, _Width / _Height, _Far, _Near);
	}

	// ���� �þ߰� 
	// 1000.0f 0.1f
	void PerspectiveFovLH(float _FovAngle, float _AspectRatio, float _Far, float _Near)
	{
		Identity();

		// DirectX::XMMatrixPerspectiveFovLH()

		float YFOV = _FovAngle * GameEngineMath::D2R;

		// ���� ������Ŀ��� Ư¡���� �κ�.
		Arr2D[2][3] = 1.0f;
		Arr2D[3][3] = 0.0f;

		// ��������� ��Ģ��
		// ��� ������Ʈ�� ��� ���� -1 ������ ������ �ִ°��̴�.

		// �� 2���� ����ε� 
		
		// x�� ������ ����
		Arr2D[0][0] = 1.0f / (tanf(YFOV / 2.0f) * _AspectRatio); // / 600


		// y�� ������ ����
		// 1�����⸦ �ϴ� ������?
		// -1 1������ ������ �������.
		
		// �ٺ����� ���������� ������
		// z���� Ŭ���� y���� �پ���.
		// �� y * 
		Arr2D[1][1] = 1.0f / tanf(YFOV / 2.0f);  // / 600

		// 1000 

		//     100    100   100 * ����
		//  * 0.5f          *0.5f
		//                  50.0f

		// �����ȿ� �ִ� �༮�� �� 0~1������ ������ �ٲߴϴ�.
		// 1000 * 0.9784123f
		//           1000  / (1000 - 0.1f);
		Arr2D[2][2] = _Far / (_Far - _Near);

		// �̵��� �� �� ����� �ߴµ�
		Arr2D[3][2] = -(_Near * _Far) / (_Far - _Near);
	}


	void ViewPort(float _Width, float _Height, float _Left, float _Right, float _ZMin = 0.0f, float _ZMax = 1.0f)
	{
		Identity();

		Arr2D[0][0] = _Width * 0.5f;
		Arr2D[1][1] = -_Height * 0.5f; // ���⼭ y�� ������ ��Ų��.
		Arr2D[2][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;

		Arr2D[3][0] = Arr2D[0][0] + _Left;
		Arr2D[3][1] = -Arr2D[1][1] + _Right;
		Arr2D[3][2] = _ZMax != 0.0f ? 0.0f : _ZMin / _ZMax;
		Arr2D[3][3] = 1.0f;
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