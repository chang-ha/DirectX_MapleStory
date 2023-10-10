#pragma once
#include "BaseBossActor.h"

#define Skill1_Colldown 3.0f
#define Skill2_Cooldown 13.0f
#define Teleport_Cooldown 10.0f
#define Summon_Mush_Cooldown 7.0f 
#define Summon_Golem_Cooldown 5.0f 

enum class LucidState
{
	Idle,
	Death,
	Skill1, // Shoot
	Skill2, // Summon Dragon
	Skill3, // Teleport
	Summon_Mush,  
	Summon_Golem, 
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
	void Release() override;

	void Start() override;
	void Update(float _Delta) override;

private:
	float Skill1Cooldown = Skill1_Colldown;
	float Skill2Cooldown = Skill2_Cooldown;
	float TeleportCooldown = Teleport_Cooldown;
	float MushCooldown = Summon_Mush_Cooldown;
	float GolemCooldown = Summon_Golem_Cooldown;
	std::shared_ptr<GameEngineSpriteRenderer> FlowerRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> TeleportRenderer = nullptr;
	LucidState State = LucidState::Idle;

	///// State
	// Start
	void IdleStart();
	void DeathStart();
	void Skill1Start(); 
	void Skill2Start(); 
	void Skill3Start();
	void Summon_MushStart();
	void Summon_GolemStart();
	//
	// Update
	void IdleUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void Skill1Update(float _Delta);
	void Skill2Update(float _Delta);
	void Skill3Update(float _Delta);
	void Summon_MushUpdate(float _Delta);
	void Summon_GolemUpdate(float _Delta);
	// 
	// End
	void IdleEnd();
	void DeathEnd();
	void Skill1End();
	void Skill2End();
	void Skill3End();
	void Summon_MushEnd();
	void Summon_GolemEnd();
	// 
	/////
};

