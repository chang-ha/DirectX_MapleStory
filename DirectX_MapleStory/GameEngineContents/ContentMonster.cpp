#include "PreCompile.h"
#include "ContentMonster.h"


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