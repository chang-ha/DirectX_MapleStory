#pragma once
#include "ContentLevel.h"

class Lucid_Enter : public ContentLevel
{
public:
	// constructer destructer
	Lucid_Enter();
	~Lucid_Enter();

	// delete function
	Lucid_Enter(const Lucid_Enter& _Ohter) = delete;
	Lucid_Enter(Lucid_Enter&& _Ohter) noexcept = delete;
	Lucid_Enter& operator=(const Lucid_Enter& _Other) = delete;
	Lucid_Enter& operator=(Lucid_Enter&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class CutsceneActor> _CutsceneActor = nullptr;
};

