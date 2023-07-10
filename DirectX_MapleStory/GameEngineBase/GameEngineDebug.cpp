#include "GameEngineDebug.h"
#include <crtdbg.h>

GameEngineDebug::GameEngineDebug() 
{
}

GameEngineDebug::~GameEngineDebug() 
{
}


void GameEngineDebug::LeckCheck() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}