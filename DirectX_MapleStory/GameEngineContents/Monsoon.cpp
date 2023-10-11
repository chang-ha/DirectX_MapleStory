#include "PreCompile.h"
#include "Monsoon.h"
#include "ContentLevel.h"
#include "SkillManager.h"
#include "BaseWindActor.h"

Monsoon::Monsoon()
{
	
}

Monsoon::~Monsoon()
{

}

void Monsoon::UseSkill()
{
	On();
	ContentSkill::UseSkill();

	switch (PlayerDir)
	{
	case ActorDir::Right:
		SkillLeftFlip();
		SkillRenderer1->SetPivotValue(float4(0.62f, 0.73f));
		break;
	case ActorDir::Left:
		SkillRightFlip();
		SkillRenderer1->SetPivotValue(float4(0.38f, 0.73f));
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	SkillRenderer1->ChangeAnimation("Effect", true, 0);
	SceneRenderer->ChangeAnimation("Screen", true, 0);
	SkillRenderer1->On();
	SceneRenderer->On();
}

void Monsoon::EndSkill()
{
	ContentSkill::EndSkill();
	Off();
}

void Monsoon::Start()
{
	ContentSkill::Start();

	if (nullptr == SceneRenderer)
	{
		SceneRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::Skill);
		SceneRenderer->Transform.SetLocalPosition({50,0});
		SceneRenderer->AutoSpriteSizeOn();
		SceneRenderer->Off();
	}

	if (nullptr == SkillCollision)
	{
		// 추후 UICollision로 개선
		SkillCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
		SkillCollision->Transform.SetLocalScale({600, 450});
		SkillCollision->Off();
	}

	if (nullptr == GameEngineSprite::Find("Monsoon_Ready"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\Monsoon");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Monsoon_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	SkillRenderer1->CreateAnimation("Effect", "Monsoon_Effect", 0.07f);
	SkillRenderer1->SetEndEvent("Effect", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer1->Off();
		}
	);

	SceneRenderer->CreateAnimation("Screen", "Monsoon_Screen", 0.07f);

	SceneRenderer->SetFrameEvent("Screen", 10, [&](GameEngineRenderer* _Renderer)
		{
			FirstUse = true;
			SkillCollision->On();
			SkillCollision->Transform.SetWorldPosition(ContentLevel::CurContentLevel->GetMainCamera()->Transform.GetWorldPosition());
		}
	);

	SceneRenderer->SetFrameEvent("Screen", 11, [&](GameEngineRenderer* _Renderer)
		{
			FirstUse = false;
			SkillCollision->Off();
		}
	);

	SceneRenderer->SetEndEvent("Screen", [&](GameEngineRenderer* _Renderer)
		{
			EndSkill();
			SceneRenderer->Off();
		}
	);
}

void Monsoon::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	SkillRenderer1->Transform.SetLocalPosition(PlayerPos);
	if (true == FirstUse)
	{
		SkillCollision->Collision(CollisionOrder::Monster, std::bind(&Monsoon::CollisionEvent, this, std::placeholders::_1));
	}
}

void Monsoon::Release()
{
	if (nullptr != SceneRenderer)
	{
		SceneRenderer->Death();
		SceneRenderer = nullptr;
	}

	if (nullptr != SkillCollision)
	{
		SkillCollision->Death();
		SkillCollision = nullptr;
	}
}

void Monsoon::CollisionEvent(std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup)
{
	for (size_t i = 0; i < _CollisionGroup.size(); i++)
	{
		std::shared_ptr<GameEngineCollision> _Other = _CollisionGroup[i];
		SkillManager::PlayerSkillManager->HitPrint("Monsoon_Hit", 12, _Other->GetParentObject());
	}

	BaseWindActor::CreateTriflingWind();
}