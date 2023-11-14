#pragma once
#include "ContentSkill.h"

class HowlingGale : public ContentSkill
{
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

private:

};

