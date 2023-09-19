#include "PreCompile.h"
#include "PhalanxCharge_Actor.h"


PhalanxCharge_Actor::PhalanxCharge_Actor()
{
	
}

PhalanxCharge_Actor::~PhalanxCharge_Actor()
{

}

void PhalanxCharge_Actor::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseSkillActor::LevelStart(_PrevLevel);
}

void PhalanxCharge_Actor::LevelEnd(GameEngineLevel* _NextLevel)
{
	BaseSkillActor::LevelEnd(_NextLevel);
}

void PhalanxCharge_Actor::Start()
{
	BaseSkillActor::Start();
	MainSpriteRenderer->CreateAnimation("Ready", "PhalanxCharge_Ready", 0.09f);
	MainSpriteRenderer->CreateAnimation("Attack", "PhalanxCharge_Attack", 0.09f);
	MainSpriteRenderer->CreateAnimation("Attack_Loop", "PhalanxCharge_Attack", 0.09f, 7, 18);
	MainSpriteRenderer->CreateAnimation("Death", "PhalanxCharge_Death", 0.02f);
	MainSpriteRenderer->ChangeAnimation("Ready");
	MainSpriteRenderer->SetPivotValue({0.5f, 0.82f});
	MainSpriteRenderer->AutoSpriteSizeOn();

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("PhalanxCharge_Attack");
	Scale = Sprite->GetSpriteData(0).GetScale();
	IsUpdate = false;
	LiveTime = 10.0f;

	MainSpriteRenderer->SetEndEvent("Ready", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->ChangeAnimation("Attack");
			IsUpdate = true;
		}
	);

	MainSpriteRenderer->SetEndEvent("Attack", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->ChangeAnimation("Attack_Loop");
		}
	);

	MainSpriteRenderer->SetStartEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->SetPivotValue({ 0.5f, 0.77f });
		}
	);

	MainSpriteRenderer->SetEndEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			Death();
		}
	);
}

void PhalanxCharge_Actor::Update(float _Delta)
{
	LiveTime -= _Delta;
	if (0.0f >= LiveTime)
	{
		MainSpriteRenderer->ChangeAnimation("Death");
	}

	BaseSkillActor::Update(_Delta);
}