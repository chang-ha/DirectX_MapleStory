#pragma once
#include "ContentLevel.h"

class ClockTowerBaseLevel : public ContentLevel
{
public:
	// constructer destructer
	ClockTowerBaseLevel();
	~ClockTowerBaseLevel();

	// delete function
	ClockTowerBaseLevel(const ClockTowerBaseLevel& _Ohter) = delete;
	ClockTowerBaseLevel(ClockTowerBaseLevel&& _Ohter) noexcept = delete;
	ClockTowerBaseLevel& operator=(const ClockTowerBaseLevel& _Other) = delete;
	ClockTowerBaseLevel& operator=(ClockTowerBaseLevel&& _Other) noexcept = delete;

protected:
	float4 CurMapScale = float4::ZERO;
	float4 StartPos = float4::ZERO;

	std::shared_ptr<class ContentBackGround> Back = nullptr;
	std::shared_ptr<class Player> CurPlayer = nullptr;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

private:

};

