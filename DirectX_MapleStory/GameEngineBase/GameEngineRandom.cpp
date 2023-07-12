#include "PreCompile.h"
#include "GameEngineRandom.h"
#include <iostream>

GameEngineRandom::GameEngineRandom() 
{
}

GameEngineRandom::GameEngineRandom(int _Seed)
{
}

int GameEngineRandom::RandomInt(int _Min, int _Max)
{
	std::uniform_int_distribution<int> RandomCreator(_Min, _Max);
	return RandomCreator(MtGen);
}

float GameEngineRandom::RandomFloat(float _Min, float _Max)
{
	std::uniform_real_distribution<float> RandomCreator(_Min, _Max);
	return RandomCreator(MtGen);
}

GameEngineRandom::~GameEngineRandom() 
{
}

