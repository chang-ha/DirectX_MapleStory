#include "PreCompile.h"
#include "VortexSphere.h"
#include "VortexSphere_Actor.h"

float VortexSphere::WholeCoolDown = 0.0f;

VortexSphere::VortexSphere()
{
	
}

VortexSphere::~VortexSphere()
{

}

void VortexSphere::UseSkill()
{
	ContentSkill::UseSkill();
	On();
	SkillRenderer1->On();
	SkillRenderer1->ChangeAnimation("Effect1", true);

	switch (PlayerDir)
	{
	case ActorDir::Right:
		SkillRenderer1->SetPivotValue({ 0.63f, 0.55f });
		SkillRenderer2->SetPivotValue({ 0.1f, 0.51f });
		SkillRenderer1->LeftFlip();
		SkillRenderer2->LeftFlip();
		break;
	case ActorDir::Left:
		SkillRenderer1->SetPivotValue({ 0.37f, 0.55f });
		SkillRenderer2->SetPivotValue({ 0.9f, 0.51f });
		SkillRenderer1->RightFlip();
		SkillRenderer2->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	SkillPlayer = GameEngineSound::SoundPlay("VortexSphere_Use.mp3");
	SkillPlayer.SetVolume(GlobalValue::SkillVolume);
}

void VortexSphere::EndSkill()
{
	ContentSkill::EndSkill();
	SkillRenderer1->Off();
	SkillRenderer2->Off();
	Off();
}

void VortexSphere::Start()
{
	ContentSkill::Start();

	if (nullptr == GameEngineSprite::Find("VortexSphere_Effect1"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\VortexSphere");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("VortexSphere_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	if (nullptr == GameEngineSound::FindSound("VortexSphere_Use.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Skill\\");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "VortexSphere_Use.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath() + "VortexSphere_Hit.mp3");
	}

	SkillRenderer1->CreateAnimation("Effect1", "VortexSphere_Effect1", 0.08f);
	SkillRenderer2->CreateAnimation("Effect2", "VortexSphere_Effect2", 0.08f);

	SkillRenderer1->SetFrameEvent("Effect1", 5, [&](GameEngineSpriteRenderer* _Renderer)
		{
			SkillRenderer2->On();
			SkillRenderer2->ChangeAnimation("Effect2", true);

			float4 PivotValue = float4::ZERO;
			switch (PlayerDir)
			{
			case ActorDir::Right:
				PivotValue.X = 180.0f;
				break;
			case ActorDir::Left:
				PivotValue.X = -180.0f;
				break;
			case ActorDir::Null:
			default:
				MsgBoxAssert("존재하지 않는 방향입니다.");
				break;
			}
			PivotValue.Y = 20.0f;

			std::shared_ptr<VortexSphere_Actor> _Actor = GetLevel()->CreateActor<VortexSphere_Actor>(UpdateOrder::Skill);
			_Actor->Transform.SetLocalPosition(PlayerPos + PivotValue);
			_Actor->SetDir(PlayerDir);
		}
	);

	SkillRenderer1->SetEndEvent("Effect1", [&](GameEngineRenderer* _Renderer)
		{
			EndSkill();
		}
	);

	SkillCurCoolDown = WholeCoolDown;
}

void VortexSphere::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	Transform.SetLocalPosition(PlayerPos);
}

void VortexSphere::Release()
{
	ContentSkill::Release();
	WholeCoolDown = SkillCurCoolDown;
}

void VortexSphere::Init()
{
	Key = 'S';
	InputTypeValue = InputType::IsPress | InputType::IsDown;
	SkillCoolDown = 1.0f;
	UseState = PlayerState::Idle | PlayerState::Alert | PlayerState::Walk | PlayerState::Jump;
	ChangeState = PlayerState::VortexSphere;
}
