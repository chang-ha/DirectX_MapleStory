#pragma once

// ���ϱ����� ǥ���ϰ�
// �θ��ڽİ��踦 ó���Ѵ�.

enum class ColType
{
	// ĸ��
	// 2D������ �浹�� ��ΰ� ������ ���ƾ� �Ѵ�.
	// �츮�� �浹�� 2D�� �� ������.
	SPHERE2D, // z�� 0���� ����� �浹 �� 
	AABBBOX2D, // z�� 0���� ����� �浹 Axis-Aligned Bounding ȸ������ ���� �ڽ�
	OBBBOX2D, // z�� 0���� ����� �浹 Oriented Bounding Box ȸ���� �ڽ� <= �� 1���� ���귮���� SPHER�� 50 60���� �������� �ִ�.
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
		// ���̷�Ʈ x���� �������ִ� �浹�� ����
		DirectX::BoundingSphere SPHERE;     // ��ġ ��ġ ��ġ ũ�� (16����Ʈ)
		DirectX::BoundingBox AABB;		    // ��ġ ��ġ ��ġ ũ�� ũ�� ũ�� (24����Ʈ)
		DirectX::BoundingOrientedBox OBB;   // ��ġ ��ġ ��ġ ũ�� ũ�� ũ�� ȸ�� ȸ�� ȸ�� ȸ�� (40����Ʈ)
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

// �� ����. 
class TransformData 
{
public:
	// w�� 0�϶��� 1�϶��� ���̸� �� ����س���.

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

	float4x4 ScaleMatrix; // ũ
	float4x4 RotationMatrix; // ��
	float4x4 PositionMatrix; // ��
	float4x4 RevolutionMatrix; // ��
	float4x4 ParentMatrix; // ��

	float4x4 LocalWorldMatrix;
	// ���� ����
	float4x4 WorldMatrix;


	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
	float4x4 ViewPort;

	// ���� => ���� => �� => �������� 
	float4x4 WorldViewProjectionMatrix;

	void LocalCalculation()
	{
		ScaleMatrix.Scale(Scale);
		RotationMatrix.RotationDeg(Rotation);
		PositionMatrix.Position(Position);

		LocalWorldMatrix = ScaleMatrix * RotationMatrix * PositionMatrix * RevolutionMatrix;
	}

	void WorldViewProjectionCalculation()
	{
		WorldViewProjectionMatrix = WorldMatrix * ViewMatrix * ProjectionMatrix;
	}
};

// ���� :
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

	// Get
	float4 GetWorldPosition()
	{
		return TransData.WorldMatrix.ArrVector[3];
	}

	float4 GetLocalScale()
	{
		return TransData.LocalScale;
	}
	// ȸ�� �� ��ü�� �� ������Ʈ�� �� �� ������
	// [1][0][0][0] ������
	// [0][1][0][0] ��
	// [0][0][1][0] ��
	// [0][0][0][1]

	float4 GetWorldForwardVector() 
	{
		return TransData.WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetWorldBackVector()
	{
		return -(TransData.WorldMatrix.ArrVector[2].NormalizeReturn());
	}


	float4 GetWorldRightVector()
	{
		return TransData.WorldMatrix.ArrVector[0].NormalizeReturn();
	}

	float4 GetWorldLeftVector()
	{
		return -(TransData.WorldMatrix.ArrVector[0].NormalizeReturn());
	}

	float4 GetWorldUpVector()
	{
		return TransData.WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetWorldDownVector()
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

