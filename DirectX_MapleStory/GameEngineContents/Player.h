#pragma once

// Ani Speed
#define IDLE_ANI_SPEED 0.5f
#define WALK_ANI_SPEED 0.1f
#define SHOOT1_ANI_SPEED 0.3f
#define ROPE_ANI_SPEED 0.2f
#define ATT_ANI_SPEED 0.3f
#define DOWN_ATT_ANI_SPEED 0.5f

// Pivot Value
#define LADDER_Y_PIVOT 3.0f

// Time Value
#define ALERT_TIME 5.0f

enum PlayerState
{
	Null = 0b0000000000000000, // StartValue
	Idle = 0b0000000000000001,
	Alert = 0b0000000000000010,
	Walk = 0b0000000000000100,
	Jump = 0b0000000000001000,
	Down = 0b0000000000010000,
	Ladder = 0b0000000000100000,
	SongOfHeaven = 0b0000000010000000,
	FairySpiral = 0b0000000100000000,
	WindWalk = 0b0000001000000000,
	HowlingGale = 0b0000010000000000,
	VortexSphere = 0b0000100000000000,
	MercilessWinds = 0b0001000000000000,
	Monsoon = 0b0010000000000000,
};

#include "ContentActor.h"

class Player : public ContentActor
{
	friend class PlayerUIManager;
public:
	static Player* MainPlayer;
	static int PlayerHP;
	static int PlayerMP;
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

	PlayerState GetState()
	{
		return State;
	}

	void StateUpdate(float _Delta);
	void Release() override;

	void SetNotGroundValue(float _Value)
	{
		NotGround.insert( _Value);
	}
	
	void PopNotGroundValue(float _Value)
	{
		NotGround.erase(_Value);
	}

	void InputObjectOff()
	{
		ChangeState(PlayerState::Idle);
		GameEngineInput::InputObjectOff(Player::MainPlayer);
		GameEngineInput::InputObjectOff(SkillManagerActor.get());
	}

	void InputObjectOn()
	{
		GameEngineInput::InputObjectOn(Player::MainPlayer);
		GameEngineInput::InputObjectOn(SkillManagerActor.get());
	}

	void PlayerCollisionOn()
	{
		HitCollision->On();
	}

	void PlayerCollisionOff()
	{
		HitCollision->Off();
	}

	void InvincibilityOn()
	{
		Invincibility = true;
		HitCollision->Off();
	}

	void InvincibilityOff()
	{
		Invincibility = false;
		HitCollision->On();
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
	bool Invincibility = false;
	bool IsLadder = false;
	bool IsDirCheck = true;
	bool IsGroundCheck = true;
	bool DoubleJump = false;
	bool GroundJump = false;
	float Speed = 200.0f;
	float AirSpeed = 200.0f;
	float JumpAirSpeed = 30.0f;
	float CameraSpeed = 2.0f;
	float LadderPivot = 0.0f;
	float AlertTime = 0.0f;

	float SkipGround = 0.0f;
	std::set<float> NotGround;

	float4 CurMapScale = float4::ZERO;
	float4 PlayerScale = float4::ZERO;
	PlayerState State = PlayerState::Null;
	std::shared_ptr<GameEngineCollision> HitCollision = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> NameRenderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> NameBGRenderer = nullptr;
	std::shared_ptr<class SkillManager> SkillManagerActor = nullptr;
	std::shared_ptr<class DamageSkinManager> DamageSkinManagerActor = nullptr;
	std::shared_ptr<class PlayerUIManager> UIManager;

	GameEngineSoundPlayer CharPlayer;

	void ChangeToIdle();
	//////////// State 
	/// Start
	void IdleStart();
	void AlertStart();
	void WalkStart();
	void JumpStart();
	void DownStart();
	void LadderStart();
	void SongOfHeavenStart();
	void FairySpiralStart();
	void WindWalkStart();
	void HowlingGaleStart();
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
	void SongOfHeavenEnd();
	void FairySpiralEnd();
	void WindWalkEnd();
	void HowlingGaleEnd();
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
	void SongOfHeavenUpdate(float _Delta);
	void FairySpiralUpdate(float _Delta);
	void WindWalkUpdate(float _Delta);
	void HowlingGaleUpdate(float _Delta);
	void VortexSphereUpdate(float _Delta);
	void MercilessWindsUpdate(float _Delta);
	void MonsoonUpdate(float _Delta);
	////////////
};

