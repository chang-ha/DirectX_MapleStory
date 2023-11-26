#pragma once
#include "BaseBossActor.h"
#include "AttackFunction.h"

#define Laser_Pattern_Cooldown 10.0f
#define BodySlam_Pattern_Cooldown 10.0f

#define Move_Delay_Value 0.05f
#define Accel_MoveSpeed 100.0f
#define Default_MoveSpeed 200.0f
#define Max_MoveSpeed 350.0f

class Lucid_Phase2_GUI : public GameEngineGUIWindow
{
	friend class Boss_Lucid_Phase2;
private:
	bool IsGUIUpdate = true;
	Boss_Lucid_Phase2* _CurBoss = nullptr;
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
};


enum class LucidState
{
	Idle,
	Death,
	PhantasmalWind,
	Laser,
	BodySlam,
	Summon_Dragon,
	Summon_ButterFly,
};

struct Phase2_Boss_Skill_Info
{
	Phase2_Boss_Skill_Info()
	{

	}

	Phase2_Boss_Skill_Info(float _SkillCooldown, LucidState _SkillState)
		: SkillCooldownValue(_SkillCooldown), SkillCooldown(_SkillCooldown), SkillState(_SkillState)
	{

	}

	float SkillCooldownValue = 0.0f;
	float SkillCooldown = 0.0f;
	LucidState SkillState = LucidState::Idle;
};

class Boss_Lucid_Phase2 : public BaseBossActor
{
	friend Lucid_Phase2_GUI;
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
	void Release() override;
private:
	bool IsCoolDownUpdate = true;
	int CurLocationIndex = 0;
	float MoveSpeed = Default_MoveSpeed;
	float MoveDelay = 1.5f;
	float4 MoveVector = float4::ZERO;
	std::vector<int> LocationNumber;
	std::vector<float4> MoveLocation;

	ActorDir Dir = ActorDir::Right;
	LucidState State = LucidState::Idle;
	std::vector<Phase2_Boss_Skill_Info> SkillInfo;
	GameEngineSoundPlayer BossPlayer;
	std::shared_ptr<Lucid_Phase2_GUI> BossGui = nullptr;
	///// State
	// Start
	void IdleStart();
	void DeathStart();
	void PhantasmalWindStart();
	void LaserStart();
	void BodySlamStart();
	void Summon_DragonStart();
	void Summon_ButterFlyStart();
	//
	// Update
	void IdleUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	void PhantasmalWindUpdate(float _Delta);
	void LaserUpdate(float _Delta);
	void BodySlamUpdate(float _Delta);
	void Summon_DragonUpdate(float _Delta);
	void Summon_ButterFlyUpdate(float _Delta);
	// 
	// End
	void IdleEnd();
	void DeathEnd();
	void PhantasmalWindEnd();
	void LaserEnd();
	void BodySlamEnd();
	void Summon_DragonEnd();
	void Summon_ButterFlyEnd();
	// 
	/////
};

