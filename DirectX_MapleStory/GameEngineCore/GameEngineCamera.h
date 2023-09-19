#pragma once
#include "GameEngineActor.h"
#include <map>
#include <list>
#include <memory>

enum EPROJECTIONTYPE
{
	Perspective,
	Orthographic,
};


// Ό³Έν :
class GameEngineCamera : public GameEngineActor
{
	friend class GameEngineRenderer;
	friend class GameEngineActor;
	friend class GameEngineLevel;

public:
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

protected:
	void Start() override;

	void Update(float _Delta);

	void Render(float _DeltaTime);

	void AllReleaseCheck() override;

private:
	EPROJECTIONTYPE ProjectionType = EPROJECTIONTYPE::Orthographic;
	float Far = 1000.0f;
	float Near = 0.1f;
	float FOV = 60.0f;

	int CameraOrder = 0;
	std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> Renderers;
};

