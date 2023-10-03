#include "PreCompile.h"
#include "PhalanxCharge_Actor.h"
#include "SkillManager.h"

#define SPEED 200.0f

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
	MainSpriteRenderer->CreateAnimation("Ready", "PhalanxCharge_Ready", 0.06f);
	MainSpriteRenderer->CreateAnimation("Attack", "PhalanxCharge_Attack", 0.09f);
	MainSpriteRenderer->CreateAnimation("Attack_Loop", "PhalanxCharge_Attack", 0.09f, 7, 18);
	MainSpriteRenderer->CreateAnimation("Death", "PhalanxCharge_Death", 0.02f);
	MainSpriteRenderer->ChangeAnimation("Ready");
	MainSpriteRenderer->SetPivotValue({0.5f, 0.82f});
	MainSpriteRenderer->AutoSpriteSizeOn();
	Speed = SPEED;

	IsUpdate = false;
	LiveTime = 10.0f;
	SkillCollision->Off();

	MainSpriteRenderer->SetEndEvent("Ready", [&](GameEngineRenderer* _Renderer)
		{
			MainSpriteRenderer->ChangeAnimation("Attack");
			IsUpdate = true;
			SkillCollision->On();
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

	Scale = {250, 100};
	SkillCollision->Transform.SetLocalScale(Scale);
	SkillCollision->Transform.SetLocalPosition({0, 50});
}

void PhalanxCharge_Actor::Update(float _Delta)
{
	LiveTime -= _Delta;
	if (0.0f >= LiveTime || 70 <= HitCount)
	{
		MainSpriteRenderer->ChangeAnimation("Death");
	}

	BaseSkillActor::Update(_Delta);

	if (SPEED == Speed && true == SkillCollision->Collision(CollisionOrder::Monster))
	{
		Speed = SPEED / 2;
	}
	else if (SPEED / 2 == Speed && false == SkillCollision->Collision(CollisionOrder::Monster))
	{
		Speed = SPEED;
	}

	SkillCollision->Collision(CollisionOrder::Monster, [&](std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup)
		{
			for (size_t i = 0; i < _CollisionGroup.size(); i++)
			{
				std::shared_ptr<GameEngineCollision> _Other = _CollisionGroup[i];
				if (false == CollisionTime.contains(_Other))
				{
					CollisionTime[_Other] = 0.0f;
				}

				if (0.0f >= CollisionTime[_Other])
				{
					HitCount += 1;
					SkillManager::PlayerSkillManager->HitPrint("PhalanxCharge_Hit", 1, _Other->GetParentObject());
					CollisionTime[_Other] = HIT_TIME;
				}
			}
		}
	);
}