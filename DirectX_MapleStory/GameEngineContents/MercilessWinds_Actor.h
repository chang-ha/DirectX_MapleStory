#pragma once
#include "BaseWindActor.h"

class MercilessWinds_Actor : public BaseWindActor
{
public:
	// constructer destructer
	MercilessWinds_Actor();
	~MercilessWinds_Actor();

	// delete function
	MercilessWinds_Actor(const MercilessWinds_Actor& _Ohter) = delete;
	MercilessWinds_Actor(MercilessWinds_Actor&& _Ohter) noexcept = delete;
	MercilessWinds_Actor& operator=(const MercilessWinds_Actor& _Other) = delete;
	MercilessWinds_Actor& operator=(MercilessWinds_Actor&& _Other) noexcept = delete;

protected:
	void ReadyStart() override;
	void AttackStart() override;
	void HitStart() override;
	void DeathStart() override;

	void DeathUpdate(float _Delta) override;

	void Start() override;
private:
	float DieStartTime = 0.0f;
};

