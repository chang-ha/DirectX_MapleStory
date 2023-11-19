#pragma once
#include "ContentActor.h"
#include "AttackFunction.h"

enum class MushState
{
	Null,
	Ready,
	Idle,
	Move,
	Death,
};

class MushRoom : public ContentBaseActor
{
public:
	// constructer destructer
	MushRoom();
	~MushRoom();

	// delete function
	MushRoom(const MushRoom& _Ohter) = delete;
	MushRoom(MushRoom&& _Ohter) noexcept = delete;
	MushRoom& operator=(const MushRoom& _Other) = delete;
	MushRoom& operator=(MushRoom&& _Other) noexcept = delete;

	void SetDir(ActorDir _Dir);

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void ChangeState(MushState _State);
	void StateUpdate(float _Delta);

private:
	float WaitTime = 0.5f;
	float4 MoveDir = float4::ZERO;
	ActorDir Dir = ActorDir::Null;
	MushState State = MushState::Ready;
	std::shared_ptr<GameEngineSpriteRenderer> MushRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> MushCollision = nullptr;
	std::shared_ptr<GameEngineCollision> AttackCollision = nullptr;
	HitTimeAttackFunction AttackFunction;
	GameEngineSoundPlayer MushRoomPlayer;

	void IdleStart();
	void MoveStart();
	void DeathStart();

	void IdleUpdate(float _Delta);
	void MoveUpdate(float _Delta);
};

