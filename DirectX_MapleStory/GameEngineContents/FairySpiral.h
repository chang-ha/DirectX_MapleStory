#pragma once
#include "ContentSkill.h"
#include "AttackFunction.h"

// Ό³Έν :
class FairySpiral : public ContentSkill
{
public:
	// constrcuter destructer
	FairySpiral();
	~FairySpiral();

	// delete Function
	FairySpiral(const FairySpiral& _Other) = delete;
	FairySpiral(FairySpiral&& _Other) noexcept = delete;
	FairySpiral& operator=(const FairySpiral& _Other) = delete;
	FairySpiral& operator=(FairySpiral&& _Other) noexcept = delete;

	void Init() override;
	void UseSkill() override;
	void EndSkill() override;
	void CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	std::set<GameEngineObject*> CollisionActor;
	OneHitAttackFunction AttackFunction;
};

