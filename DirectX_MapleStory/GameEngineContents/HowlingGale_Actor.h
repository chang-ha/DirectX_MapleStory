#pragma once
#include "BaseSkillActor.h"

enum class HowlingGaleState
{
	Ready,
	Attack,
	Death
};

class HowlingGale_Actor : public BaseSkillActor
{
	friend class HowlingGale;
public:
	static HowlingGale_Actor* MainHowlingGale;

public:
	// constructer destructer
	HowlingGale_Actor();
	~HowlingGale_Actor();

	// delete function
	HowlingGale_Actor(const HowlingGale_Actor& _Ohter) = delete;
	HowlingGale_Actor(HowlingGale_Actor&& _Ohter) noexcept = delete;
	HowlingGale_Actor& operator=(const HowlingGale_Actor& _Other) = delete;
	HowlingGale_Actor& operator=(HowlingGale_Actor&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	HowlingGaleState State = HowlingGaleState::Ready;
	GameEngineSoundPlayer HowlingGalePlayer;
};

