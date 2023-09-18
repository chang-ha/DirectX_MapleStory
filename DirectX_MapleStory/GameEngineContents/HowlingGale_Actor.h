#pragma once
#include "ContentActor.h"

enum class HowlingGaleState
{
	Ready,
	Attack,
	Death
};

class HowlingGale_Actor : public ContentActor
{
public:
	static HowlingGale_Actor* MainHowlingGale;
public:
	// constructer destructer
	HowlingGale_Actor();
	~HowlingGale_Actor();

	// delete function
	HowlingGale_Actor(const HowlingGale_Actor& _Ohter) = delete;
	HowlingGale_Actor(HowlingGale_Actor&& _Ohter) noexcept = delete;
	HowlingGale_Actor& operator=(const HowlingGale_Actor& _Other) = delete;
	HowlingGale_Actor& operator=(HowlingGale_Actor&& _Other) noexcept = delete;

	void ChangeState(HowlingGaleState _State);
	void SetScale(const float4& _Value)
	{
		Scale = _Value;
	}

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void StateUpdate(float _Delta);
	void BlockOutMap();

private:
	float Speed = 200.0f;
	float4 Scale = float4::ZERO;
	float4 CurMapScale = float4::ZERO;
	HowlingGaleState State = HowlingGaleState::Ready;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;

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

