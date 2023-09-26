#pragma once
#include "BaseBossActor.h"

enum class LucidState
{
	Idle,
	Death,
	Skill1, // Shoot
	Skill2, // Summon Dragon
	Skill3, // Teleport
	Skill4, // Summon Butterfly, Golem, Mushroom
};

class Boss_Lucid_Phase1 : public BaseBossActor
{
public:
	// constructer destructer
	Boss_Lucid_Phase1();
	~Boss_Lucid_Phase1();

	// delete function
	Boss_Lucid_Phase1(const Boss_Lucid_Phase1& _Ohter) = delete;
	Boss_Lucid_Phase1(Boss_Lucid_Phase1&& _Ohter) noexcept = delete;
	Boss_Lucid_Phase1& operator=(const Boss_Lucid_Phase1& _Other) = delete;
	Boss_Lucid_Phase1& operator=(Boss_Lucid_Phase1&& _Other) noexcept = delete;

	void ChangeState(LucidState _State);
	void StateUpdate(float _Delta);

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> FlowerRenderer = nullptr;
	LucidState State = LucidState::Idle;

	///// State
	// Start
	void IdleStart();
	void DeathStart();
	void Skill1Start(); 
	void Skill2Start(); 
	void Skill3Start();
	void Skill4Start();
	//
	// Update
	void IdleUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void Skill1Update(float _Delta);
	void Skill2Update(float _Delta);
	void Skill3Update(float _Delta);
	void Skill4Update(float _Delta);
	// 
	// End
	void IdleEnd();
	void DeathEnd();
	void Skill1End();
	void Skill2End();
	void Skill3End();
	void Skill4End();
	// 
	/////
};

