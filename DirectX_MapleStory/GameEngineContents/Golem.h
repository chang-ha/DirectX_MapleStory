#pragma once

#include "ContentActor.h"
#include "AttackFunction.h"

enum class GolemState
{
	Null,
	Ready,
	Revive,
	Idle,
	Attack,
	Death,
};

enum class Golem_Phase
{
	Phase1 = 1,
	Phase2 = 2
};

class Golem : public ContentActor
{
public:
	// constructer destructer
	Golem();
	~Golem();

	// delete function
	Golem(const Golem& _Ohter) = delete;
	Golem(Golem&& _Ohter) noexcept = delete;
	Golem& operator=(const Golem& _Other) = delete;
	Golem& operator=(Golem&& _Other) noexcept = delete;

	void Init(Golem_Phase _Phase)
	{
		Phase = _Phase;
		Init(static_cast<int>(_Phase));
	}
	
	void ChangeState(GolemState _State);
	void StateUpdate(float _Delta);

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	virtual void ReadyStart();
	virtual void ReviveStart();
	virtual void IdleStart();
	virtual void AttackStart();
	virtual void DeathStart();

	void ReadyUpdate(float _Delta);
	void ReviveUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void DeathUpdate(float _Delta);

	Golem_Phase Phase = Golem_Phase::Phase1;
	GolemState State = GolemState::Ready;
	std::shared_ptr<GameEngineCollision> GolemCollision = nullptr;

	void Init(int _PhaseNumber);
private:
	std::shared_ptr<GameEngineCollision> TakeDownCollision = nullptr;
	OneHitAttackFunction AttackFunction;
};

