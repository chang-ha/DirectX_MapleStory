#pragma once
#include "ContentActor.h"
#include "AttackFunction.h"

#define ATTACK_COOLDOWN 1.5f

enum class FieldMonsterState
{
	Ready,
	Idle,
	Move,
	Attack,
	Death
};

class FieldMonster : public ContentActor
{
public:
	// constructer destructer
	FieldMonster();
	~FieldMonster();

	// delete function
	FieldMonster(const FieldMonster& _Ohter) = delete;
	FieldMonster(FieldMonster&& _Ohter) noexcept = delete;
	FieldMonster& operator=(const FieldMonster& _Other) = delete;
	FieldMonster& operator=(FieldMonster&& _Other) noexcept = delete;

	void ChangeState(FieldMonsterState _State);
	void StateUpdate(float _Delta);
	void Init(std::string_view _MonsterName);

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void ChangeDir();

	float Speed = 100.0f;
	float AttackCoolDown = ATTACK_COOLDOWN;
	std::string MonsterName = "";
	ActorDir Dir = ActorDir::Null;
	FieldMonsterState State = FieldMonsterState::Ready;
	std::shared_ptr<GameEngineCollision> MonsterCollision = nullptr;
	std::shared_ptr<GameEngineCollision> DetectCollision = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;
	OneHitAttackFunction AttackFunction;

private:
	// Start
	virtual void ReadyStart();
	virtual void IdleStart();
	virtual void MoveStart();
	virtual void AttackStart();
	virtual void DeathStart();

	void ReadyUpdate(float _Delta);
	void IdleUpdate(float _Delta);
	void MoveUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void DeathUpdate(float _Delta);

	// End
	void ReadyEnd();
	void IdleEnd();
	void MoveEnd();
	void AttackEnd();
	void DeathEnd();
};

