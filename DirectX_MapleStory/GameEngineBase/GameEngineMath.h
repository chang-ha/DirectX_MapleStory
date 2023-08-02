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
		DirectX::XMVECTOR DirectXVector;
	};

	float4(DirectX::FXMVECTOR& _DirectXVector)
		: DirectXVector(_DirectXVector)
	{

	}

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
		float4 ReturnValue = DirectX::XMVectorSet(-X, -Y, -Z, W);
		return ReturnValue;
	}

	float4 operator-(const float4& _Other) const
	{
		float4 ReturnValue;
		ReturnValue.DirectXVector = DirectX::XMVectorSubtract(DirectXVector, _Other.DirectXVector);
		ReturnValue.W = W;
		return ReturnValue;
	}



	float4 operator+(const float4& _Other) const
	{
		float4 ReturnValue;
		ReturnValue.DirectXVector = DirectX::XMVectorAdd(DirectXVector, _Other.DirectXVector);
		ReturnValue.W = W;
		return ReturnValue;
	}

	float4 operator*(const float4& _Other) const
	{
		float4 ReturnValue;
		ReturnValue = DirectX::XMVectorMultiply(DirectXVector, _Other.DirectXVector);
		ReturnValue.W = W;
		return ReturnValue;
	}


	float4 operator*(const float _Value) const
	{
		float4 OtherVector = { _Value , _Value , _Value , 1.0f };
		float4 ReturnValue;
		ReturnValue = DirectX::XMVectorMultiply(DirectXVector, OtherVector.DirectXVector);
		ReturnValue.W = W;
		return ReturnValue;
	}

	float4 operator/(const float4& _Other) const
	{

		float4 ReturnValue = DirectX::XMVectorDivide(DirectXVector, _Other.DirectXVector);
		ReturnValue.W = W;
		return ReturnValue;
	}


	float4 operator/(const float _Value) const
	{
		float4 OtherVecter = { _Value , _Value , _Value , 1.0f};
		float4 ReturnValue = DirectX::XMVectorDivide(DirectXVector, OtherVecter.DirectXVector);
		ReturnValue.W = W;

		return ReturnValue;
	}

	float4& operator/=(const float4 _Value)
	{
		float PrevW = W;
		DirectXVector = DirectX::XMVectorDivide(DirectXVector, _Value.DirectXVector);
		W = PrevW;
		return *this;
	}


	float4& operator/=(const float _Value)
	{
		float4 OtherVecter = { _Value , _Value , _Value , 1.0f };
		float PrevW = W;
		DirectXVector = DirectX::XMVectorDivide(DirectXVector, OtherVecter.DirectXVector);
		W = PrevW;
		return *this;
	}


	float4& operator+=(const float4& _Other)
	{
		float PrevW = W;
		DirectXVector = DirectX::XMVectorAdd(DirectXVector, _Other.DirectXVector);
		W = PrevW;
		return *this;
	}


	float4& operator-=(const float4& _Other)
	{
		float PrevW = W;
		DirectXVector = DirectX::XMVectorSubtract(DirectXVector, _Other.DirectXVector);
		W = PrevW;
		return *this;
	}

	float4& operator*=(const float4& _Other)
	{
		float PrevW = W;
		DirectXVector = DirectX::XMVectorMultiply(DirectXVector, _Other.DirectXVector);
		W = PrevW;
		return *this;
	}

	float4& operator*=(const float _Value)
	{
		float4 OtherVecter = { _Value , _Value , _Value , 1.0f };
		float PrevW = W;
		DirectXVector = DirectX::XMVectorMultiply(DirectXVector, OtherVecter.DirectXVector);
		W = PrevW;
		return *this;
	}

	bool operator==(const float4 _Value) const
	{
		return DirectX::XMVector3Equal(DirectXVector, _Value.DirectXVector);
	}

	inline void Normalize()
	{
		DirectXVector = DirectX::XMVector3Normalize(DirectXVector);
	}

	inline float4 NormalizeReturn()
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	inline float Size()
	{
		float4 Result = DirectX::XMVector3Length(DirectXVector);
		return Result.X;
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
	inline float Angle2DDeg()
	{
		return Angle2DRad() * GameEngineMath::R2D;
	}

	inline float Angle2DRad()
	{
		float4 Result = DirectX::XMVector2AngleBetweenNormals(DirectXVector, float4::RIGHT.DirectXVector);
		return Result.X;
	}


	float4 VectorRotationToDegXReturn(const float _Deg)
	{
		return VectorRotationToDegX(*this, _Deg);
	}

	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		float4 Result = DirectX::XMVector3Dot(_Left.DirectXVector, _Right.DirectXVector);
		return Result.X;
	}


	static float4 Cross3D(const float4& _Left, const float4& _Right)
	{
		float4 Result = DirectX::XMVector3Cross(_Left.DirectXVector, _Right.DirectXVector);
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

	static float4 GetUnitVectorFromDeg(const float _Degree)
	{
		return GetUnitVectorFromRad(_Degree * GameEngineMath::D2R);
	}

	static float4 GetUnitVectorFromRad(const float _Rad)
	{
		return { cosf(_Rad) , sinf(_Rad) };
	}

	static float4 LerpClimp(const float4& Start, const float4& _End, float _Ratio)
	{
		if (1.0f <= _Ratio)
		{
			_Ratio = 1.0f;
		}

		float4 Result = DirectX::XMVectorLerp(Start.DirectXVector, _End.DirectXVector, _Ratio);
		return Result;
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
		DirectX::XMMATRIX DirectXMatrix;
	};

	float4x4& operator=(DirectX::XMMATRIX _Matrix)
	{
		DirectXMatrix = _Matrix;
		return *this;
	}

	float4x4() 
	{
		Identity();
	}

	float4x4(const DirectX::FXMMATRIX& _Matrix)
		: DirectXMatrix(_Matrix)
	{
	}

	void Identity() 
	{
		DirectXMatrix = DirectX::XMMatrixIdentity();
		return;
	}

	void Scale(const float4& _Value)
	{
		// Identity();
		//Arr2D[0][0] = _Value.X;
		//Arr2D[1][1] = _Value.Y;
		//Arr2D[2][2] = _Value.Z;

		DirectXMatrix = DirectX::XMMatrixScalingFromVector(_Value.DirectXVector);
	}



	void RotationXDegs(const float _Value)
	{
		RotationXRad(_Value * GameEngineMath::D2R);
	}

	void RotationXRad(const float _Value)
	{
		// Identity();

		DirectXMatrix = DirectX::XMMatrixRotationX(_Value);

		//// DirectX::XMMatrixRotationX
		//float CosValue = cosf(_Value);
		//float SinValue = sinf(_Value);
		//Arr2D[1][1] = CosValue;
		//Arr2D[1][2] = SinValue;
		//Arr2D[2][1] = -SinValue;
		//Arr2D[2][2] = CosValue;
	}

	void RotationYDegs(const float _Value)
	{
		RotationYRad(_Value * GameEngineMath::D2R);
	}

	void RotationYRad(const float _Value)
	{
		DirectXMatrix = DirectX::XMMatrixRotationY(_Value);
	}

	void RotationZDegs(const float _Value)
	{
		RotationZRad(_Value * GameEngineMath::D2R);
	}

	void RotationZRad(const float _Value)
	{
		DirectXMatrix = DirectX::XMMatrixRotationZ(_Value);
	}

	void Pos(const float4& _Value)
	{
		DirectXMatrix = DirectX::XMMatrixTranslationFromVector(_Value.DirectXVector);
	}

	void TransPose()
	{
		DirectXMatrix = DirectX::XMMatrixTranspose(DirectXMatrix);
	}

	void LookToLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		DirectXMatrix = DirectX::XMMatrixLookToLH(_EyePos.DirectXVector, _EyeDir.DirectXVector, _EyeUp.DirectXVector);
	}

	void OrthographicLH(float _Width, float _Height, float _Near, float _Far)
	{
		DirectXMatrix = DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);
	}

	void PerspectiveFovLH(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	{
		PerspectiveFovLH(_FovAngle, _Width / _Height, _Near, _Far);
	}

	void PerspectiveFovLH(float _FovAngle, float _AspectRatio, float _Near, float _Far)
	{
		DirectXMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovAngle, _AspectRatio, _Near, _Far);
	}


	void ViewPort(float _Width, float _Height, float _Left, float _Right, float _ZMin = 0.0f, float _ZMax = 1.0f)
	{
		Identity();

		Arr2D[0][0] = _Width * 0.5f;
		Arr2D[1][1] = -_Height * 0.5f; // 여기서 y축 반전을 시킨다.
		Arr2D[2][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;

		Arr2D[3][0] = Arr2D[0][0] + _Left;
		Arr2D[3][1] = -Arr2D[1][1] + _Right;
		Arr2D[3][2] = _ZMax != 0.0f ? 0.0f : _ZMin / _ZMax;
		Arr2D[3][3] = 1.0f;
	}

	float4x4 operator*(const float4x4& _Other)
	{
		const float4x4& A = *this;
		const float4x4& B = _Other;

		return DirectX::XMMatrixMultiply(A.DirectXMatrix, B.DirectXMatrix);
	}
};