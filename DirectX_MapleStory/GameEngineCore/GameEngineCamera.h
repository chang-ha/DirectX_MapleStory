#pragma once
#include "GameEngineActor.h"
#include <map>
#include <list>
#include <memory>

// ī�޶�� ������ ������ �迭�Դϴ�.
// 

// ���� :
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

protected:
	void Start() override;

	void Update(float _Delta);

	void Render(float _DeltaTime);

private:
	int CameraOrder = 0;

	std::map<int, std::list<std::shared_ptr<class GameEngineRenderer>>> Renderers;
};

