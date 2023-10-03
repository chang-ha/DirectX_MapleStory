#pragma once
#include "ContentSkill.h"

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
	void RenderEvent(GameEngineRenderer* _Renderer);
	void CollisionEvent(std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup);

protected:
	void Start() override;
	void Update(float _Delta) override;


private:
	bool FirstUse = false;
	EventParameter SkillEvent;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
};

