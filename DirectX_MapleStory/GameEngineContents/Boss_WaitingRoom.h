#pragma once
#include "ContentLevel.h"

class Boss_WaitingRoom : public ContentLevel
{
public:
	// constructer destructer
	Boss_WaitingRoom();
	~Boss_WaitingRoom();

	// delete function
	Boss_WaitingRoom(const Boss_WaitingRoom& _Ohter) = delete;
	Boss_WaitingRoom(Boss_WaitingRoom&& _Ohter) noexcept = delete;
	Boss_WaitingRoom& operator=(const Boss_WaitingRoom& _Other) = delete;
	Boss_WaitingRoom& operator=(Boss_WaitingRoom&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void ResourcesRelease() override;

private:
	std::shared_ptr<class ContentBackGround> Back = nullptr;
	std::shared_ptr<class Player> CurPlayer = nullptr;
};

