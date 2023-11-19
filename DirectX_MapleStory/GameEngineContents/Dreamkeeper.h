#pragma once
#include "FieldMonster.h"

class Dreamkeeper : public FieldMonster
{
public:
	// constructer destructer
	Dreamkeeper();
	~Dreamkeeper();

	// delete function
	Dreamkeeper(const Dreamkeeper& _Ohter) = delete;
	Dreamkeeper(Dreamkeeper&& _Ohter) noexcept = delete;
	Dreamkeeper& operator=(const Dreamkeeper& _Other) = delete;
	Dreamkeeper& operator=(Dreamkeeper&& _Other) noexcept = delete;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	void ReadyStart() override;
	void IdleStart() override;
	void MoveStart() override;
	void AttackStart() override;
	void DeathStart() override;
};

