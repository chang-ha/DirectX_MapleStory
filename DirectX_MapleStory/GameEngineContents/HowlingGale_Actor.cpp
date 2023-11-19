#include "PreCompile.h"
#include "HowlingGale_Actor.h"
#include "Player.h"
#include "HitRenderManager.h"
#include "BaseWindActor.h"

#define SPEED 130.0f

HowlingGale_Actor* HowlingGale_Actor::MainHowlingGale = nullptr;

HowlingGale_Actor::HowlingGale_Actor()
{
	
}

HowlingGale_Actor::~HowlingGale_Actor()
{

}

void HowlingGale_Actor::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseSkillActor::LevelStart(_PrevLevel);
}

void HowlingGale_Actor::LevelEnd(GameEngineLevel* _NextLevel)
{
	BaseSkillActor::LevelEnd(_NextLevel);
	if (nullptr != MainHowlingGale)
	{
		Death();
		MainHowlingGale = nullptr;
	}
	HowlingGalePlayer.Stop();
}

void HowlingGale_Actor::Start()
{
	BaseSkillActor::Start();
	MainHowlingGale = this;
	LiveTime = 20.0f;
	Speed = SPEED;

	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->CreateAnimation("Ready", "Ready_Stack1", 0.04f);
	MainSpriteRenderer->CreateAnimation("Attack", "Attack_Stack1");
	MainSpriteRenderer->CreateAnimation("Death", "Death_Stack1");
	MainSpriteRenderer->ChangeAnimation("Ready");
	MainSpriteRenderer->SetPivotValue(float4(0.5f, 0.965f));

	// Renderer Event 1stack
	MainSpriteRenderer->SetEndEvent("Ready", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->ChangeAnimation("Attack");
		}
	);

	MainSpriteRenderer->SetEndEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			IsUpdate = false;
			Death();
			MainHowlingGale = nullptr;
		}
	);

	Scale = { 100, 600 };
	SkillCollision->Transform.SetLocalScale(Scale);
	SkillCollision->Transform.SetLocalPosition({0, 300});

	HowlingGalePlayer = GameEngineSound::SoundPlay("HowlingGale_Loop.mp3", 10000);
	HowlingGalePlayer.SetVolume(GlobalValue::SkillVolume);
}

void HowlingGale_Actor::Update(float _Delta)
{
	if (false == IsUpdate)
	{
		return;
	}

	LiveTime -= _Delta;
	if (0.0f >= LiveTime && false == MainSpriteRenderer->IsCurAnimation("Death"))
	{
		MainSpriteRenderer->ChangeAnimation("Death");

		HowlingGalePlayer.Stop();
		HowlingGalePlayer = GameEngineSound::SoundPlay("HowlingGale_Death.mp3");
		HowlingGalePlayer.SetVolume(GlobalValue::SkillVolume);
	}

	BaseSkillActor::Update(_Delta);

	if (true == IsGround && 0.0f > MoveVectorForce.Y)
	{
		GravityReset();
		MoveVectorForceYReset();
	}

	if (SPEED == Speed && true == SkillCollision->Collision(CollisionOrder::Monster))
	{
		Speed = SPEED / 4;
	}
	else if (SPEED / 4 == Speed && false == SkillCollision->Collision(CollisionOrder::Monster))
	{
		Speed = SPEED;
	}

	AttackFunction.AttackUpdate(SkillCollision, CollisionOrder::Monster, "HowlingGale_Hit", 0.4f, 3, 6);
}

void HowlingGale_Actor::Release()
{
	BaseSkillActor::Release();
	AttackFunction.CollisionTime.clear();
}