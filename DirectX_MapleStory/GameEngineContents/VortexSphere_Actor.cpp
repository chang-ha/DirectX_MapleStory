#include "PreCompile.h"
#include "VortexSphere_Actor.h"
#include "SkillManager.h"

VortexSphere_Actor::VortexSphere_Actor()
{

}

VortexSphere_Actor::~VortexSphere_Actor()
{

}

void VortexSphere_Actor::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseSkillActor::LevelStart(_PrevLevel);
}

void VortexSphere_Actor::LevelEnd(GameEngineLevel* _NextLevel)
{
	BaseSkillActor::LevelEnd(_NextLevel);
}

void VortexSphere_Actor::Start()
{
	BaseSkillActor::Start();
	GravityOff();
	IsBlockOut = false;
	Speed = 150.0f;

	MainSpriteRenderer->CreateAnimation("Attack", "VortexSphere_Actor", 0.07f);
	MainSpriteRenderer->ChangeAnimation("Attack");
	MainSpriteRenderer->AutoSpriteSizeOn();
	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("VortexSphere_Actor");
	Scale = Sprite->GetSpriteData(0).GetScale();

	SkillCollision->Transform.SetLocalScale(Scale);
}

void VortexSphere_Actor::Update(float _Delta)
{
	BaseSkillActor::Update(_Delta);
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
					SkillManager::PlayerSkillManager->HitPrint("VortexSphere_Hit", 6, _Other->GetParentObject());
					CollisionTime[_Other] = HIT_TIME;
				}
			}
		}
	);
}

void VortexSphere_Actor::MoveUpdate(float _Delta)
{
	Transform.AddLocalPosition(MoveDir * Speed * _Delta);
}

void VortexSphere_Actor::SetDir(ActorDir _Dir)
{
	Dir = _Dir;

	switch (Dir)
	{
	case ActorDir::Right:
		MoveDir = float4::RIGHT;
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MoveDir = float4::LEFT;
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}
