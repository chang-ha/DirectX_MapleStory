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

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

private:
	float Delay = 0.0f;
	float Speed = 150.0f;
	ActorDir Dir = ActorDir::Right;
	DragonState State = DragonState::Idle;
	std::shared_ptr<GameEngineSpriteRenderer> DragonRenderer = nullptr;
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> BreathRenderers;

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

