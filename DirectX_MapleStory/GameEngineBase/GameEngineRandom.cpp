#include "PreCompile.h"
#include "GameEngineRandom.h"
#include <iostream>

GameEngineRandom::GameEngineRandom() 
{
}

GameEngineRandom::GameEngineRandom(int _Seed)
{
}

GameEngineRandom::~GameEngineRandom()
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

float4 GameEngineRandom::RandomVectorBox2D(float _MinX, float _MaxX, float _MinY, float _MaxY)
{
	float4 Result;

	{
		std::uniform_real_distribution<float> RandomCreator(_MinX > _MaxX ? _MaxX : _MinX, _MinX > _MaxX ? _MinX : _MaxX);
		Result.X = RandomCreator(MtGen);
	}

	{
		std::uniform_real_distribution<float> RandomCreator(_MinY > _MaxY ? _MaxY : _MinY, _MinY > _MaxY ? _MinY : _MaxY);
		Result.Y = RandomCreator(MtGen);
	}

	return Result;
}
