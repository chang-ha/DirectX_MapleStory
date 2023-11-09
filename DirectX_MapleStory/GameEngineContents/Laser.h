#pragma once
#include "AttackFunction.h"

class Laser : public GameEngineActor
{
public:
	// constructer destructer
	Laser();
	~Laser();

	// delete function
	Laser(const Laser& _Ohter) = delete;
	Laser(Laser&& _Ohter) noexcept = delete;
	Laser& operator=(const Laser& _Other) = delete;
	Laser& operator=(Laser&& _Other) noexcept = delete;

	void Init(std::string_view _LaserName, int _ReadyEndIndex = 12, float _AniSpeed = 0.09f);
	void SetAngle(float _Angle);
	void SetColScale(const float4& _Scale);

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> LaserRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> LaserCollision = nullptr;
	OneHitAttackFunction AttackFunction;
};

