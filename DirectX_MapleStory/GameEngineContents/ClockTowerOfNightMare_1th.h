#pragma once
#include "ClockTowerBaseLevel.h"

class ClockTowerOfNightMare_1th : public ClockTowerBaseLevel
{
public:
	// constructer destructer
	ClockTowerOfNightMare_1th();
	~ClockTowerOfNightMare_1th();

	// delete function
	ClockTowerOfNightMare_1th(const ClockTowerOfNightMare_1th& _Ohter) = delete;
	ClockTowerOfNightMare_1th(ClockTowerOfNightMare_1th&& _Ohter) noexcept = delete;
	ClockTowerOfNightMare_1th& operator=(const ClockTowerOfNightMare_1th& _Other) = delete;
	ClockTowerOfNightMare_1th& operator=(ClockTowerOfNightMare_1th&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
private:

};

