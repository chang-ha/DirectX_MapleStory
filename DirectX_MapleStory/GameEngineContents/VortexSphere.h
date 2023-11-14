#pragma once
#include "ContentSkill.h"

class VortexSphere : public ContentSkill
{
public:
	// constructer destructer
	VortexSphere();
	~VortexSphere();

	// delete function
	VortexSphere(const VortexSphere& _Ohter) = delete;
	VortexSphere(VortexSphere&& _Ohter) noexcept = delete;
	VortexSphere& operator=(const VortexSphere& _Other) = delete;
	VortexSphere& operator=(VortexSphere&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Init() override;

private:

};