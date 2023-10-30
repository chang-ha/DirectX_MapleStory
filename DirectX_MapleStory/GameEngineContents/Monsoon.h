#pragma once
#include "ContentSkill.h"

class Monsoon : public ContentSkill
{
public:
	// constructer destructer
	Monsoon();
	~Monsoon();

	// delete function
	Monsoon(const Monsoon& _Other) = delete;
	Monsoon(Monsoon&& _Other) noexcept = delete;
	Monsoon& operator=(const Monsoon& _Other) = delete;
	Monsoon& operator=(Monsoon&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void CollisionEvent(std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup);


private:
	std::shared_ptr<GameEngineSpriteRenderer> SceneRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	std::set<GameEngineObject*> CollisionActor;
};

