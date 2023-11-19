#pragma once
#include "BaseSkillActor.h"

#define HIT_TIME 0.2f
#define SOUNDLOOP_DELAY 0.8f

class PhalanxCharge_Actor : public BaseSkillActor
{
	friend class PhalanxCharge;
public:
	static PhalanxCharge_Actor* Main_PhalanxCharge;

public:
	// constructer destructer
	PhalanxCharge_Actor();
	~PhalanxCharge_Actor();

	// delete function
	PhalanxCharge_Actor(const PhalanxCharge_Actor& _Ohter) = delete;
	PhalanxCharge_Actor(PhalanxCharge_Actor&& _Ohter) noexcept = delete;
	PhalanxCharge_Actor& operator=(const PhalanxCharge_Actor& _Other) = delete;
	PhalanxCharge_Actor& operator=(PhalanxCharge_Actor&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	std::map<std::shared_ptr<GameEngineCollision>, float> CollisionTime;

private:
	int HitCount = 0;
	float SoundLoopTime = SOUNDLOOP_DELAY;
	float4 MoveDir = float4::ZERO;
	GameEngineSoundPlayer PhalanPlayer;

	void SwitchDir();
	void CollisionTimeUpdate(float _Delta);
};

