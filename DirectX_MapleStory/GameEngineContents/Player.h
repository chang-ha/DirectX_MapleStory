#pragma once
#define IDLE_ANI_SPEED 0.5f
#define WALK_ANI_SPEED 0.1f
#define SHOOT1_ANI_SPEED 0.2f
#define ROPE_ANI_SPEED 0.2f
#define ATT_ANI_SPEED 0.3f
#define DOWN_ATT_ANI_SPEED 0.5f

#define LADDER_Y_PIVOT 3.0f

enum class PlayerState
{
	Null, // StartValue
	Idle,
	Alert,
	Walk,
	Jump,
	Down,
	Ladder,
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

	void ChangeState(PlayerState _State);
	void StateUpdate(float _Delta);

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

	void DirCheck();
	void ChasingCamera(float _Delta);
	void BlockOutMap();
	void LadderCheck();

private:
	bool IsLadder = false;
	bool DoubleJump = false;
	bool GroundJump = false;
	float Speed = 250.0f;
	float AirSpeed = 200.0f;
	float JumpAirSpeed = 30.0f;
	float CameraSpeed = 5.0f;
	float LadderPivot = 0.0f;
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
	void LadderStart();

	/// End
	void IdleEnd();
	void AlertEnd();
	void WalkEnd();
	void JumpEnd();
	void DownEnd();
	void LadderEnd();

	/// Update
	void IdleUpdate(float _Delta);
	void AlertUpdate(float _Delta);
	void WalkUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void LadderUpdate(float _Delta);
	////////////
};

