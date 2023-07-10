#pragma once
#include "GameEngineFile.h"

// Ό³Έν :
class GameEngineDirectory : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	GameEngineDirectory(const std::string& _path);
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	std::vector<class GameEngineFile> GetAllFile(std::vector<std::string> _Ext);

protected:

private:

};

