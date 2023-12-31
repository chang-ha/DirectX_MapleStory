#pragma once
#include "ContentActor.h"
#include "AttackFunction.h"

class ContentMonster : public ContentBaseActor
{
public:
	ContentMonster();
	~ContentMonster();

	ContentMonster(const ContentMonster& _Other) = delete;
	ContentMonster(ContentMonster&& _Other) noexcept = delete;
	ContentMonster& operator=(const ContentMonster& _Other) = delete;
	ContentMonster& operator=(ContentMonster&& _Other) noexcept = delete;

protected:
	std::shared_ptr<GameEngineSpriteRenderer> MonsterRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> MonsterCollision = nullptr;
	OneHitAttackFunction AttackFunction;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
};

