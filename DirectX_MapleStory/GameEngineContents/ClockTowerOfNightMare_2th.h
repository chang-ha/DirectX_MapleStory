#pragma once
#include "ClockTowerBaseLevel.h"

class ClockTowerOfNightMare_2th : public ClockTowerBaseLevel
{
public:
	// constructer destructer
	ClockTowerOfNightMare_2th();
	~ClockTowerOfNightMare_2th();

	// delete function
	ClockTowerOfNightMare_2th(const ClockTowerOfNightMare_2th& _Ohter) = delete;
	ClockTowerOfNightMare_2th(ClockTowerOfNightMare_2th&& _Ohter) noexcept = delete;
	ClockTowerOfNightMare_2th& operator=(const ClockTowerOfNightMare_2th& _Other) = delete;
	ClockTowerOfNightMare_2th& operator=(ClockTowerOfNightMare_2th&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
private:

};

