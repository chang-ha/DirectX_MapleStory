#pragma once
#include "GameEngineObject.h"

// ���� : ���Ϳ� ������Ʈ���� �Բ� ����� ���� ��ɵ��� ��Ƴ��� ���̴�.
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

