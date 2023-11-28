#include "PreCompile.h"
#include "HowlingGale_Actor.h"
#include "Player.h"
#include "HitRenderManager.h"
#include "BaseWindActor.h"
#include "ContentActor.h"

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

	if (nullptr == DetectCollision)
	{
		DetectCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Detect);
		// DetectCollision->Off();
	}
	MainHowlingGale = this;
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

	// Detect Monster & Set Dir
	if (true == SkillCollision->Collision(CollisionOrder::Monster))
	{
		return;
	}

	if (false == DetectCollision->Collision(CollisionOrder::Monster))
	{
		return;
	}

	DetectCollision->Collision(CollisionOrder::Monster, [&](std::vector<GameEngineCollision*> _Collisions)
		{
			ContentBaseActor* _TargetActor = nullptr;
			for (size_t i = 0; i < _Collisions.size(); i++)
			{
				ContentBaseActor* _Actor = dynamic_cast<ContentBaseActor*>(_Collisions[i]->GetParentObject());

				if (nullptr == _Actor)
				{
					MsgBoxAssert("ContentBaseActor를 상속받지 않는 몬스터가 존재합니다.");
					return;
				}

				int MostHP = 0;
				int CompareHP = _Actor->GetHP();

				if (MostHP < CompareHP)
				{
					MostHP = CompareHP;
					_TargetActor = _Actor;
				}
			}

			if (nullptr == _TargetActor)
			{
				return;
			}

			float4 CurPos = this->Transform.GetWorldPosition();
			float4 TargetPos = _TargetActor->Transform.GetWorldPosition();

			if (0.0f > CurPos.X - TargetPos.X)
			{
				SetDir(ActorDir::Right);
			}
			else
			{
				SetDir(ActorDir::Left);
			}
		});
}

void HowlingGale_Actor::Release()
{
	BaseSkillActor::Release();

	if (nullptr != DetectCollision)
	{
		DetectCollision->Death();
		DetectCollision = nullptr;
	}

	AttackFunction.CollisionTime.clear();
}

void HowlingGale_Actor::Init(int _Stack)
{
	Stack = _Stack;
	std::string StackString = std::to_string(Stack);

	LiveTime = 20.0f;
	Speed = SPEED;

	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->CreateAnimation("Ready", "Ready_Stack" + StackString, 0.04f);
	MainSpriteRenderer->CreateAnimation("Attack", "Attack_Stack" + StackString);
	MainSpriteRenderer->CreateAnimation("Death", "Death_Stack" + StackString);
	MainSpriteRenderer->ChangeAnimation("Ready");
	MainSpriteRenderer->SetPivotValue(float4(0.5f, 0.965f));

	// Renderer Event
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

	switch (Stack)
	{
	case 1:
		Scale = { 100, 600 };
		break;
	case 2:
		Scale = { 330, 800 };
		break;
	default:
		MsgBoxAssert("잘못된 스택값이 들어왔습니다.");
		break;
	}

	SkillCollision->Transform.SetLocalScale(Scale);
	SkillCollision->Transform.SetLocalPosition({ 0, Scale.hY()});

	DetectCollision->Transform.SetLocalScale({1500, Scale.Y});
	DetectCollision->Transform.SetLocalPosition({ 0, Scale.hY() });

	HowlingGalePlayer = GameEngineSound::SoundPlay("HowlingGale_Loop.mp3", 10000);
	HowlingGalePlayer.SetVolume(GlobalValue::SkillVolume);
}
