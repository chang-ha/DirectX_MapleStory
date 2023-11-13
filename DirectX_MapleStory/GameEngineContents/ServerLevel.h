#pragma once
#include "ContentLevel.h"

class ServerLevel : public ContentLevel
{
public:
	// constructer destructer
	ServerLevel();
	~ServerLevel();

	// delete function
	ServerLevel(const ServerLevel& _Ohter) = delete;
	ServerLevel(ServerLevel&& _Ohter) noexcept = delete;
	ServerLevel& operator=(const ServerLevel& _Other) = delete;
	ServerLevel& operator=(ServerLevel&& _Other) noexcept = delete;

protected:

private:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void ResourcesRelease() override;
};

