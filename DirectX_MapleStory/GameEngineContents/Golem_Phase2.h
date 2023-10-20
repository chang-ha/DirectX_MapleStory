#pragma once
#include "Golem.h"

class Golem_Phase2 : public Golem
{
public:
	// constructer destructer
	Golem_Phase2();
	~Golem_Phase2();

	// delete function
	Golem_Phase2(const Golem_Phase2& _Ohter) = delete;
	Golem_Phase2(Golem_Phase2&& _Ohter) noexcept = delete;
	Golem_Phase2& operator=(const Golem_Phase2& _Other) = delete;
	Golem_Phase2& operator=(Golem_Phase2&& _Other) noexcept = delete;

	void SetSummonFootHold(int _SummonFootHold);

protected:

private:
	int SummonFootHold = -1;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
};

