#pragma once

// ���ϱ����� ǥ���ϰ�
// �θ��ڽİ��踦 ó���Ѵ�.

// �� ����. 
class TransformData 
{
public:
	// w�� 0�϶��� 1�϶��� ���̸� �� ����س���.

	float4 Scale = float4::ONENULL;
	float4 Rotation = float4::ZERONULL;
	float4 Position = float4::ZERO;
	
	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalPosition;

	float4 WorldScale;
	float4 WorldRotation;
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
	float4x4 WorldViewPorjectionMatrix;

	void LocalCalculation()
	{
		ScaleMatrix.Scale(Scale);
		RotationMatrix.RotationDeg(Rotation);
		PositionMatrix.Position(Position);

		LocalWorldMatrix = ScaleMatrix * RotationMatrix * PositionMatrix * RevolutionMatrix;
	}

	void WorldViewProjectionCalculation()
	{
		WorldViewPorjectionMatrix = WorldMatrix * ViewMatrix * ProjectionMatrix;
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

	void CalculationViewAndProjection(const TransformData& _Transform);

	void CalculationViewAndProjection(const float4x4& _View, const float4x4& _Projection);

	void TransformUpdate();

	void SetParent(GameEngineTransform& _Parent)
	{
		Parent = &_Parent;
		Parent->Childs.push_back(this);
	}

	void CalChilds();

protected:

private:
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Childs;
	TransformData TransData;

};

