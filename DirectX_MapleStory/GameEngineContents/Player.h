#pragma once
#define IDLE_ANI_SPEED 0.5f
#define WALK_ANI_SPEED 0.1f
#define SHOOT1_ANI_SPEED 0.2f
#define ROPE_ANI_SPEED 0.2f
#define ATT_ANI_SPEED 0.3f
#define DOWN_ATT_ANI_SPEED 0.5f

enum class PlayerState
{
	Null, // StartValue
	Idle,
	Alert,
	Walk,
	Jump,
	Down,
};

#include "ContentActor.h"

class Player : public ContentActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void ChangeState(PlayerState _State);
	void StateUpdate(float _Delta);
	void CheckGround();

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void DirCheck();
	void ChasingCamera(float _Delta);

private:
	bool IsGround = true;
	bool DoubleJump = false;
	bool GroundJump = false;
	float Speed = 250.0f;
	float AirSpeed = 200.0f;
	float JumpAirSpeed = 30.0f;
	float CameraSpeed = 5.0f;
	float4 CurMapScale = float4::ZERO;
	float4 PlayerScale = float4::ZERO;
	PlayerState State = PlayerState::Null;

	//////////// State 
	/// Start
	void IdleStart();
	void AlertStart();
	void WalkStart();
	void JumpStart();
	void DownStart();

	/// Update
	void IdleUpdate(float _Delta);
	void AlertUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void DownUpdate(float _Delta);
	////////////
};

