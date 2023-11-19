#include "PreCompile.h"
#include "WindWalk.h"
#include "Player.h"

#define ANI_SPEED 0.1f

WindWalk::WindWalk()
{

}

WindWalk::~WindWalk()
{

}

void WindWalk::UseSkill()
{
	ContentSkill::UseSkill();
	On();
	SkillRenderer1->On();
	SkillAfterImageRenderer->On();
	
	switch (PlayerDir)
	{
	case ActorDir::Right:
		SkillLeftFlip();
		SkillRenderer1->SetPivotValue(float4(0.25f, 0.6f));
		break;
	case ActorDir::Left:
		SkillRightFlip();
		SkillRenderer1->SetPivotValue(float4(0.75f, 0.6f));
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("�������� �ʴ� �����Դϴ�.");
		break;
	}

	PlayerPos.Z = RenderDepth::skill;
	SkillRenderer1->ChangeAnimation("Effect1", true);
	SkillAfterImageRenderer->ChangeAnimation("AfterImage", true);
	SkillAfterImageRenderer->Transform.SetLocalPosition(PlayerPos);

	SkillPlayer = GameEngineSound::SoundPlay("WindWalk_Use.mp3");
	SkillPlayer.SetVolume(GlobalValue::SkillVolume);
}

void WindWalk::EndSkill()
{
	ContentSkill::EndSkill();
}

void WindWalk::Start()
{
	MP = 0;

	ContentSkill::Start();
	if (nullptr == GameEngineSprite::Find("WindWalk_Effect1"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\WindWalk");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("WindWalk_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}
	SkillRenderer1->CreateAnimation("Effect1", "WindWalk_Effect1", ANI_SPEED);
	SkillAfterImageRenderer->CreateAnimation("AfterImage", "WindWalk_AfterImage", ANI_SPEED);

	if (nullptr == GameEngineSound::FindSound("WindWalk_Use.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Sounds\\Skill\\WindWalk_Use.mp3");
		GameEngineSound::SoundLoad(FilePath.GetStringPath());
	}

	SkillAfterImageRenderer->SetPivotType(PivotType::Center);

	SkillRenderer1->Off();
	SkillAfterImageRenderer->Off();

	SkillRenderer1->SetEndEvent("Effect1", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer1->Off();
		}
	);

	SkillAfterImageRenderer->SetEndEvent("AfterImage", [&](GameEngineRenderer* _Renderer)
		{
			SkillAfterImageRenderer->Off();
			this->Off();
		}
	);

}

void WindWalk::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	PlayerPos.Z = RenderDepth::skill;
	SkillRenderer1->Transform.SetLocalPosition(PlayerPos);

}

void WindWalk::Init()
{
	Key = VK_SPACE;
	InputTypeValue = InputType::IsDown;
	SkillCoolDown = 0.0f;
	UseState = PlayerState::Idle | PlayerState::Alert | PlayerState::Walk | PlayerState::Jump;
	ChangeState = PlayerState::WindWalk;
}