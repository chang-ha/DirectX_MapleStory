#pragma once
#include "ContentLevel.h"

class Lachlen : public ContentLevel
{
public:
	// constructer destructer
	Lachlen();
	~Lachlen();

	// delete function
	Lachlen(const Lachlen& _Ohter) = delete;
	Lachlen(Lachlen&& _Ohter) noexcept = delete;
	Lachlen& operator=(const Lachlen& _Other) = delete;
	Lachlen& operator=(Lachlen&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<class ContentBackGround> Back = nullptr;
	std::shared_ptr<class Player> CurPlayer = nullptr;
	std::shared_ptr<class SkillManager> SkillManagerActor = nullptr;
	std::vector<std::shared_ptr<FlowObject>> MapObjects;
};

