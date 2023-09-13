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
	void Event(GameEngineRenderer* _Renderer);

protected:
	void Start() override;
	void Update(float _Delta) override;


private:
	float4 SkillScale = float4::ZERO;
	EventParameter SkillEvent;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
};

