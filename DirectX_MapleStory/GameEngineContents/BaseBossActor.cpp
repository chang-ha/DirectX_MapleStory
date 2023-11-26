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
	if (nullptr == BossWarningMent)
	{
		BossWarningMent = GetLevel()->CreateActor<WarningMent>(UpdateOrder::UI);
	}
}

void BaseBossActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	ThreeQuarters = false;
	TwoQuarters = false;
	OneQuarters = false;
	Death();
}

void BaseBossActor::Start()
{
	HP = Boss_MAX_HP;
	
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
	if (false == ThreeQuarters && Boss_MAX_HP * 0.75f > HP)
	{
		BossWarningMent->SetWarningMent("루시드가 힘을 이끌어내고있습니다!");
		ThreeQuarters = true;
	}

	if (false == TwoQuarters && Boss_MAX_HP * 0.5f > HP)
	{
		BossWarningMent->SetWarningMent("루시드가 더 강한 힘을 발휘할 겁니다!");
		TwoQuarters = true;
	}

	if (false == OneQuarters && Boss_MAX_HP * 0.25f > HP)
	{
		BossWarningMent->SetWarningMent("루시드가 분노한 것 같습니다!");
		OneQuarters = true;
	}
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

	if (nullptr != BossWarningMent)
	{
		BossWarningMent = nullptr;
	}
}
