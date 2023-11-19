#pragma once
#include "FieldMonster.h"

class BlueEyed_Gargoyle : public FieldMonster
{
public:
	// constructer destructer
	BlueEyed_Gargoyle();
	~BlueEyed_Gargoyle();

	// delete function
	BlueEyed_Gargoyle(const BlueEyed_Gargoyle& _Ohter) = delete;
	BlueEyed_Gargoyle(BlueEyed_Gargoyle&& _Ohter) noexcept = delete;
	BlueEyed_Gargoyle& operator=(const BlueEyed_Gargoyle& _Other) = delete;
	BlueEyed_Gargoyle& operator=(BlueEyed_Gargoyle&& _Other) noexcept = delete;

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

