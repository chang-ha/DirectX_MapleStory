#pragma once
#include "BaseBossActor.h"

enum class LucidState
{
	Idle,
	Death,
	Summon_Golem,
};

class Boss_Lucid_Phase2 : public BaseBossActor
{
public:
	// constructer destructer
	Boss_Lucid_Phase2();
	~Boss_Lucid_Phase2();

	// delete function
	Boss_Lucid_Phase2(const Boss_Lucid_Phase2& _Ohter) = delete;
	Boss_Lucid_Phase2(Boss_Lucid_Phase2&& _Ohter) noexcept = delete;
	Boss_Lucid_Phase2& operator=(const Boss_Lucid_Phase2& _Other) = delete;
	Boss_Lucid_Phase2& operator=(Boss_Lucid_Phase2&& _Other) noexcept = delete;

	void ChangeState(LucidState _State);
	void StateUpdate(float _Delta);

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
private:
	LucidState State = LucidState::Idle;

	///// State
	// Start
	void IdleStart();
	void DeathStart();
	void Summon_GolemStart();
	//
	// Update
	void IdleUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void Summon_GolemUpdate(float _Delta);
	// 
	// End
	void IdleEnd();
	void DeathEnd();
	void Summon_GolemEnd();
	// 
	/////
};
