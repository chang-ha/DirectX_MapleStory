﻿#include "PreCompile.h"
#include "Laser.h"

Laser::Laser()
{

}

Laser::~Laser()
{

}

void Laser::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Laser::Start()
{
	LaserRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterAttack);
	LaserCollision = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
}

void Laser::Update(float _Delta)
{

}

void Laser::Init(std::string_view _LaserName)
{
	if (nullptr == GameEngineSprite::Find(std::string(_LaserName.data())))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Laser");
		Dir.MoveChild(_LaserName);
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	if (nullptr == GameEngineSprite::Find("Phasr1_Hit"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Laser\\Phase1_Hit");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	LaserRenderer->CreateAnimation("Ready", _LaserName, 0.1f, 0, 12);
	LaserRenderer->CreateAnimation("Attack", _LaserName, 0.1f, 12);
	LaserRenderer->ChangeAnimation("Ready");
	LaserRenderer->AutoSpriteSizeOn();

	LaserRenderer->SetEndEvent("Ready", [&](GameEngineSpriteRenderer*)
		{
			LaserRenderer->ChangeAnimation("Attack");
		}
	);

	LaserRenderer->SetStartEvent("Attack", [&](GameEngineSpriteRenderer*)
		{

		}
	);

	LaserRenderer->SetEndEvent("Attack", [&](GameEngineSpriteRenderer*)
		{
			Death();
		}
	);
}

void Laser::SetAngle(float _Angle)
{
	LaserRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, -_Angle });
}