#pragma once
#include "ContentSkill.h"
#include "HowlingGale_Actor.h"

class HowlingGale : public ContentSkill
{
	static float WholeCoolDown;
public:
	// constructer destructer
	HowlingGale();
	~HowlingGale();

	// delete function
	HowlingGale(const HowlingGale& _Ohter) = delete;
	HowlingGale(HowlingGale&& _Ohter) noexcept = delete;
	HowlingGale& operator=(const HowlingGale& _Other) = delete;
	HowlingGale& operator=(HowlingGale&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Init() override;
	void Release() override;

private:
	HowlingStack _SummonStack = HowlingStack::Stack1;
};

