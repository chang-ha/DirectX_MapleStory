#include "PreCompile.h"
#include "FairySpiral.h"
#include "Player.h"
#include "SkillManager.h"

FairySpiral::FairySpiral()
{
	
}

FairySpiral::~FairySpiral()
{

}

void FairySpiral::Init()
{
	
}

void FairySpiral::UseSkill()
{
	ContentSkill::UseSkill();
	FirstUse = true;
	On();
	SkillRenderer1->On();

	ActorDir Dir = Player::MainPlayer->GetDir();
	switch (Dir)
	{
	case ActorDir::Right:
		SkillRenderer1->SetPivotType(PivotType::Right);
		SetScaleSkillRenderer({ -1.0f, 1.0f });
		break;
	case ActorDir::Left:
		SkillRenderer1->SetPivotType(PivotType::Right);
		SetScaleSkillRenderer({ 1.0f, 1.0f });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향으로 스킬을 사용할 수 없습니다.");
		break;
	}

	SkillRenderer1->ChangeAnimation("Attack", true, 0);

	//if (nullptr != SkillCollision)
	//{
	//	SkillCollision->Death();
	//	SkillCollision = nullptr;
	//}
	// Collisions
}

void FairySpiral::EndSkill()
{
	ContentSkill::EndSkill();
	Off();
	SkillRenderer1->Off();
}

void FairySpiral::Start()
{
	ContentSkill::Start();
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentResources");
	Dir.MoveChild("ContentResources\\Textures\\Skill\\FairySprial");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Childs = Directorys[i];
		GameEngineSprite::CreateFolder("FairySprial_" + Childs.GetFileName(), Childs.GetStringPath());
	}

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("FairySprial_Attack");
	SkillScale = Sprite->GetSpriteData(0).GetScale();
	SkillRenderer1->CreateAnimation("Attack", "FairySprial_Attack", 0.06f);
	SkillRenderer1->CreateAnimation("Hit", "FairySprial_Hit", 0.06f);
	SkillRenderer1->SetFrameEvent("Attack", 1, std::bind(&FairySpiral::Event, this, std::placeholders::_1));
	SkillRenderer1->SetEndEvent("Attack", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer1->Off();
			EndSkill();
		}
	);

	SkillCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
	SkillCollision->Transform.SetLocalScale(SkillScale);
	SkillEvent.Stay = [&](GameEngineCollision* _Other)
		{
			float4 OtherPos = _Other->GetParentObject()->Transform.GetWorldPosition();
			SkillManager::PlayerSkillManager->HitPrint("FairySprial_Hit", 6, _Other->GetParentObject());
		};
}

void FairySpiral::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	Transform.SetLocalPosition(PlayerPos);
	if (true == FirstUse)
	{
		SkillCollision->CollisionEvent(CollisionOrder::Monster, SkillEvent);
	}
}

void FairySpiral::Event(GameEngineRenderer* _Renderer)
{
	FirstUse = false;
}
