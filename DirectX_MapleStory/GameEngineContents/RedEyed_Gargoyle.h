#pragma once
#include "FieldMonster.h"

class RedEyed_Gargoyle : public FieldMonster
{
public:
	// constructer destructer
	RedEyed_Gargoyle();
	~RedEyed_Gargoyle();

	// delete function
	RedEyed_Gargoyle(const RedEyed_Gargoyle& _Ohter) = delete;
	RedEyed_Gargoyle(RedEyed_Gargoyle&& _Ohter) noexcept = delete;
	RedEyed_Gargoyle& operator=(const RedEyed_Gargoyle& _Other) = delete;
	RedEyed_Gargoyle& operator=(RedEyed_Gargoyle&& _Other) noexcept = delete;

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

