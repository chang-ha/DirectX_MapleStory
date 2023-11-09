#include "PreCompile.h"
#include "AttackFunction.h"
#include "HitRenderManager.h"

void OneHitAttackFunction::AttackUpdate(std::shared_ptr<GameEngineCollision> _AttackCollision, 
	CollisionOrder _Order, 
	std::string_view _HitAniName, 
	int _HitCount /*= 1*/, int _Damage /*= -1*/, bool _RandomPivot /*= true*/, PivotType _PivotType /*= PivotType::Bottom*/)
{
	_AttackCollision->Collision(_Order, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			for (size_t i = 0; i < _CollisionGroup.size(); i++)
			{
				GameEngineCollision* _Other = _CollisionGroup[i];
				GameEngineObject* _Object = _Other->GetParentObject();
				if (true == CollisionActor.contains(_Object))
				{
					return;
				}
				HitRenderManager::MainHitRenderManager->HitPrint(_HitAniName, _HitCount, _Object, _Damage, _RandomPivot, _PivotType);
				CollisionActor.insert(_Object);
			}
		}
	);
}

void HitTimeAttackFunction::CollisionTimeUpdate(float _Delta)
{
	for (std::pair<const std::shared_ptr<GameEngineCollision>, float>& _Pair : CollisionTime)
	{
		_Pair.second -= _Delta;
	}
}

void HitTimeAttackFunction::AttackUpdate(std::shared_ptr<GameEngineCollision> _AttackCollision, 
	CollisionOrder _Order, 
	std::string_view _HitAniName, 
	float _Hit_Time /*= 0.2f*/, int _HitCount /*= 1*/, int _Damage /*= -1*/, bool _RandomPivot /*= true*/, PivotType _PivotType /*= PivotType::Bottom*/)
{
	_AttackCollision->Collision(_Order, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			for (size_t i = 0; i < _CollisionGroup.size(); i++)
			{
				std::shared_ptr<GameEngineCollision> _Other = std::dynamic_pointer_cast<GameEngineCollision>(_CollisionGroup[i]->shared_from_this());
				if (false == CollisionTime.contains(_Other))
				{
					CollisionTime[_Other] = 0.0f;
				}

				if (0.0f >= CollisionTime[_Other])
				{
					HitRenderManager::MainHitRenderManager->HitPrint(_HitAniName, _HitCount, _Other->GetParentObject(), _Damage, _RandomPivot, _PivotType);
					CollisionTime[_Other] = _Hit_Time;
				}
			}
		}
	);
}
