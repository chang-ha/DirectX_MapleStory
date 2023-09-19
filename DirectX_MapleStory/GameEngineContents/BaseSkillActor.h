#pragma once
#include "ContentActor.h"

#define HIT_TIME 0.5f

class BaseSkillActor : public ContentActor
{
public:
	// constructer destructer
	BaseSkillActor();
	~BaseSkillActor();

	// delete function
	BaseSkillActor(const BaseSkillActor& _Ohter) = delete;
	BaseSkillActor(BaseSkillActor&& _Ohter) noexcept = delete;
	BaseSkillActor& operator=(const BaseSkillActor& _Other) = delete;
	BaseSkillActor& operator=(BaseSkillActor&& _Other) noexcept = delete;

protected:
	bool IsUpdate = true;
	bool IsBlockOut = true;
	float Speed = 200.0f;
	float LiveTime = 10.0f;
	float4 Scale = float4::ZERO;
	float4 CurMapScale = float4::ZERO;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	std::map<std::shared_ptr<GameEngineCollision>, float> CollisionTime;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	virtual void MoveUpdate(float _Delta);
	void BlockOutMap();
	void CollisionTimeUpdate(float _Delta);

	inline void SetDir(ActorDir _Dir)
	{
		Dir = _Dir;
	}
private:

};

