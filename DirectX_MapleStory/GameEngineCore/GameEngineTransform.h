#pragma once

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

	float4 ScaleMatrix;
	float4 RotationMatrix;
	float4 PositionMatrix;
	float4 LocalWorldMatrix;
	float4 WorldMatrix;
	float4 View;
	float4 Projection;
	float4 ViewPort;
	float4 WorldViewPorjectionMatrix;
};

class GameEngineTransform
{
public:
	// constructer destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete function
	GameEngineTransform(const GameEngineTransform& _Ohter) = delete;
	GameEngineTransform(GameEngineTransform&& _Ohter) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

protected:

private:
	TransformData TransData;

};

