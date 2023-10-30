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
	BossWarningMent = GetLevel()->CreateActor<WarningMent>(UpdateOrder::UI);
}

void BaseBossActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BaseBossActor::Start()
{
	HP = 10000;
	
	if (nullptr == BossRenderer)
	{
		BossRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BOSSMONSTER);
		BossRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::bossmonster});
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
