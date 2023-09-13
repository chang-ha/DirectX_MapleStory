#pragma once

enum class MonsterState
{
	Null,
	Idle,
	Hit,
	Death,
};
class ContentMonster : public GameEngineActor
{
public:
	ContentMonster();
	~ContentMonster();

	ContentMonster(const ContentMonster& _Other) = delete;
	ContentMonster(ContentMonster&& _Other) noexcept = delete;
	ContentMonster& operator=(const ContentMonster& _Other) = delete;
	ContentMonster& operator=(ContentMonster&& _Other) noexcept = delete;

	MonsterState GetState()
	{
		return State;
	}

	void ChangeState(MonsterState _State);
	void StateUpdate(float _Delta);

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

	void CollisionEnter(GameEngineCollision* _this, GameEngineCollision* _Other);
private:
	float4 MonsterScale = float4::ZERO;
	MonsterState State = MonsterState::Null;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> MainCollision = nullptr;

	//TestCode
	EventParameter MonsterEvent;

	//////////// State 
	/// Start
	void IdleStart();
	void HitStart();
	void DeathStart();

	/// End
	void IdleEnd();
	void HitEnd();
	void DeathEnd();

	/// Update
	void IdleUpdate(float _Delta);
	void HitUpdate(float _Delta);
	void DeathUpdate(float _Delta);
	////////////
};

