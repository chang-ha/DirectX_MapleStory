#pragma once
#include "EngineEnum.h"

// 기하구조를 표현하고
// 부모자식관계를 처리한다.

enum class ColType
{
	// 캡슐
	// 2D에서의 충돌은 모두가 한축이 같아야 한다.
	// 우리는 충돌이 2D가 더 느려요.
	SPHERE2D, // z를 0으로 만들고 충돌 구 
	AABBBOX2D, // z를 0으로 만들고 충돌 Axis-Aligned Bounding 회전하지 않은 박스
	OBBBOX2D, // z를 0으로 만들고 충돌 Oriented Bounding Box 회전한 박스 <= 을 1번할 연산량으로 SPHER를 50 60개를 돌릴수가 있다.
	SPHERE3D,
	AABBBOX3D,
	OBBBOX3D,
	MAX,
};

class CollisionData
{
public:
	union
	{
		// 다이렉트 x에서 지원해주는 충돌용 도형
		DirectX::BoundingSphere SPHERE;     // 위치 위치 위치 크기 (16바이트)
		DirectX::BoundingBox AABB;		    // 위치 위치 위치 크기 크기 크기 (24바이트)
		DirectX::BoundingOrientedBox OBB;   // 위치 위치 위치 크기 크기 크기 회전 회전 회전 회전 (40바이트)
	};

	CollisionData()
		: OBB()
	{

	}
};

class GameEngineTransform;
class CollisionParameter
{
public:
	CollisionData& Left;
	CollisionData& Right;
	ColType LeftType = ColType::AABBBOX2D;
	ColType RightType = ColType::AABBBOX2D;

	inline int GetLeftTypeToInt() const
	{
		return static_cast<int>(LeftType);
	}

	inline int GetRightTypeToInt() const
	{
		return static_cast<int>(RightType);
	}

	CollisionParameter(
		CollisionData& _Left,
		CollisionData& _Right,
		ColType _LeftType = ColType::AABBBOX2D,
		ColType _RightType = ColType::AABBBOX2D
	)
		:
		Left(_Left),
		Right(_Right),
		LeftType(_LeftType),
		RightType(_RightType)
	{
	}
};

// 왜 굳이. 
class TransformData 
{
public:
	// w가 0일때와 1일때의 차이를 잘 기억해놓자.

	float4 Scale = float4::ONENULL;
	float4 Rotation = float4::ZERONULL;
	float4 Quaternion = float4::ZERO;
	float4 Position = float4::ZERO;
	
	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalQuaternion;
	float4 LocalPosition;

	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldQuaternion;
	float4 WorldPosition;

	float4x4 ScaleMatrix; // 크
	float4x4 RotationMatrix; // 자
	float4x4 PositionMatrix; // 이
	float4x4 RevolutionMatrix; // 공
	float4x4 ParentMatrix; // 공

	float4x4 LocalWorldMatrix;
	// 월드 공간
	float4x4 WorldMatrix;


	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
	float4x4 ViewPort;

	// 로컬 => 월드 => 뷰 => 프로젝션 
	float4x4 WorldViewProjectionMatrix;

	void LocalCalculation()
	{
		ScaleMatrix.Scale(Scale);
		RotationMatrix.RotationDeg(Rotation);
		PositionMatrix.Position(Position);

		LocalWorldMatrix = ScaleMatrix * RotationMatrix * PositionMatrix * RevolutionMatrix;
		WorldMatrix = LocalWorldMatrix;
	}

	void WorldViewProjectionCalculation()
	{
		WorldViewProjectionMatrix = WorldMatrix * ViewMatrix * ProjectionMatrix;
	}

	void operator=(const TransformData& _Other)
	{
		memcpy_s(this, sizeof(TransformData), &_Other, sizeof(TransformData));
	}

	TransformData()
	{

	}

	TransformData(const TransformData& _Other)
	{
		memcpy_s(this, sizeof(TransformData), &_Other, sizeof(TransformData));
	}
};

