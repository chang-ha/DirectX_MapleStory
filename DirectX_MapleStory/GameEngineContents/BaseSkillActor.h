#pragma once
#include "ContentActor.h"
#include "AttackFunction.h"

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
	float Speed = 0.0f;
	float LiveTime = 10.0f;
	float4 Scale = float4::ZERO;
	float4 CurMapScale = float4::ZERO;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	HitTimeAttackFunction AttackFunction;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	virtual void MoveUpdate(float _Delta);
	void BlockOutMap();

	virtual void SetDir(ActorDir _Dir)
	{
		Dir = _Dir;
		switch (Dir)
		{
		case ActorDir::Right:
			MainSpriteRenderer->LeftFlip();
			break;
		case ActorDir::Left:
			MainSpriteRenderer->RightFlip();
			break;
		case ActorDir::Null:
		default:
			MsgBoxAssert("존재하지 않는 방향입니다.");
			break;
		}
	}
private:

};

