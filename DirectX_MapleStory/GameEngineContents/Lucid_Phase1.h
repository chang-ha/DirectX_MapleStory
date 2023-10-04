#pragma once
#include "ContentLevel.h"

class Lucid_Phase1 : public ContentLevel
{
public:
	// constructer destructer
	Lucid_Phase1();
	~Lucid_Phase1();

	// delete function
	Lucid_Phase1(const Lucid_Phase1& _Ohter) = delete;
	Lucid_Phase1(Lucid_Phase1&& _Ohter) noexcept = delete;
	Lucid_Phase1& operator=(const Lucid_Phase1& _Other) = delete;
	Lucid_Phase1& operator=(Lucid_Phase1&& _Other) noexcept = delete;

	void CallDragon();

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;

private:
	float LaserCoolDown = 0.0f;
	std::shared_ptr<class Dragon> LeftDragon = nullptr;
	std::shared_ptr<class Dragon> RightDragon = nullptr;
};

