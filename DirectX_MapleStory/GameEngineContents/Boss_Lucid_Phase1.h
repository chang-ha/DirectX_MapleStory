#pragma once
#include "BaseBossActor.h"

#define Teleport_Cooldown 10.0f
#define Summon_Mush_Cooldown 7.0f 
#define Summon_Golem_Cooldown 5.0f 

enum class LucidState
{
	Idle,
	Death,
	PhantasmalWind, // Shoot
	TeleportSkill, // Teleport
	Summon_Dragon, // Summon Dragon
	Summon_Mush,  
	Summon_Golem,
	Summon_ButterFly,
};

struct Phase1_Boss_Skill_Info
{
	Phase1_Boss_Skill_Info()
	{

	}

	Phase1_Boss_Skill_Info(float _SkillCooldown, LucidState _SkillState)
		: SkillCooldownValue(_SkillCooldown), SkillCooldown(_SkillCooldown), SkillState(_SkillState)
	{

	}

	float SkillCooldownValue = 0.0f;
	float SkillCooldown = 0.0f;
	LucidState SkillState = LucidState::Idle;
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
	std::vector<Phase1_Boss_Skill_Info> SkillInfo;
	std::shared_ptr<GameEngineSpriteRenderer> FlowerRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> TeleportRenderer = nullptr;
	LucidState State = LucidState::Idle;

	///// State
	// Start
	void IdleStart();
	void DeathStart();
	void PhantasmalWindStart();
	void Summon_DragonStart();
	void TeleportSkillStart();
	void Summon_MushStart();
	void Summon_GolemStart();
	void Summon_ButterFlyStart();
	//
	// Update
	void IdleUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void PhantasmalWindUpdate(float _Delta);
	void Summon_DragonUpdate(float _Delta);
	void TeleportSkillUpdate(float _Delta);
	void Summon_MushUpdate(float _Delta);
	void Summon_GolemUpdate(float _Delta);
	void Summon_ButterFlyUpdate(float _Delta);
	// 
	// End
	void IdleEnd();
	void DeathEnd();
	void PhantasmalWindEnd();
	void Summon_DragonEnd();
	void TeleportSkillEnd();
	void Summon_MushEnd();
	void Summon_GolemEnd();
	void Summon_ButterFlyEnd();
	// 
	/////
};

