#pragma once
#include "ContentSkill.h"

class PhalanxCharge : public ContentSkill
{
public:
	// constructer destructer
	PhalanxCharge();
	~PhalanxCharge();

	// delete function
	PhalanxCharge(const PhalanxCharge& _Ohter) = delete;
	PhalanxCharge(PhalanxCharge&& _Ohter) noexcept = delete;
	PhalanxCharge& operator=(const PhalanxCharge& _Other) = delete;
	PhalanxCharge& operator=(PhalanxCharge&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Init() override;

private:

};

