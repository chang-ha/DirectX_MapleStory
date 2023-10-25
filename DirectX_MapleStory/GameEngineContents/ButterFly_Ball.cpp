#include "PreCompile.h"
#include "ButterFly_Ball.h"

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
	BallRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTERATTACK);
	BallRenderer->AutoSpriteSizeOn();
	BallRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::monsterattack});

	BallCollision = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
	BallCollision->SetCollisionType(ColType::SPHERE2D);
	BallCollision->Transform.SetLocalScale({21, 21});
}

void ButterFly_Ball::Update(float _Delta)
{
	Transform.AddLocalPosition(DirVector * Speed * _Delta);
}

void ButterFly_Ball::Release()
{

}

void ButterFly_Ball::Init(int _Phase)
{
	std::string PhaseNumber = "";
	PhaseNumber = std::to_string(_Phase);

	BallRenderer->CreateAnimation("Ball", "Phase" + PhaseNumber + "_ButterFly_Ball_Ball");
	BallRenderer->CreateAnimation("Hit", "Phase" + PhaseNumber + "_ButterFly_Ball_Hit");
	BallRenderer->ChangeAnimation("Ball");
}
