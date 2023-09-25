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

}

void BaseBossActor::Start()
{
	BossRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	BossCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
}

void BaseBossActor::Update(float _Delta)
{

}