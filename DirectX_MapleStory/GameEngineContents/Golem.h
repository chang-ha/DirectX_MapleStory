#pragma once

#include "ContentActor.h"

enum class GolemState
{
	Null,
	Ready,
	Revive,
	Idle,
	Attack,
	Death,
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

	/// <summary>
	/// Init 1 or 2
	/// </summary>
	/// <param name="_PhaseNumber"> == CurPhaseNumber</param>
	void Init(int _PhaseNumber);
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

	GolemState State = GolemState::Ready;
	std::shared_ptr<GameEngineCollision> GolemCollision = nullptr;
private:
};

