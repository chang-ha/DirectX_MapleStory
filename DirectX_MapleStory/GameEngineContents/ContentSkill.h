#pragma once

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

	virtual void Init() {}

protected:
	std::shared_ptr<GameEngineSpriteRenderer> SkillRenderer1 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> SkillRenderer2 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> SkillAfterImageRenderer = nullptr;

private:
};

