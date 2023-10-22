#pragma once

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
	BodySlamState State = BodySlamState::Ready;
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

	void ReadyEnd();
	void AttackEnd();
	void DeathEnd();

	void ReadyUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void DeathUpdate(float _Delta);
};

