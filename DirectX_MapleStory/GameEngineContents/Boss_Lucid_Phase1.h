#pragma once
#include "BaseBossActor.h"

class Boss_Lucid_Phase1 : public BaseBossActor
{
public:
	// constructer destructer
	Boss_Lucid_Phase1();
	~Boss_Lucid_Phase1();

	// delete function
	Boss_Lucid_Phase1(const Boss_Lucid_Phase1& _Ohter) = delete;
	Boss_Lucid_Phase1(Boss_Lucid_Phase1&& _Ohter) noexcept = delete;
	Boss_Lucid_Phase1& operator=(const Boss_Lucid_Phase1& _Other) = delete;
	Boss_Lucid_Phase1& operator=(Boss_Lucid_Phase1&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> FlowerRenderer = nullptr;
};

