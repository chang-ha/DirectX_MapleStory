#include "PreCompile.h"
#include "FairySpiral.h"
#include "Player.h"
#include "HitRenderManager.h"
#include "BaseWindActor.h"

#define XRANGE 380.0f
#define YRANGE 200.0f

FairySpiral::FairySpiral()
{
	
}

FairySpiral::~FairySpiral()
{

}

void FairySpiral::UseSkill()
{
	AttackFunction.CollisionActor.clear();
	// CollisionActor.clear();

	ContentSkill::UseSkill();
	On();
	SkillRenderer1->On();

	ActorDir Dir = Player::MainPlayer->GetDir();
	switch (Dir)
	{
	case ActorDir::Right:
		SkillRenderer1->SetPivotValue(float4(0.8f, 0.5f));
		SkillCollision->Transform.SetLocalPosition({ XRANGE / 2, YRANGE / 4 });
		SkillLeftFlip();
		break;
	case ActorDir::Left:
		SkillRenderer1->SetPivotValue(float4(0.2f, 0.5f));
		SkillCollision->Transform.SetLocalPosition({ -XRANGE / 2, YRANGE / 4 });
		SkillRightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향으로 스킬을 사용할 수 없습니다.");
		break;
	}

	SkillRenderer1->ChangeAnimation("Attack", true, 0);

	SkillPlayer = GameEngineSound::SoundPlay("FairySprial_Use.mp3");
	SkillPlayer.SetVolume(GlobalValue::SkillVolume);
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
	if (nullptr == GameEngineSprite::Find("FairySprial_Attack"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\FairySprial");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("FairySprial_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	if (nullptr == GameEngineSound::FindSound("FairySprial_Use.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Skill\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "FairySprial_Use.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "FairySprial_Hit.mp3");
	}

	SkillRenderer1->CreateAnimation("Attack", "FairySprial_Attack", 0.06f);
	SkillRenderer1->CreateAnimation("Hit", "FairySprial_Hit", 0.06f);

	SkillRenderer1->SetFrameEvent("Attack", 2, [&](GameEngineRenderer* _Renderer)
		{
			SkillCollision->On();
		}
	);

	SkillRenderer1->SetFrameEvent("Attack", 6, [&](GameEngineRenderer* _Renderer)
		{
			SkillCollision->Off();
		}
	);

	SkillRenderer1->SetEndEvent("Attack", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer1->Off();
			EndSkill();
		}
	);

	if (nullptr == SkillCollision)
	{
		SkillCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
		SkillCollision->Transform.SetLocalScale({ XRANGE, YRANGE });
		SkillCollision->Off();
	}
}

void FairySpiral::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	Transform.SetLocalPosition(PlayerPos);
	AttackFunction.AttackUpdate(SkillCollision, CollisionOrder::Monster, "FairySprial_Hit", 6);
}

void FairySpiral::Release()
{
	ContentSkill::Release();

	if (nullptr != SkillCollision)
	{
		SkillCollision->Death();
		SkillCollision = nullptr;
	}

	AttackFunction.CollisionActor.clear();
}

void FairySpiral::Init()
{
	Key = VK_SHIFT;
	InputTypeValue = InputType::IsPress | InputType::IsDown;
	SkillCoolDown = 0.0f;
	UseState = PlayerState::Idle | PlayerState::Alert | PlayerState::Walk | PlayerState::Jump;
	ChangeState = PlayerState::FairySpiral;
}
