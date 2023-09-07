#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ContentSkill : public GameEngineActor
{ 
public:
	// constructer destructer
	ContentSkill();
	~ContentSkill();

	// delete function
	ContentSkill(const ContentSkill& _Ohter) = delete;
	ContentSkill(ContentSkill&& _Ohter) noexcept = delete;
	ContentSkill& operator=(const ContentSkill& _Other) = delete;
	ContentSkill& operator=(ContentSkill&& _Other) noexcept = delete;

protected:
	std::shared_ptr<GameEngineSpriteRenderer> SkillRenderer = nullptr;

private:

};

