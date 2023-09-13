#include "PreCompile.h"
#include "ContentMonster.h"


ContentMonster::ContentMonster()
{

}

ContentMonster::~ContentMonster()
{

}

void ContentMonster::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void ContentMonster::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void ContentMonster::ChangeState(MonsterState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case MonsterState::Idle:
			IdleEnd();
			break;
		case MonsterState::Hit:
			HitEnd();
			break;
		case MonsterState::Death:
			DeathEnd();
			break;
		case MonsterState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값을 끝내려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case MonsterState::Idle:
			IdleStart();
			break;
		case MonsterState::Hit:
			HitStart();
			break;
		case MonsterState::Death:
			DeathStart();
			break;
		case MonsterState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 변경하려고 했습니다.");
			break;
		}
	}

	State = _State;
}

void ContentMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
	case MonsterState::Hit:
		return HitUpdate(_Delta);
	case MonsterState::Death:
		return DeathUpdate(_Delta);
	case MonsterState::Null:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void ContentMonster::Start()
{
	if (nullptr == GameEngineSprite::Find("Monster_Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Monster");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& ChildDir = Directorys[i];
			GameEngineSprite::CreateFolder(ChildDir.GetStringPath());
		}

	}
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	MainSpriteRenderer->CreateAnimation("Monster_Idle", "Monster_Idle");
	MainSpriteRenderer->CreateAnimation("Monster_Hit", "Monster_Hit");
	MainSpriteRenderer->CreateAnimation("Monster_Die", "Monster_Die");
	MainSpriteRenderer->ChangeAnimation("Monster_Idle");
	MainSpriteRenderer->AutoSpriteSizeOn();
	State = MonsterState::Idle;

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Monster_Idle");
	MonsterScale = Sprite->GetSpriteData(0).GetScale();
	Sprite = nullptr;

	// Collision
	MainCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	MainCollision->Transform.SetLocalScale(MonsterScale);

	// MonsterEvent.Enter = std::bind(&ContentMonster::CollisionEnter, this, std::placeholders::_1);
	MainSpriteRenderer->SetEndEvent("Monster_Die", [=](GameEngineRenderer* _Renderer)
		{Death(); });
}

void ContentMonster::Update(float _Delta)
{
	StateUpdate(_Delta);
	MainCollision->CollisionEvent(CollisionOrder::PlayerAttack, MonsterEvent);
}

void ContentMonster::CollisionEnter(GameEngineCollision* _Other)
{

}

void ContentMonster::IdleStart()
{
	
}
void ContentMonster::HitStart()
{

}

void ContentMonster::DeathStart()
{
	MainSpriteRenderer->ChangeAnimation("Monster_Die");
}

void ContentMonster::IdleEnd()
{
	}
void ContentMonster::HitEnd()
{
	}
void ContentMonster::DeathEnd()
{
	}
void ContentMonster::IdleUpdate(float _Delta)
{
	}
void ContentMonster::HitUpdate(float _Delta)
{
	}
void ContentMonster::DeathUpdate(float _Delta)
{
	//if (true == MainSpriteRenderer->IsCurAnimationEnd())
	//{
	//	Death();
	//}
}