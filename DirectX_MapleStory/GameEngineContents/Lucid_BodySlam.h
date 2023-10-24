#pragma once

class BodySlamData
{
	friend class Lucid_BodySlam;
public:
	BodySlamData(float _PlusMoveSpeed, float4 _DestinationPos)
		: PlusMoveSpeed(_PlusMoveSpeed), DestinationPos(_DestinationPos)
	{

	}

	BodySlamData()
	{

	}
private:
	float PlusMoveSpeed = 0.0f;
	float4 DestinationPos = float4::ZERO;

};

enum class BodySlamState
{
	Ready,
	Attack,
	Death,
};

class Lucid_BodySlam : public GameEngineActor
{
public:
	// constructer destructer
	Lucid_BodySlam();
	~Lucid_BodySlam();

	// delete function
	Lucid_BodySlam(const Lucid_BodySlam& _Ohter) = delete;
	Lucid_BodySlam(Lucid_BodySlam&& _Ohter) noexcept = delete;
	Lucid_BodySlam& operator=(const Lucid_BodySlam& _Other) = delete;
	Lucid_BodySlam& operator=(Lucid_BodySlam&& _Other) noexcept = delete;

protected:

private:
	ActorDir Dir = ActorDir::Null;
	BodySlamState State = BodySlamState::Ready;
	float DelayTime = 1.0f;

	int CurLocationIndex = 0;
	float BaseSpeed = 25.0f;
	float4 MoveVector = float4::ZERO;

	std::vector<BodySlamData> MoveLocation;
	std::shared_ptr<GameEngineSpriteRenderer> BodySlamRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BodySlamCollision = nullptr;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void ChangeState(BodySlamState _State);
	void StateUpdate(float _Delta);

	void ReadyStart();
	void AttackStart();
	void DeathStart();

	void ReadyUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void DeathUpdate(float _Delta);
};

