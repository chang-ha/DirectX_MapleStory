#include "PreCompile.h"
#include "Monsoon.h"
#include "ContentLevel.h"
#include "HitRenderManager.h"
#include "BaseWindActor.h"

float Monsoon::WholeCoolDown = 0.0f;

Monsoon::Monsoon()
{
	
}

Monsoon::~Monsoon()
{

}

void Monsoon::UseSkill()
{
	AttackFunction.CollisionActor.clear();
	// CollisionActor.clear();

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

	SkillPlayer = GameEngineSound::SoundPlay("Monsoon_Ready.mp3");
	SkillPlayer.SetVolume(GlobalValue::SkillVolume);

	SkillPlayer = GameEngineSound::SoundPlay("Monsoon_Use.mp3");
	SkillPlayer.SetVolume(GlobalValue::SkillVolume);
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
		SceneRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::SKILL);
		SceneRenderer->Transform.SetLocalPosition({50, 0, RenderDepth::skill});
		SceneRenderer->AutoSpriteSizeOn();
		SceneRenderer->Off();
	}

	if (nullptr == SkillCollision)
	{
		SkillCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
		SkillCollision->Transform.SetLocalScale({900, 600});
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

	if (nullptr == GameEngineSound::FindSound("Monsoon_Ready.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Skill\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "Monsoon_Ready.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "Monsoon_Use.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "Monsoon_Hit.mp3");
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
			SkillCollision->On();
			SkillCollision->Transform.SetWorldPosition(ContentLevel::CurContentLevel->GetMainCamera()->Transform.GetWorldPosition());
		}
	);

	SceneRenderer->SetFrameEvent("Screen", 13, [&](GameEngineRenderer* _Renderer)
		{
			SkillCollision->Off();
		}
	);

	SceneRenderer->SetEndEvent("Screen", [&](GameEngineRenderer* _Renderer)
		{
			EndSkill();
			SceneRenderer->Off();
		}
	);

	SkillCurCoolDown = WholeCoolDown;
}

void Monsoon::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	SceneRenderer->GetColorData().MulColor.A = GlobalValue::SkillEffectAlpha;
	PlayerPos.Z = RenderDepth::skill;
	SkillRenderer1->Transform.SetLocalPosition(PlayerPos);
	float4 CameraPos = ContentLevel::CurContentLevel->GetMainCamera()->Transform.GetWorldPosition();
	CameraPos.Z = RenderDepth::skill;
	SceneRenderer->Transform.SetWorldPosition(CameraPos);
	AttackFunction.AttackUpdate(SkillCollision, CollisionOrder::Monster ,"Monsoon_Hit", 12, -1, true);
}

void Monsoon::Init()
{
	Key = 'W';
	InputTypeValue = InputType::IsDown;
	SkillCoolDown = 30.0f;
	UseState = PlayerState::Idle | PlayerState::Alert | PlayerState::Walk | PlayerState::Jump;
	ChangeState = PlayerState::Monsoon;
}

void Monsoon::Release()
{
	WholeCoolDown = SkillCurCoolDown;

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

	AttackFunction.CollisionActor.clear();
}