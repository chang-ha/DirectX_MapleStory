#pragma once
#include "ClockTowerBaseLevel.h"

class ClockTowerOfNightMare_5th : public ClockTowerBaseLevel
{
public:
	// constructer destructer
	ClockTowerOfNightMare_5th();
	~ClockTowerOfNightMare_5th();

	// delete function
	ClockTowerOfNightMare_5th(const ClockTowerOfNightMare_5th& _Ohter) = delete;
	ClockTowerOfNightMare_5th(ClockTowerOfNightMare_5th&& _Ohter) noexcept = delete;
	ClockTowerOfNightMare_5th& operator=(const ClockTowerOfNightMare_5th& _Other) = delete;
	ClockTowerOfNightMare_5th& operator=(ClockTowerOfNightMare_5th&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
private:

};

