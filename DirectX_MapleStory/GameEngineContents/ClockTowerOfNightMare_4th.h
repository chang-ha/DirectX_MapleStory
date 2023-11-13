#pragma once
#include "ClockTowerBaseLevel.h"

class ClockTowerOfNightMare_4th : public ClockTowerBaseLevel
{
public:
	// constructer destructer
	ClockTowerOfNightMare_4th();
	~ClockTowerOfNightMare_4th();

	// delete function
	ClockTowerOfNightMare_4th(const ClockTowerOfNightMare_4th& _Ohter) = delete;
	ClockTowerOfNightMare_4th(ClockTowerOfNightMare_4th&& _Ohter) noexcept = delete;
	ClockTowerOfNightMare_4th& operator=(const ClockTowerOfNightMare_4th& _Other) = delete;
	ClockTowerOfNightMare_4th& operator=(ClockTowerOfNightMare_4th&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
private:

};

