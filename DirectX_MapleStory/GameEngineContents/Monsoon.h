#pragma once
#include "ContentSkill.h"

class Monsoon : public ContentSkill
{
public:
	// constructer destructer
	Monsoon();
	~Monsoon();

	// delete function
	Monsoon(const Monsoon& _Ohter) = delete;
	Monsoon(Monsoon&& _Ohter) noexcept = delete;
	Monsoon& operator=(const Monsoon& _Other) = delete;
	Monsoon& operator=(Monsoon&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};

