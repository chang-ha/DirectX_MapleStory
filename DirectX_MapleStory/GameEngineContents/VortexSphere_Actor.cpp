#include "PreCompile.h"
#include "VortexSphere_Actor.h"
#include "HitRenderManager.h"
#include "BaseWindActor.h"

#define SPEED 150.0f

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
	WallCheckOff();
	GravityOff();
	IsBlockOut = false;
	Speed = SPEED;
	LiveTime = 20.0f;

	MainSpriteRenderer->CreateAnimation("Attack", "VortexSphere_Actor", 0.07f);
	MainSpriteRenderer->ChangeAnimation("Attack");
	MainSpriteRenderer->AutoSpriteSizeOn();

	Scale = { 300, 300 };
	SkillCollision->SetCollisionType(ColType::SPHERE2D);
	SkillCollision->Transform.SetLocalScale(Scale);
}

void VortexSphere_Actor::Update(float _Delta)
{
	BaseSkillActor::Update(_Delta);

	if (SPEED == Speed && true == SkillCollision->Collision(CollisionOrder::Monster))
	{
		Speed = SPEED / 2;
	}
	else if (SPEED / 2 == Speed && false == SkillCollision->Collision(CollisionOrder::Monster))
	{
		Speed = SPEED;
	}

	AttackFunction.AttackUpdate(SkillCollision, CollisionOrder::Monster, "VortexSphere_Hit", 0.4f, 6, 12);
}

void VortexSphere_Actor::MoveUpdate(float _Delta)
{
	Transform.AddLocalPosition(MoveDir * Speed * _Delta);
}

void VortexSphere_Actor::SetDir(ActorDir _Dir)
{
	Dir = _Dir;

	switch (Dir)
	{
	case ActorDir::Right:
		MoveDir = float4::RIGHT;
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MoveDir = float4::LEFT;
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}
