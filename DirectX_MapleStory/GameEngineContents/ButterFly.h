#pragma once

#define Fly_Accel_MoveSpeed 100.0f
#define Fly_Default_MoveSpeed 150.0f
#define Fly_Max_MoveSpeed 250.0f

enum class ButterFlyState
{
	Ready,
	Move,
	Attack,
	Death,
};

enum class ButterFly_Phase
{
	Phase1 = 1,
	Phase2 = 2,
};

class ButterFly : public GameEngineActor
{
public:
	// constructer destructer
	ButterFly();
	~ButterFly();

	// delete function
	ButterFly(const ButterFly& _Ohter) = delete;
	ButterFly(ButterFly&& _Ohter) noexcept = delete;
	ButterFly& operator=(const ButterFly& _Other) = delete;
	ButterFly& operator=(ButterFly&& _Other) noexcept = delete;

	void Init(ButterFly_Phase _Phase)
	{
		Phase = static_cast<int>(_Phase);
		Init(Phase);
	}

	void ChangeState(ButterFlyState _State);
	void StateUpdate(float _Delta);

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	int Phase = 0;
	int CurLocationIndex = 0;
	float LiveTime = 20.0f;
	float MoveSpeed = Fly_Default_MoveSpeed;
	float4 MoveVector = float4::ZERO;
	std::vector<int> LocationNumber;
	std::vector<float4> MoveLocation;

	ActorDir Dir = ActorDir::Null;
	ButterFlyState State = ButterFlyState::Ready;
	std::shared_ptr<GameEngineSpriteRenderer> FlyRenderer = nullptr;
	GameEngineSoundPlayer ButterFlyPlayer;

	void Init(int _Phase);

	// Start
	void ReadyStart();
	void MoveStart();
	void AttackStart();
	void DeathStart();
	//
	// Update
	void ReadyUpdate(float _Delta);
	void MoveUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	// 
};

