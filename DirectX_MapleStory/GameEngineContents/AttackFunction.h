#pragma once

struct OneHitAttackFunction
{
	std::set<GameEngineObject*> CollisionActor;

	void AttackUpdate(std::shared_ptr<GameEngineCollision> _AttackCollision, CollisionOrder _Order, std::string_view _HitAniName, int _HitCount = 1, int _Damage = -1, bool _RandomPivot = true, PivotType _PivotType = PivotType::Bottom);
};

struct HitTimeAttackFunction
{
	std::map<std::shared_ptr<GameEngineCollision>, float> CollisionTime;

	void CollisionTimeUpdate(float _Delta);
	void AttackUpdate(std::shared_ptr<GameEngineCollision> _AttackCollision, CollisionOrder _Order, std::string_view _HitAniName, float _Hit_Time = 0.2f, int _HitCount = 1, int _Damage = -1, bool _RandomPivot = true, PivotType _PivotType = PivotType::Bottom);
};