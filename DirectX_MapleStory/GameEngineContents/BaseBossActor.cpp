#include "PreCompile.h"
#include "BaseBossActor.h"

BaseBossActor::BaseBossActor()
{

}

BaseBossActor::~BaseBossActor()
{

}

void BaseBossActor::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void BaseBossActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BaseBossActor::Start()
{
	if (nullptr == BossRenderer)
	{
		BossRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
		BossRenderer->AutoSpriteSizeOn();
	}

	if (nullptr == BossCollision)
	{
		BossCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	}
}

void BaseBossActor::Update(float _Delta)
{

}

void BaseBossActor::Release()
{
	if (nullptr != BossRenderer)
	{
		BossRenderer->Death();
		BossRenderer = nullptr;
	}

	if (nullptr != BossCollision)
	{
		BossCollision->Death();
		BossCollision = nullptr;
	}
}
