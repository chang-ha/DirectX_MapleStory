#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "PhantasmalWind.h"

PhantasmalWind::PhantasmalWind()
{

}

PhantasmalWind::~PhantasmalWind()
{

}

void PhantasmalWind::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void PhantasmalWind::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void PhantasmalWind::Start()
{
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterAttack);
	MainSpriteRenderer->CreateAnimation("Attack", "Lucid_Attack");
	MainSpriteRenderer->ChangeAnimation("Attack");
	MainSpriteRenderer->LeftFlip();

	// Random Angle
	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this));
	DirAngle = Random.RandomFloat(0.0f, 180.0f);
	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);
	MoveVector.Y *= -1.0f;
	MainSpriteRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, -DirAngle });

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Lucid_Attack");
	float4 Scale = Sprite->GetSpriteData(0).GetScale();
	float RandomRatio = Random.RandomFloat(0.2f, 1.0f);
	MainSpriteRenderer->SetImageScale(Scale * RandomRatio);
}

void PhantasmalWind::Update(float _Delta)
{
	LiveTime -= _Delta;
	if (0.0f >= LiveTime)
	{
		Death();
	}

	Transform.AddLocalPosition( MoveVector * Speed * _Delta);
}