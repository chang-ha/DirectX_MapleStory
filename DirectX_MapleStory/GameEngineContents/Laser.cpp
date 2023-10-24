#include "PreCompile.h"
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
	if (nullptr == LaserRenderer)
	{
		LaserRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTERATTACK);
		LaserRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::monsterattack});
	}

	if (nullptr == LaserCollision)
	{
		LaserCollision = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
		LaserCollision->SetCollisionType(ColType::OBBBOX2D);
		LaserCollision->Off();
	}
}

void Laser::Update(float _Delta)
{

}

void Laser::Release()
{
	if (nullptr != LaserRenderer)
	{
		LaserRenderer->Death();
		LaserRenderer = nullptr;
	}

	if (nullptr != LaserCollision)
	{
		LaserCollision->Death();
		LaserCollision = nullptr;
	}
}

void Laser::Init(std::string_view _LaserName, int _ReadyEndIndex, float _AniSpeed)
{
	//if (nullptr == GameEngineSprite::Find(std::string(_LaserName.data())))
	//{
	//	GameEngineDirectory Dir;
	//	Dir.MoveParentToExistsChild("ContentResources");
	//	Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Laser");
	//	Dir.MoveChild(_LaserName);
	//	GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	//}

	LaserRenderer->CreateAnimation("Ready", _LaserName, _AniSpeed, 0, _ReadyEndIndex);
	LaserRenderer->CreateAnimation("Attack", _LaserName, _AniSpeed, _ReadyEndIndex);
	LaserRenderer->ChangeAnimation("Ready");
	LaserRenderer->AutoSpriteSizeOn();

	LaserRenderer->SetEndEvent("Ready", [&](GameEngineSpriteRenderer*)
		{
			LaserRenderer->ChangeAnimation("Attack");
		}
	);

	LaserRenderer->SetStartEvent("Attack", [&](GameEngineSpriteRenderer*)
		{
			LaserCollision->On();
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
	LaserCollision->Transform.SetLocalRotation({ 0.0f, 0.0f, _Angle });
}

void Laser::SetColScale(const float4& _Scale)
{
	LaserCollision->Transform.SetLocalScale(_Scale);
}
