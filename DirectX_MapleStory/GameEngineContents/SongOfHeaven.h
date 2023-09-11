#pragma once
#include "ContentSkill.h"

class SongOfHeaven : public ContentSkill
{
public:
	// constructer destructer
	SongOfHeaven();
	~SongOfHeaven();

	// delete function
	SongOfHeaven(const SongOfHeaven& _Ohter) = delete;
	SongOfHeaven(SongOfHeaven&& _Ohter) noexcept = delete;
	SongOfHeaven& operator=(const SongOfHeaven& _Other) = delete;
	SongOfHeaven& operator=(SongOfHeaven&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float ShootDps = 0.12f;
	float4 Pivot2 = float4::ZERO;
};