// 설명 :
class GameEngineTransform
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

	void OrthographicLH(float _Width, float _Height, float _Near, float _Far)
	{
		TransData.ProjectionMatrix.OrthographicLH(_Width, _Height, _Near, _Far);
	}

	void PerspectiveFovLHDeg(float _FovAngle, float _Width, float _Height, float _Near, float _Far)
	{
		TransData.ProjectionMatrix.PerspectiveFovLHDeg(_FovAngle, _Width, _Height, _Near, _Far);
	}

	void LookToLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		TransData.ViewMatrix.LookToLH(_EyePos, _EyeDir, _EyeUp);
	}

	const TransformData& GetConstTransformDataRef()
	{
		return TransData;
	}

	// Set Local
	void SetLocalScale(const float4& _Value)
	{
		TransData.Scale = _Value;
		TransformUpdate();
	}

	void AddLocalScale(const float4& _Value)
	{
		TransData.Scale += _Value;
		TransformUpdate();
	}

	void SetLocalRotation(const float4& _Value)
	{
		TransData.Rotation = _Value;
		TransformUpdate();
	}

	void AddLocalRotation(const float4& _Value)
	{
		TransData.Rotation += _Value;
		TransformUpdate();

	}

	void SetLocalPosition(const float4& _Value)
	{
		TransData.Position = _Value;
		TransformUpdate();
	}

	void AddLocalPosition(const float4& _Value)
	{
		TransData.Position += _Value;
		TransformUpdate();
		
	}

	// Set World
	bool AbsoluteScale = false;
	bool AbsolutePosition = false;
	bool AbsoluteRotation = false;

	void SetWorldScale(const float4& _Value)
	{
		AbsoluteScale = true;
		TransData.Scale = _Value;
		TransformUpdate();
	}

	void SetWorldRotation(const float4& _Value)
	{
		AbsoluteRotation = true;
		TransData.Rotation = _Value;
		TransformUpdate();
	}

	void SetWorldPosition(const float4& _Value)
	{
		AbsolutePosition = true;
		TransData.Position = _Value;
		TransformUpdate();
	}

	void AddWorldScale(const float4& _Value)
	{
		SetWorldScale(GetWorldScale() + _Value);
	}

	void AddWorldRotation(const float4& _Value)
	{
		SetWorldRotation(GetWorldRotationEuler() + _Value);
	}

	void AddWorldPosition(const float4& _Value)
	{
		SetWorldPosition(GetWorldPosition() + _Value);
	}


	// Get
	float4 GetWorldScale() const
	{
		return TransData.WorldScale;
	}

	float4 GetWorldRotationEuler() const
	{
		return TransData.WorldRotation;
	}

	float4 GetWorldPosition() const
	{
		return TransData.WorldPosition;
	}
	 
	float4 GetLocalScale() const
	{
		return TransData.LocalScale;
	}

	float4 GetLocalRotationEuler() const
	{
		return TransData.LocalRotation;
	}

	float4 GetLocalPosition() const
	{
		return TransData.LocalPosition;
	}

	// 회전 그 자체로 한 오브젝트의 앞 위 오른쪽
	// [1][0][0][0] 오른쪽
	// [0][1][0][0] 위
	// [0][0][1][0] 앞
	// [0][0][0][1]

	float4 GetWorldForwardVector() const
	{
		return TransData.WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetWorldBackVector() const
	{
		return -(TransData.WorldMatrix.ArrVector[2].NormalizeReturn());
	}


	float4 GetWorldRightVector() const
	{
		return TransData.WorldMatrix.ArrVector[0].NormalizeReturn();
	}

	float4 GetWorldLeftVector() const
	{
		return -(TransData.WorldMatrix.ArrVector[0].NormalizeReturn());
	}

	float4 GetWorldUpVector() const
	{
		return TransData.WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetWorldDownVector() const
	{
		return TransData.WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4x4 GetWorldViewProjectionMatrix()
	{
		return TransData.WorldViewProjectionMatrix;
	}

	void CalculationViewAndProjection(const TransformData& _Transform);

	void CalculationViewAndProjection(const float4x4& _View, const float4x4& _Projection);

	void TransformUpdate();

	void SetParent(GameEngineTransform& _Parent)
	{
		Parent = &_Parent;
		Parent->Childs.push_back(this);
		TransformUpdate();
	}

	void SetTransformData(const TransformData& Data)
	{
		TransData = Data;
	}

	void CalChilds();

	static bool Collision(const CollisionParameter& _Data);

	CollisionData ColData;
protected:

private:

	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Childs;
	TransformData TransData;

};

