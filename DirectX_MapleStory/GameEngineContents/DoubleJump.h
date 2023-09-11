#pragma once
#include "ContentSkill.h"

class DoubleJump : public ContentSkill
{
public:
	// constructer destructer
	DoubleJump();
	~DoubleJump();

	// delete function
	DoubleJump(const DoubleJump& _Ohter) = delete;
	DoubleJump(DoubleJump&& _Ohter) noexcept = delete;
	DoubleJump& operator=(const DoubleJump& _Other) = delete;
	DoubleJump& operator=(DoubleJump&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};

