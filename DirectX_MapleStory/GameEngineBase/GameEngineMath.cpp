#include "PreCompile.h"
#include "GameEngineMath.h"


const float4 float4::ONE = { 1.0f, 1.0f, 1.0f, 1.0f };
const float4 float4::ONENULL = { 1.0f, 1.0f, 1.0f, 0.0f };
const float4 float4::ZERO = { 0.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::ZERONULL = { 0.0f, 0.0f, 0.0f, 0.0f };

const float4 float4::LEFT = { -1.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::RIGHT = { 1.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::UP = { 0.0f, 1.0f, 0.0f, 0.0f };
const float4 float4::DOWN = { 0.0f, -1.0f, 0.0f, 0.0f };
const float4 float4::FORWARD = { 0.0f, 0.0f, 1.0f, 0.0f };
const float4 float4::BACKWARD = { 0.0f, 0.0f, -1.0f, 0.0f };

const float GameEngineMath::PI = 3.14159265358979323846264338327950288419716939937510f;
const float GameEngineMath::PI2 = PI * 2.0f;

// Radian To Degree, Degree To Radian
const float GameEngineMath::R2D = 180.0f / GameEngineMath::PI;
const float GameEngineMath::D2R = GameEngineMath::PI / 180.0f;


float4 float4::operator*(const float4x4& _Other) const
{
	float4 Result;
	const float4& A = *this;
	const float4x4& B = _Other;

	//Result.Arr2D[0][0] = (A.Arr2D[0][0] * B.Arr2D[0][0]) + (A.Arr2D[0][1] * B.Arr2D[1][0]) + (A.Arr2D[0][2] * B.Arr2D[2][0]) + (A.Arr2D[0][3] * B.Arr2D[3][0]);
	//Result.Arr2D[0][1] = (A.Arr2D[0][0] * B.Arr2D[0][1]) + (A.Arr2D[0][1] * B.Arr2D[1][1]) + (A.Arr2D[0][2] * B.Arr2D[2][1]) + (A.Arr2D[0][3] * B.Arr2D[3][1]);
	//Result.Arr2D[0][2] = (A.Arr2D[0][0] * B.Arr2D[0][2]) + (A.Arr2D[0][1] * B.Arr2D[1][2]) + (A.Arr2D[0][2] * B.Arr2D[2][2]) + (A.Arr2D[0][3] * B.Arr2D[3][2]);
	//Result.Arr2D[0][3] = (A.Arr2D[0][0] * B.Arr2D[0][3]) + (A.Arr2D[0][1] * B.Arr2D[1][3]) + (A.Arr2D[0][2] * B.Arr2D[2][3]) + (A.Arr2D[0][3] * B.Arr2D[3][3]);

	Result = DirectX::XMVector3Transform(A.DirectXVector, B.DirectXMatrix);

	return Result;
}

float4& float4::operator*=(const class float4x4& _Other)
{
	float4 Result = operator*(_Other);
	*this = Result;
	return *this;
}

float4 float4::VectorRotationToRadX(const float4& _Value, const float _Rad)
{
	float4x4 Rot;
	Rot.RotationXRad(_Rad);
	return _Value * Rot;
}

float4 float4::VectorRotationToRadY(const float4& _Value, const float _Rad)
{
	float4x4 Rot;
	Rot.RotationYRad(_Rad);
	return _Value * Rot;
}

float4 float4::VectorRotationToRadZ(const float4& _Value, const float _Rad)
{
	float4x4 Rot;
	Rot.RotationZRad(_Rad);
	return _Value * Rot;
}