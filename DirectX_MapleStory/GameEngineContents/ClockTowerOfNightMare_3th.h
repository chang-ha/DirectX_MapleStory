#pragma once
#include "ClockTowerBaseLevel.h"

class ClockTowerOfNightMare_3th : public ClockTowerBaseLevel
{
public:
	// constructer destructer
	ClockTowerOfNightMare_3th();
	~ClockTowerOfNightMare_3th();

	// delete function
	ClockTowerOfNightMare_3th(const ClockTowerOfNightMare_3th& _Ohter) = delete;
	ClockTowerOfNightMare_3th(ClockTowerOfNightMare_3th&& _Ohter) noexcept = delete;
	ClockTowerOfNightMare_3th& operator=(const ClockTowerOfNightMare_3th& _Other) = delete;
	ClockTowerOfNightMare_3th& operator=(ClockTowerOfNightMare_3th&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
private:

};

