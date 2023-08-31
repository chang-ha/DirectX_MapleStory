#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineComponent.h"

GameEngineActor::GameEngineActor() 
{
}

GameEngineActor::~GameEngineActor() 
{
}


GameEngineLevel* GameEngineActor::GetLevel()
{
	// 나중에 문제가 될거라고 한겁니다.

	return GetParent<GameEngineLevel>();
}

void GameEngineActor::ComponentInit(std::shared_ptr<GameEngineComponent> _Component, int _Order)
{
	_Component->SetOrder(_Order);
	_Component->SetParent(this, _Order);
	_Component->Start();
}