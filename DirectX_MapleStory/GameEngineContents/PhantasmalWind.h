#pragma once
#include "ContentMonster.h"

class PhantasmalWind : public GameEngineActor
{
public:
	static bool AllAngleValue;
	// constructer destructer
	PhantasmalWind();
	~PhantasmalWind();

	// delete function
	PhantasmalWind(const PhantasmalWind& _Ohter) = delete;
	PhantasmalWind(PhantasmalWind&& _Ohter) noexcept = delete;
	PhantasmalWind& operator=(const PhantasmalWind& _Other) = delete;
	PhantasmalWind& operator=(PhantasmalWind&& _Other) noexcept = delete;

	void SetSpeed(float _Speed)
	{
		Speed = _Speed;
	}

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	float LiveTime = 30.0f;
	float DirAngle = 0.0f;
	float Speed = 50.0f;
	float4 MoveVector = float4::ZERO;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> PhantasmaCollision = nullptr;
	MonsterAttackFunction AttackFunction;
};

