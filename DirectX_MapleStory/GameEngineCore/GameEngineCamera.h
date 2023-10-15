#pragma once
#include "GameEngineActor.h"
#include <map>
#include <list>
#include <memory>

// 설명 :
class GameEngineCamera : public GameEngineActor
{
	friend class GameEngineRenderer;
	friend class GameEngineActor;
	friend class GameEngineLevel;

public:
	static float FreeRotSpeed;
	static float FreeSpeed;

	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	void SetCameraOrder(int _Order);

	inline void SetProjectionType(EPROJECTIONTYPE _ProjectionType)
	{
		ProjectionType = _ProjectionType;
	}

	float4 GetWorldMousePos2D();

	void SetZoomValue(float _Value)
	{
		ZoomValue = _Value;
	}

	void AddZoomValue(float _Value)
	{
		ZoomValue += _Value;
	}

	bool IsFreeCamera()
	{
		return IsFreeCameraValue;
	}


	void CameraTargetSetting(GameEngineTransform& _Target, float4 _Pivot)
	{
		Pivot = _Pivot;
		Target = &_Target;
	}

	void CameraTargetReset()
	{
		Pivot = float4::ZERO;
		Target = nullptr;
	}

	float4 GetScreenMousePrevPos() { return ScreenMousePrevPos; }
	float4 GetScreenMousePos() { return ScreenMousePos; }
	float4 GetScreenMouseDir() { return ScreenMouseDir; }
	float4 GetScreenMouseDirNormal() { return ScreenMouseDirNormal; }

protected:
	void Start() override;

	void Update(float _Delta);

	void Render(float _DeltaTime);

	void AllReleaseCheck() override;

private:
	float4 Pivot = float4::ZERO;
	GameEngineTransform* Target = nullptr;

	EPROJECTIONTYPE ProjectionType = EPROJECTIONTYPE::Orthographic;
	float Far = 10000.0f;
	float Near = 0.1f;
	float FOV = 60.0f;
	float ZoomValue = 0.0f;

	bool IsFreeCameraValue = false;

	int CameraOrder = 0;
	std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> Renderers;

	EPROJECTIONTYPE PrevProjectionType = EPROJECTIONTYPE::Orthographic; // FreeCamera하기 전 투영방식 저장

	float4 ScreenMousePrevPos;
	float4 ScreenMousePos;
	float4 ScreenMouseDir;
	float4 ScreenMouseDirNormal;
	TransformData OriginData; // FreeCamera하기 전 Transform 저장

	void CameraUpdate(float _DeltaTime);
};

