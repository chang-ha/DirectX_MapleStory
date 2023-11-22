#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "MercilessWinds_Actor.h"
#include "ContentLevel.h"
#include "Player.h"
#include "BaseWindActor.h"

MercilessWinds_Actor::MercilessWinds_Actor()
{

}

MercilessWinds_Actor::~MercilessWinds_Actor()
{

}

void MercilessWinds_Actor::Start()
{
	BaseWindActor::Start();

	if (nullptr == GameEngineSprite::Find("MercilessWinds_Actor_Attack"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\MercilessWinds_Actor");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("MercilessWinds_Actor_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	Transform.SetLocalPosition(Player::MainPlayer->Transform.GetWorldPosition());

	MainSpriteRenderer->CreateAnimation("Attack", "MercilessWinds_Actor_Attack");
	MainSpriteRenderer->CreateAnimation("Hit", "MercilessWinds_Actor_Hit", 0.06f);
	ReadyStart();

	MainSpriteRenderer->SetEndEvent("Hit", [&](GameEngineRenderer* _Renderer)
		{
			Death();
		}
	);

	DetectCollision->Transform.SetLocalScale({ 1500, 2000 });
	HitCollision->Transform.SetLocalScale({ 90, 40 });
	MainSpriteRenderer->LeftFlip();

	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);

	Off();
	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this));
	float4 PivotValue = Random.RandomVectorBox2D(-150, 150, -200, 200);
	Transform.AddLocalPosition(PivotValue);

	float RandomValue = Random.RandomFloat(0, 1);
	if (0.5 >= RandomValue)
	{
		DirAngle = 90.0f;
	}
	else
	{
		DirAngle = -90.0f;
	}
}

void MercilessWinds_Actor::ReadyStart()
{
	ChangeState(WindState::Attack);
}

void MercilessWinds_Actor::AttackStart()
{
	MainSpriteRenderer->ChangeAnimation("Attack");
	MainSpriteRenderer->SetPivotValue({0.3f, 0.45f});
}

void MercilessWinds_Actor::HitStart()
{
	MainSpriteRenderer->ChangeAnimation("Hit");
	MainSpriteRenderer->SetPivotType(PivotType::Center);
	HitCollision->Off();
	DetectCollision->Off();

	GameEngineSoundPlayer MercilessPlayer = GameEngineSound::SoundPlay("MercilessWinds_Hit.mp3");
	MercilessPlayer.SetVolume(GlobalValue::HitVolume);
}

void MercilessWinds_Actor::DeathStart()
{
	HitCollision->Off();
	DetectCollision->Off();
}

void MercilessWinds_Actor::DeathUpdate(float _Delta)
{
	DieStartTime += _Delta;
	MainSpriteRenderer->GetColorData().MulColor.A -= DieStartTime;

	if (0.0f > MainSpriteRenderer->GetColorData().MulColor.A)
	{
		MainSpriteRenderer->GetColorData().MulColor.A = 0.0f;
		Death();
	}
}
