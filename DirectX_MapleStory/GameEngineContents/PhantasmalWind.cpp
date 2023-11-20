#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "PhantasmalWind.h"
#include "ReleaseFunction.h"

bool PhantasmalWind::AllAngleValue = false;

PhantasmalWind::PhantasmalWind()
{

}

PhantasmalWind::~PhantasmalWind()
{

}

void PhantasmalWind::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void PhantasmalWind::Start()
{
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTERATTACK);
	MainSpriteRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::monsterattack});
	MainSpriteRenderer->CreateAnimation("Attack", "PhantasmalWind");
	MainSpriteRenderer->ChangeAnimation("Attack");
	MainSpriteRenderer->LeftFlip();

	PhantasmaCollision = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
	PhantasmaCollision->SetCollisionType(ColType::OBBBOX2D);

	// Random Angle
	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this));
	if (true == AllAngleValue)
	{
		DirAngle = Random.RandomFloat(0.0f, 360.0f);
	}
	else if (false == AllAngleValue)
	{
		DirAngle = Random.RandomFloat(0.0f, 180.0f);
	}

	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);
	MoveVector.Y *= -1.0f;
	MainSpriteRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, -DirAngle });
	PhantasmaCollision->Transform.SetLocalRotation({ 0.0f, 0.0f, DirAngle });

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("PhantasmalWind");
	float4 Scale = Sprite->GetSpriteData(0).GetScale();
	float RandomRatio = Random.RandomFloat(0.2f, 1.0f);
	MainSpriteRenderer->SetImageScale(Scale * RandomRatio);
	PhantasmaCollision->Transform.SetLocalScale(float4{230, 350} * RandomRatio);
	PhantasmaCollision->Transform.SetLocalPosition(MoveVector * 50.0f * RandomRatio);
}

void PhantasmalWind::Update(float _Delta)
{
	LiveTime -= _Delta;
	if (0.0f >= LiveTime)
	{
		Death();
	}

	Transform.AddLocalPosition( MoveVector * Speed * _Delta);
	AttackFunction.AttackUpdate(PhantasmaCollision, CollisionOrder::Player, "PhantasmalWind_Hit", 1.0f, 1, 10, false, PivotType::Center);
	AttackFunction.CollisionTimeUpdate(_Delta);
}

void PhantasmalWind::Release()
{
	if (nullptr != MainSpriteRenderer)
	{
		MainSpriteRenderer->Death();
		MainSpriteRenderer = nullptr;
	}

	if (nullptr != PhantasmaCollision)
	{
		PhantasmaCollision->Death();
		PhantasmaCollision = nullptr;
	}
}