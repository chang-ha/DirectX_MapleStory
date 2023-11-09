#pragma once
#include "ContentActor.h"

struct MonsterAttackFunction
{
	std::set<GameEngineObject*> CollisionActor;

	void AttackUpdate(std::shared_ptr<GameEngineCollision> _AttackCollision, std::string_view _HitAniName, int _Damage);
};


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
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> MonsterRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> MonsterCollision = nullptr;
	MonsterAttackFunction AttackFunction;
};

