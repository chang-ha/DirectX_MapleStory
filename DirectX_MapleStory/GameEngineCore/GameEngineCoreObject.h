#pragma once
#include "GameEngineObject.h"

// 설명 : 액터와 컴포넌트들이 함께 사용할 편의 기능들을 모아놓을 것이다.
class GameEngineCoreObject : public GameEngineObject
{
public:
	// constrcuter destructer
	GameEngineCoreObject();
	~GameEngineCoreObject();

	// delete Function
	GameEngineCoreObject(const GameEngineCoreObject& _Other) = delete;
	GameEngineCoreObject(GameEngineCoreObject&& _Other) noexcept = delete;
	GameEngineCoreObject& operator=(const GameEngineCoreObject& _Other) = delete;
	GameEngineCoreObject& operator=(GameEngineCoreObject&& _Other) noexcept = delete;

protected:
	class GameEngineLevel* GetLevel();
	class GameEngineActor* GetActor();

private:

};

