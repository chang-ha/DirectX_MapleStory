#include "PreCompile.h"
#include "AttackFunction.h"
#include "HitRenderManager.h"

void OneHitAttackFunction::AttackUpdate(std::shared_ptr<GameEngineCollision> _AttackCollision, CollisionOrder _Order, std::string_view _HitAniName, int _HitCount, int _Damage, bool _RandomPivot)
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
				HitRenderManager::MainHitRenderManager->HitPrint(_HitAniName, _HitCount, _Object, _Damage, _RandomPivot);
				CollisionActor.insert(_Object);
			}
		}
	);
}