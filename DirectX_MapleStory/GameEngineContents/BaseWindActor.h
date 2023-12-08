#pragma once

enum class WindState
{
	Ready,
	Attack,
	Hit,
	Death
};

class BaseWindActor : public GameEngineActor
{
public:
	static bool IsCreateWind;
	// constructer destructer
	BaseWindActor();
	~BaseWindActor();

	// delete function
	BaseWindActor(const BaseWindActor& _Ohter) = delete;
	BaseWindActor(BaseWindActor&& _Ohter) noexcept = delete;
	BaseWindActor& operator=(const BaseWindActor& _Other) = delete;
	BaseWindActor& operator=(BaseWindActor&& _Other) noexcept = delete;

	static void CreateTriflingWind();

	void ChangeState(WindState _State);
	void StateUpdate(float _Delta);

protected:
	std::string WindName = "";
	float LiveTime = 5.0f;
	float DirAngle = 0.0f;
	float Speed = 600.0f;
	float RotationSpeed = 0.0f;
	WindState State = WindState::Ready;
	float4 MoveVector = float4::ZERO;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<GameEngineCollision> DetectCollision;
	std::shared_ptr<GameEngineCollision> HitCollision;
	GameEngineSoundPlayer WindPlayer;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void Init(std::string_view _WindName);

	virtual void ReadyStart();
	virtual void AttackStart();
	virtual void HitStart();
	virtual void DeathStart();

	void ReadyUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void HitUpdate(float _Delta);
	virtual void DeathUpdate(float _Delta);

private:
};

