#pragma once
#include "ContentLevel.h"

class Lucid_Phase2 : public ContentLevel
{
public:
	// constructer destructer
	Lucid_Phase2();
	~Lucid_Phase2();

	// delete function
	Lucid_Phase2(const Lucid_Phase2& _Ohter) = delete;
	Lucid_Phase2(Lucid_Phase2&& _Ohter) noexcept = delete;
	Lucid_Phase2& operator=(const Lucid_Phase2& _Other) = delete;
	Lucid_Phase2& operator=(Lucid_Phase2&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class ContentBackGround> Back = nullptr;
	std::shared_ptr<class Boss_Lucid_Phase1> Boss = nullptr;
	std::shared_ptr<class Player> CurPlayer = nullptr;
};

