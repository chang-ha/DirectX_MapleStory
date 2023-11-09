#include "PreCompile.h"
#include "ContentMonster.h"
#include "HitRenderManager.h"

void MonsterAttackFunction::AttackUpdate(std::shared_ptr<GameEngineCollision> _AttackCollision, std::string_view _HitAniName, int _Damage)
{
	_AttackCollision->Collision(CollisionOrder::Player, [&](std::vector<GameEngineCollision*>& _CollisionGroup)
		{
			for (size_t i = 0; i < _CollisionGroup.size(); i++)
			{
				GameEngineCollision* _Other = _CollisionGroup[i];
				GameEngineObject* _Object = _Other->GetParentObject();
				if (true == CollisionActor.contains(_Object))
				{
					return;
				}
				HitRenderManager::MainHitRenderManager->HitPrint(_HitAniName, 1, _Object, _Damage, false);
				CollisionActor.insert(_Object);
			}
		}
	);
}

ContentMonster::ContentMonster()
{

}

ContentMonster::~ContentMonster()
{

}

void ContentMonster::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void ContentMonster::Start()
{
	MonsterRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	MonsterRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::monster});
	MonsterRenderer->AutoSpriteSizeOn();

	// Collision
	MonsterCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
}

void ContentMonster::Update(float _Delta)
{

}

void ContentMonster::Release()
{
	if (nullptr != MonsterRenderer)
	{
		MonsterRenderer->Death();
		MonsterRenderer = nullptr;
	}

	if (nullptr != MonsterCollision)
	{
		MonsterCollision->Death();
		MonsterCollision = nullptr;
	}
}