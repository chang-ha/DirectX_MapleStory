#pragma once
#include "ContentLevel.h"

class Boss_ClearRoom : public ContentLevel
{
public:
	// constructer destructer
	Boss_ClearRoom();
	~Boss_ClearRoom();

	// delete function
	Boss_ClearRoom(const Boss_ClearRoom& _Ohter) = delete;
	Boss_ClearRoom(Boss_ClearRoom&& _Ohter) noexcept = delete;
	Boss_ClearRoom& operator=(const Boss_ClearRoom& _Other) = delete;
	Boss_ClearRoom& operator=(Boss_ClearRoom&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class ContentBackGround> Back = nullptr;
	std::shared_ptr<class Player> CurPlayer = nullptr;
};

