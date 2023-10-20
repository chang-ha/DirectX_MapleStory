#pragma once
// Ani Speed
#define IDLE_ANI_SPEED 0.5f
#define WALK_ANI_SPEED 0.1f
#define SHOOT1_ANI_SPEED 0.7f
#define ROPE_ANI_SPEED 0.2f
#define ATT_ANI_SPEED 0.3f
#define DOWN_ATT_ANI_SPEED 0.5f

// Pivot Value
#define LADDER_Y_PIVOT 3.0f

// Time Value
#define ALERT_TIME 5.0f

enum class PlayerState
{
	Null, // StartValue
	Idle,
	Alert,
	Walk,
	Jump,
	Down,
	Ladder,
	Attack,
	Shooting, // SongOfHeaven
	Attack2, // FairySpiral
	WindWalk, // WindWalk
	Shoot, //HowlingGale
	VortexSphere,
	MercilessWinds,
	Monsoon
};

#include "ContentActor.h"

class Player : public ContentActor
{
public:
	static Player* MainPlayer;
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	inline float4 GetPlayerScale() const
	{
		return PlayerScale;
	}

	void ChangeState(PlayerState _State);
	void StateUpdate(float _Delta);
	void Release() override;
	void SetNotGroundValue(float _Value)
	{
		NotGround = _Value;
	}

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

	void DirCheck();
	void ChasingCamera(float _Delta);
	void BlockOutMap();
	void LadderCheck();
	bool CheckGround(float4 PlusCheckPos = float4::ZERO) override;

private:
	bool IsLadder = false;
	bool IsDirCheck = true;
	bool DoubleJump = false;
	bool GroundJump = false;
	float Speed = 200.0f;
	float AirSpeed = 200.0f;
	float JumpAirSpeed = 30.0f;
	float CameraSpeed = 2.0f;
	float LadderPivot = 0.0f;
	float AlertTime = 0.0f;

	// 추후 Set으로 개선
	float SkipGround = 0.0f;
	float NotGround = 0.0f;

	float4 CurMapScale = float4::ZERO;
	float4 PlayerScale = float4::ZERO;
	PlayerState State = PlayerState::Null;

	void ChangeToIdle();
	//////////// State 
	/// Start
	void IdleStart();
	void AlertStart();
	void WalkStart();
	void JumpStart();
	void DownStart();
	void LadderStart();
	void AttackStart();
	void ShootingStart();
	void Attack2Start();
	void WindWalkStart();
	void ShootStart();
	void VortexSphereStart();
	void MercilessWindsStart();
	void MonsoonStart();

	/// End
	void IdleEnd();
	void AlertEnd();
	void WalkEnd();
	void JumpEnd();
	void DownEnd();
	void LadderEnd();
	void AttackEnd();
	void ShootingEnd();
	void Attack2End();
	void WindWalkEnd();
	void ShootEnd();
	void VortexSphereEnd();
	void MercilessWindsEnd();
	void MonsoonEnd();

	/// Update
	void IdleUpdate(float _Delta);
	void AlertUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void LadderUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void ShootingUpdate(float _Delta);
	void Attack2Update(float _Delta);
	void WindWalkUpdate(float _Delta);
	void ShootUpdate(float _Delta);
	void VortexSphereUpdate(float _Delta);
	void MercilessWindsUpdate(float _Delta);
	void MonsoonUpdate(float _Delta);
	////////////
};

