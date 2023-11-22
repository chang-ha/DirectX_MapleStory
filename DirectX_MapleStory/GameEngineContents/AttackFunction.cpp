#include "PreCompile.h"
#include "AttackFunction.h"
#include "HitRenderManager.h"
#include "ContentActor.h"
#include "MultiKillManager.h"

void OneHitAttackFunction::AttackUpdate(std::shared_ptr<GameEngineCollision> _AttackCollision, 
	CollisionOrder _Order, 
	std::string_view _HitAniName, 
	int _HitCount /*= 1*/, int _Damage /*= -1*/, bool _RandomPivot /*= true*/, PivotType _PivotType /*= PivotType::Bottom*/)
{
	std::set<std::shared_ptr<GameEngineObject>>::iterator StartIter = CollisionActor.begin();
	std::set<std::shared_ptr<GameEngineObject>>::iterator EndIter = CollisionActor.end();

	for (; StartIter != EndIter;)
	{
		if (false == (*StartIter)->IsDeath())
		{
			++StartIter;
			continue;
		}

		StartIter = CollisionActor.erase(StartIter);
	}

	_AttackCollision->Collision(_Order, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			int KillCount = 0;
			for (size_t i = 0; i < _CollisionGroup.size(); i++)
			{
				GameEngineCollision* _Other = _CollisionGroup[i];
				std::shared_ptr<GameEngineObject> _Object = _Other->GetParentObject()->shared_from_this();
				if (true == CollisionActor.contains(_Object))
				{
					continue;
				}
				HitRenderManager::MainHitRenderManager->HitPrint(_HitAniName, _HitCount, _Object.get(), _Damage, _RandomPivot, _PivotType);
				CollisionActor.insert(_Object);

				std::shared_ptr<ContentBaseActor> _Actor = _Object->GetDynamic_Cast_This<ContentBaseActor>();
				if (nullptr == _Actor)
				{
					continue;
				}

				if (0 >= _Actor->GetHP())
				{
					++KillCount;
				}
			}
			MultiKillManager::MultiKillPrint(KillCount);
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
	std::map<std::shared_ptr<GameEngineCollision>, float>::iterator StartIter = CollisionTime.begin();
	std::map<std::shared_ptr<GameEngineCollision>, float>::iterator EndIter = CollisionTime.end();

	for (; StartIter != EndIter;)
	{
		if (false == (*StartIter).first->IsDeath())
		{
			++StartIter;
			continue;
		}

		StartIter = CollisionTime.erase(StartIter);
	}

	_AttackCollision->Collision(_Order, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			int KillCount = 0;
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

				std::shared_ptr<GameEngineObject> _Object = _Other->GetParentObject()->shared_from_this();
				std::shared_ptr<ContentBaseActor> _Actor = _Object->GetDynamic_Cast_This<ContentBaseActor>();
				if (nullptr == _Actor)
				{
					continue;
				}

				if (0 >= _Actor->GetHP())
				{
					++KillCount;
				}
			}
			MultiKillManager::MultiKillPrint(KillCount);
		}
	);
}
