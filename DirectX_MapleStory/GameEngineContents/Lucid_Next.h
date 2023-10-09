#pragma once
#include "ContentLevel.h"

class Lucid_Next : public ContentLevel
{
public:
	// constructer destructer
	Lucid_Next();
	~Lucid_Next();

	// delete function
	Lucid_Next(const Lucid_Next& _Ohter) = delete;
	Lucid_Next(Lucid_Next&& _Ohter) noexcept = delete;
	Lucid_Next& operator=(const Lucid_Next& _Other) = delete;
	Lucid_Next& operator=(Lucid_Next&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class ContentBackGround> Back = nullptr;
	std::shared_ptr<class RenderActor> Clock = nullptr;
};

