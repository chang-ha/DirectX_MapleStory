#pragma once

struct OneHitAttackFunction
{
	std::set<GameEngineObject*> CollisionActor;

	void AttackUpdate(std::shared_ptr<GameEngineCollision> _AttackCollision, CollisionOrder _Order, std::string_view _HitAniName, int _HitCount = 1, int _Damage = -1, bool _RandomPivot = true);
};

