#include "PreCompile.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

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