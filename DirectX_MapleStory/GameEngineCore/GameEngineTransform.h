#pragma once

// ���ϱ����� ǥ���ϰ�
// �θ��ڽİ��踦 ó���Ѵ�.

// �� ����. 
class TransformData 
{
public:
	float4 Scale;
	float4 Rotation;
	float4 Position;
	
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


	float4x4 View;
	float4x4 Projection;
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

	void LookToLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		TransData.View.LookToLH(_EyePos, _EyeDir, _EyeUp);
	}

	const TransformData& GetConstTransformDataRef()
	{
		return TransData;
	}

	// �ٸ� ���� 

	// set
	void SetLocalPosition(const float4& _Value)
	{
		TransData.Position = _Value;
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

	void TransformUpdate();

	void SetParent(GameEngineTransform& _Parent)
	{
		Parent = &_Parent;
	}

protected:

private:
	GameEngineTransform* Parent = nullptr;

	TransformData TransData;
};
