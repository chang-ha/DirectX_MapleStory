#pragma once
#include "GameEnginePath.h"
#include <string>

// Ό³Έν :
class GameEngineFile : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineFile();
	GameEngineFile(const std::string& _path);
	~GameEngineFile();

	//// delete Function
	//GameEngineFile(const GameEngineFile& _Other) = delete;
	//GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	//GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	//GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;

protected:

private:

};

