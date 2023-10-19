#pragma once

enum class DragonState
{
	Idle,
	Down,
	Up,
	Breath
};

class Dragon : public GameEngineActor
{
public:
	// constructer destructer
	Dragon();
	~Dragon();

	// delete function
	Dragon(const Dragon& _Ohter) = delete;
	Dragon(Dragon&& _Ohter) noexcept = delete;
	Dragon& operator=(const Dragon& _Other) = delete;
	Dragon& operator=(Dragon&& _Other) noexcept = delete;

	void ChangeState(DragonState _State);
	void StateUpdate(float _Delta);
	void SetDir(ActorDir _Dir);

	void BreathOn();
	void BreathOff();
	void RightBreath();
	void LeftBreath();

	void SetBreathPos(const float4& _Pos);

	void SetDestination_YPos(float _Pos)
	{
		Destination_YPos = _Pos;
	}

	void SetBreathMinMaxPos(float _MinPos, float _MaxPos)
	{
		Breath_MoveDir = 1.0f;
		Breath_Min_Pos = _MinPos;
		Breath_Max_Pos = _MaxPos;
	}

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	float Delay = 0.0f;
	float Speed = 150.0f;
	float Destination_YPos = -750.0f;

	bool IsMoveBreath = false;
	float BreathSpeed = 200.0f;
	float Breath_MoveDir = 0.0f;
	float Breath_Max_Pos = 0.0f;
	float Breath_Min_Pos = 0.0f;

	ActorDir Dir = ActorDir::Right;
	DragonState State = DragonState::Idle;
	std::shared_ptr<GameEngineSpriteRenderer> DragonRenderer = nullptr;
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> BreathRenderers;
	std::shared_ptr<GameEngineCollision> BreathCollision = nullptr;

	///// State
	// Start
	void IdleStart();
	void DownStart();
	void UpStart();
	void BreathStart();
	//
	// Update
	void IdleUpdate(float _Delta);
	void DownUpdate(float _Delta);
	void UpUpdate(float _Delta);
	void BreathUpdate(float _Delta);
	// 
	// End
	void IdleEnd();
	void DownEnd();
	void UpEnd();
	void BreathEnd();
	// 
	///// 
};

