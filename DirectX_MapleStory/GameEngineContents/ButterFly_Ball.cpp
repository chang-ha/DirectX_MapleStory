#include "PreCompile.h"
#include "ButterFly_Ball.h"
#include "SkillManager.h"
#include "AttackFunction.h"

ButterFly_Ball::ButterFly_Ball()
{

}

ButterFly_Ball::~ButterFly_Ball()
{

}

void ButterFly_Ball::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void ButterFly_Ball::Start()
{
	if (nullptr == BallRenderer)
	{
		BallRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTERATTACK);
		BallRenderer->AutoSpriteSizeOn();
		BallRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::monsterattack });
	}

	if (nullptr == BallCollision)
	{
		BallCollision = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
		BallCollision->SetCollisionType(ColType::SPHERE2D);
		BallCollision->Transform.SetLocalScale({ 21, 21 });
	}
}

void ButterFly_Ball::Update(float _Delta)
{
	Transform.AddLocalPosition(DirVector * Speed * _Delta);
	AttackFunction.AttackUpdate(BallCollision, CollisionOrder::Player, "Phase" + PhaseNumber + "_ButterFly_Ball_Hit", 1, 5, false);
}

void ButterFly_Ball::Release()
{
	if (nullptr != BallRenderer)
	{
		BallRenderer->Death();
		BallRenderer = nullptr;
	}

	if (nullptr != BallCollision)
	{
		BallCollision->Death();
		BallCollision = nullptr;
	}

	AttackFunction.CollisionActor.clear();
}

void ButterFly_Ball::Init(int _Phase)
{
	PhaseNumber = "";
	PhaseNumber = std::to_string(_Phase);

	BallRenderer->CreateAnimation("Ball", "Phase" + PhaseNumber + "_ButterFly_Ball_Ball");
	BallRenderer->CreateAnimation("Hit", "Phase" + PhaseNumber + "_ButterFly_Ball_Hit");
	BallRenderer->ChangeAnimation("Ball");
}
