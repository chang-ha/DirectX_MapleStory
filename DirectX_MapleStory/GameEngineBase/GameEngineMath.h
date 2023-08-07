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
		//return X == _Value.X &&
		//	Y == _Value.Y &&
		//	Z == _Value.Z;
	}

	inline void Normalize()
	{
		// 길이를 1로 만드는 함수입니다.
		//float Len = Size();

		//if (0.0f == Len)
		//{
		//	// MsgBoxAssert("0으로 나누려고 했습니다.");
		//	return;
		//}

		//X /= Len;
		//Y /= Len;
		//Z /= Len;

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
		//float Value = X * X + Y * Y + Z * Z; // == 빗변 * 빗변
		//return sqrtf(Value);

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
		// 2개의 벡터의 각도 구해주는 함수
		float4 Result = DirectX::XMVector2AngleBetweenNormals(DirectXVector, float4::RIGHT.DirectXVector);

		//float4 AngleVector = NormalizeReturn();

		//// 라디안 각도만 나오게 된다. = acosf(AngleVector.X);

		//float Angle = acosf(AngleVector.X);

		//if (0 >= AngleVector.Y)
		//{
		//	Angle = GameEngineMath::PI + GameEngineMath::PI - Angle;
		//}

		return Result.X;
	}


	float4 VectorRotationToDegXReturn(const float _Deg)
	{
		return VectorRotationToDegX(*this, _Deg);
	}

	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		// float Result = (_Left.X * _Right.X) + (_Left.Y * _Right.Y) + (_Left.Z * _Right.Z);
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
		// 90 => 1.57
		return GetUnitVectorFromRad(_Degree * GameEngineMath::D2R);
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

	float4x4(const float4x4& _Matrix)
		: DirectXMatrix(_Matrix.DirectXMatrix)
	{
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

	void RotationDeg(const float4& _Value)
	{
		RotationRad(_Value * GameEngineMath::D2R);
	}
	
	void RotationRad(const float4& _Value)
	{
		float4x4 X;
		float4x4 Y;
		float4x4 Z;

		X.RotationXRad(_Value.X);
		Y.RotationYRad(_Value.Y);
		Z.RotationZRad(_Value.Z);

		DirectXMatrix = (X * Y * Z).DirectXMatrix;
	}


	void RotationXDeg(const float _Value)
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

	void RotationYDeg(const float _Value)
	{
		RotationYRad(_Value * GameEngineMath::D2R);
	}

	void RotationYRad(const float _Value)
	{
		// Identity();

		DirectXMatrix = DirectX::XMMatrixRotationY(_Value);

		// DirectX::XMMatrixRotationY
		//float CosValue = cosf(_Value);
		//float SinValue = sinf(_Value);
		//Arr2D[0][0] = CosValue;
		//Arr2D[0][2] = -SinValue;
		//Arr2D[2][0] = SinValue;
		//Arr2D[2][2] = CosValue;
	}

	void RotationZDeg(const float _Value)
	{
		RotationZRad(_Value * GameEngineMath::D2R);
	}

	void RotationZRad(const float _Value)
	{
		DirectXMatrix = DirectX::XMMatrixRotationZ(_Value);
		//Identity();

		//// DirectX::XMMatrixRotationZ
		//float CosValue = cosf(_Value);
		//float SinValue = sinf(_Value);
		//Arr2D[0][0] = CosValue;
		//Arr2D[0][1] = SinValue;
		//Arr2D[1][0] = -SinValue;
		//Arr2D[1][1] = CosValue;


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

	void Position(const float4& _Value)
	{

		DirectXMatrix = DirectX::XMMatrixTranslationFromVector(_Value.DirectXVector);

		//Identity();
		//Arr2D[3][0] = _Value.X;
		//Arr2D[3][1] = _Value.Y;
		//Arr2D[3][2] = _Value.Z;
	}

	void TransPose()
	{
		// [][][][]
		// [][][][]
		// [][][][]
		// [][][][]

		DirectXMatrix = DirectX::XMMatrixTranspose(DirectXMatrix);


		//float4x4 This = *this;
		//Identity();
		//for (size_t y = 0; y < MatrixYCount; ++y)
		//{
		//	for (size_t x = 0; x < MatrixXCount; ++x)
		//	{
		//		Arr2D[x][y] = This.Arr2D[y][x];
		//	}
		//}
	}

	void LookToLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		DirectXMatrix = DirectX::XMMatrixLookToLH(_EyePos.DirectXVector, _EyeDir.DirectXVector, _EyeUp.DirectXVector);

		//Identity();

		//float4 EyePos = _EyePos;
		//float4 EyeForward = _EyeDir;
		//float4 EyeUp = _EyeUp;

		//// 카메라의 Z앞
		//EyeForward.Normalize();
		//// 카마라의 Y위 
		//EyeUp.Normalize();
		//// 카마라의 X위 
		//float4 EyeRight = float4::Cross3D(EyeUp, EyeForward);

		//// 회전행렬을 벡터만으로 만드는 방법.
		//// float4x4 RotMat;
		//ArrVector[0] = EyeRight;
		//ArrVector[1] = EyeUp;
		//ArrVector[2] = EyeForward;

		//// 45도 돌아간 카메라라면 
		//// 다른 모든 물체는 -45도 돌아야 한다.
		//TransPose();

		//// XYZ돌아서 어떤 물체를 바라보고 있는 카메라
		//// 회전행렬을 역으로 돌려야 한다.
		//// -X-Y-Z돌아서 어떤 물체를 원점으로 돌리게 만들어야 하는데.
		//// 전치행렬 Transpose를 만들어야 한다..

		//float4 NegEyePos = -EyePos;

		//// 모든 물체가 이동해야할 방향을 구하고 있다.
		//float XValue = float4::DotProduct3D(EyeRight, NegEyePos);
		//float YValue = float4::DotProduct3D(EyeUp, NegEyePos);
		//float ZValue = float4::DotProduct3D(EyeForward, NegEyePos);

		//// 위치
		//ArrVector[3] = { XValue, YValue, ZValue };
	}

	//               보통 모니터 크기를 넣어주는데
	//               그냥 보고싶은 너비와 높이의 수치만 넣어주면 됩니다.
	//                      1280                 720           5000
	void OrthographicLH(float _Width, float _Height, float _Near, float _Far)
	{
		DirectXMatrix = DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);

		//// DirectX::XMMatrixOrthographicLH
		//Identity();
		////                     5000 - 0.1
		//float fRange = 1.0f / (_Far - _Near);
		//Arr2D[0][0] = 2.0f / _Width;
		//Arr2D[1][1] = 2.0f / _Height;
		//Arr2D[2][2] = fRange;
		//Arr2D[3][2] = -fRange * _Near;
	}

	//      60도를 본다.                    200              100
	// 수직
	void PerspectiveFovLH(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	{
		PerspectiveFovLH(_FovAngle, _Width / _Height, _Near, _Far);
	}

	// 수직 시야각 
	// 1000.0f 0.1f
	void PerspectiveFovLH(float _FovAngle, float _AspectRatio, float _Near, float _Far)
	{
		DirectXMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovAngle, _AspectRatio, _Near, _Far);

		//Identity();

		//// DirectX::XMMatrixPerspectiveFovLH()

		//float YFOV = _FovAngle * GameEngineMath::D2R;

		//// 원근 투영행렬에서 특징적인 부분.
		//Arr2D[2][3] = 1.0f;
		//Arr2D[3][3] = 0.0f;

		//// 투영행렬의 규칙은
		//// 모든 오브젝트의 모든 점을 -1 사이의 공간에 넣는것이다.

		//// 요 2값은 제대로된 
		//
		//// x와 곱해질 비율
		//Arr2D[0][0] = 1.0f / (tanf(YFOV / 2.0f) * _AspectRatio); // / 600


		//// y와 곱해질 비율
		//// 1나누기를 하는 이유는?
		//// -1 1사이의 값으로 만들려고.
		//
		//// 근본적인 원근투영의 원리는
		//// z값이 클수록 y값이 줄어든다.
		//// 이 y * 
		//Arr2D[1][1] = 1.0f / tanf(YFOV / 2.0f);  // / 600

		//// 1000 

		////     100    100   100 * 투영
		////  * 0.5f          *0.5f
		////                  50.0f

		//// 범위안에 있는 녀석들 다 0~1사이의 값으로 바꿉니다.
		//// 1000 * 0.9784123f
		////           1000  / (1000 - 0.1f);
		//Arr2D[2][2] = _Far / (_Far - _Near);

		//// 이동이 이 좀 들어가기는 했는데
		//Arr2D[3][2] = -(_Near * _Far) / (_Far - _Near);
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
		// float4x4 Result;
		const float4x4& A = *this;
		const float4x4& B = _Other;

		return DirectX::XMMatrixMultiply(A.DirectXMatrix, B.DirectXMatrix);

		//Result.Arr2D[0][0] = (A.Arr2D[0][0] * B.Arr2D[0][0]) + (A.Arr2D[0][1] * B.Arr2D[1][0]) + (A.Arr2D[0][2] * B.Arr2D[2][0]) + (A.Arr2D[0][3] * B.Arr2D[3][0]);
		//Result.Arr2D[0][1] = (A.Arr2D[0][0] * B.Arr2D[0][1]) + (A.Arr2D[0][1] * B.Arr2D[1][1]) + (A.Arr2D[0][2] * B.Arr2D[2][1]) + (A.Arr2D[0][3] * B.Arr2D[3][1]);
		//Result.Arr2D[0][2] = (A.Arr2D[0][0] * B.Arr2D[0][2]) + (A.Arr2D[0][1] * B.Arr2D[1][2]) + (A.Arr2D[0][2] * B.Arr2D[2][2]) + (A.Arr2D[0][3] * B.Arr2D[3][2]);
		//Result.Arr2D[0][3] = (A.Arr2D[0][0] * B.Arr2D[0][3]) + (A.Arr2D[0][1] * B.Arr2D[1][3]) + (A.Arr2D[0][2] * B.Arr2D[2][3]) + (A.Arr2D[0][3] * B.Arr2D[3][3]);

		//Result.Arr2D[1][0] = (A.Arr2D[1][0] * B.Arr2D[0][0]) + (A.Arr2D[1][1] * B.Arr2D[1][0]) + (A.Arr2D[1][2] * B.Arr2D[2][0]) + (A.Arr2D[1][3] * B.Arr2D[3][0]);
		//Result.Arr2D[1][1] = (A.Arr2D[1][0] * B.Arr2D[0][1]) + (A.Arr2D[1][1] * B.Arr2D[1][1]) + (A.Arr2D[1][2] * B.Arr2D[2][1]) + (A.Arr2D[1][3] * B.Arr2D[3][1]);
		//Result.Arr2D[1][2] = (A.Arr2D[1][0] * B.Arr2D[0][2]) + (A.Arr2D[1][1] * B.Arr2D[1][2]) + (A.Arr2D[1][2] * B.Arr2D[2][2]) + (A.Arr2D[1][3] * B.Arr2D[3][2]);
		//Result.Arr2D[1][3] = (A.Arr2D[1][0] * B.Arr2D[0][3]) + (A.Arr2D[1][1] * B.Arr2D[1][3]) + (A.Arr2D[1][2] * B.Arr2D[2][3]) + (A.Arr2D[1][3] * B.Arr2D[3][3]);

		//Result.Arr2D[2][0] = (A.Arr2D[2][0] * B.Arr2D[0][0]) + (A.Arr2D[2][1] * B.Arr2D[1][0]) + (A.Arr2D[2][2] * B.Arr2D[2][0]) + (A.Arr2D[2][3] * B.Arr2D[3][0]);
		//Result.Arr2D[2][1] = (A.Arr2D[2][0] * B.Arr2D[0][1]) + (A.Arr2D[2][1] * B.Arr2D[1][1]) + (A.Arr2D[2][2] * B.Arr2D[2][1]) + (A.Arr2D[2][3] * B.Arr2D[3][1]);
		//Result.Arr2D[2][2] = (A.Arr2D[2][0] * B.Arr2D[0][2]) + (A.Arr2D[2][1] * B.Arr2D[1][2]) + (A.Arr2D[2][2] * B.Arr2D[2][2]) + (A.Arr2D[2][3] * B.Arr2D[3][2]);
		//Result.Arr2D[2][3] = (A.Arr2D[2][0] * B.Arr2D[0][3]) + (A.Arr2D[2][1] * B.Arr2D[1][3]) + (A.Arr2D[2][2] * B.Arr2D[2][3]) + (A.Arr2D[2][3] * B.Arr2D[3][3]);

		//Result.Arr2D[3][0] = (A.Arr2D[3][0] * B.Arr2D[0][0]) + (A.Arr2D[3][1] * B.Arr2D[1][0]) + (A.Arr2D[3][2] * B.Arr2D[2][0]) + (A.Arr2D[3][3] * B.Arr2D[3][0]);
		//Result.Arr2D[3][1] = (A.Arr2D[3][0] * B.Arr2D[0][1]) + (A.Arr2D[3][1] * B.Arr2D[1][1]) + (A.Arr2D[3][2] * B.Arr2D[2][1]) + (A.Arr2D[3][3] * B.Arr2D[3][1]);
		//Result.Arr2D[3][2] = (A.Arr2D[3][0] * B.Arr2D[0][2]) + (A.Arr2D[3][1] * B.Arr2D[1][2]) + (A.Arr2D[3][2] * B.Arr2D[2][2]) + (A.Arr2D[3][3] * B.Arr2D[3][2]);
		//Result.Arr2D[3][3] = (A.Arr2D[3][0] * B.Arr2D[0][3]) + (A.Arr2D[3][1] * B.Arr2D[1][3]) + (A.Arr2D[3][2] * B.Arr2D[2][3]) + (A.Arr2D[3][3] * B.Arr2D[3][3]);

		//return Result;
	}
};