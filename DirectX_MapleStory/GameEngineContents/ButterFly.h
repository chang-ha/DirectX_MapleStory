#pragma once

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
		Init(static_cast<int>(_Phase));
	}

	void ChangeState(ButterFlyState _State);
	void StateUpdate(float _Delta);

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	ActorDir Dir = ActorDir::Null;
	ButterFlyState State = ButterFlyState::Ready;
	std::shared_ptr<GameEngineSpriteRenderer> FlyRenderer = nullptr;

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

