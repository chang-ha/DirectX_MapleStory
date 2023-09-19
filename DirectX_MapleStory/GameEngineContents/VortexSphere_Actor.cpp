#include "PreCompile.h"
#include "VortexSphere_Actor.h"

VortexSphere_Actor::VortexSphere_Actor()
{

}

VortexSphere_Actor::~VortexSphere_Actor()
{

}

void VortexSphere_Actor::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseSkillActor::LevelStart(_PrevLevel);
}

void VortexSphere_Actor::LevelEnd(GameEngineLevel* _NextLevel)
{
	BaseSkillActor::LevelEnd(_NextLevel);
}

void VortexSphere_Actor::Start()
{
	BaseSkillActor::Start();
	IsBlockOut = false;

	MainSpriteRenderer->CreateAnimation("Attack", "VortexSphere_Actor", 0.09f);
	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("VortexSphere_Actor");
	Scale = Sprite->GetSpriteData(0).GetScale();

	SkillCollision->Transform.SetLocalScale(Scale);
}

void VortexSphere_Actor::Update(float _Delta)
{
	BaseSkillActor::Update(_Delta);
}

void VortexSphere_Actor::MoveUpdate(float _Delta)
{
}

