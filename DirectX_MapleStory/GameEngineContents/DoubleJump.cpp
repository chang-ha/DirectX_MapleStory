#include "PreCompile.h"
#include "DoubleJump.h"
#include "Player.h"

#define ANI_SPEED 0.08f
DoubleJump::DoubleJump()
{

}

DoubleJump::~DoubleJump()
{

}
void DoubleJump::Init()
{
	int a = 0;
}

void DoubleJump::UseSkill()
{
	ContentSkill::UseSkill();

	SkillRenderer1->On();
	SkillRenderer2->On();
	SkillAfterImageRenderer->On();

	std::string AniDir = "";
	if (GameEngineInput::IsPress(VK_UP))
	{
		AniDir = "Up_";
		SkillRenderer1->SetPivotType(PivotType::Top);
		SkillRenderer2->SetPivotType(PivotType::Top);
		SkillAfterImageRenderer->SetPivotType(PivotType::Top);
		Pivot = float4(0, PlayerScale.hY());
	}
	else
	{
		ActorDir Dir = Player::MainPlayer->GetDir();
		switch (Dir)
		{
		case ActorDir::Right:
			SetScaleSkillRenderer({ -1.0f, 1.0f });
			SkillRenderer1->SetPivotType(PivotType::Left);
			SkillRenderer2->SetPivotType(PivotType::Left);
			SkillAfterImageRenderer->SetPivotType(PivotType::Left);
			Pivot = PlayerScale.Half();
			break;
		case ActorDir::Left:
			SetScaleSkillRenderer({ 1.0f, 1.0f });
			SkillRenderer1->SetPivotType(PivotType::Left);
			SkillRenderer2->SetPivotType(PivotType::Left);
			SkillAfterImageRenderer->SetPivotType(PivotType::Left);
			Pivot = float4(-PlayerScale.hX(), PlayerScale.hY());
			break;
		case ActorDir::Null:
		default:
			break;
		}
	}
	SkillRenderer1->ChangeAnimation(AniDir + "Effect1", true, 0);
	SkillRenderer2->ChangeAnimation(AniDir + "Effect2", true, 0);
	SkillAfterImageRenderer->ChangeAnimation(AniDir + "AfterImage", true, 0);
	SkillAfterImageRenderer->Transform.SetLocalPosition(PlayerPos);
}

void DoubleJump::EndSkill()
{
	ContentSkill::EndSkill();
}

void DoubleJump::Start() 
{
	ContentSkill::Start();

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentResources");
	Dir.MoveChild("ContentResources\\Textures\\Skill\\DoubleJump");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Childs = Directorys[i];
		GameEngineSprite::CreateFolder(Childs.GetStringPath());
	}

	SkillRenderer1->CreateAnimation("Effect1", "Effect1", ANI_SPEED);
	SkillRenderer1->CreateAnimation("Up_Effect1", "Up_Effect1", ANI_SPEED);
	SkillRenderer2->CreateAnimation("Effect2", "Effect2", ANI_SPEED);
	SkillRenderer2->CreateAnimation("Up_Effect2", "Up_Effect2", ANI_SPEED);
	SkillAfterImageRenderer->CreateAnimation("AfterImage", "AfterImage", ANI_SPEED);
	SkillAfterImageRenderer->CreateAnimation("Up_AfterImage", "Up_AfterImage", ANI_SPEED);
}

void DoubleJump::Update(float _Delta)
{
	// 현재 항상 Update에 들어옴
	// 추후 스킬 사용시에만 업데이트 들어오도록 최적화 예정
	//if (false == IsSkillStart)
	//{
	//	return;
	//}

	ContentSkill::Update(_Delta);
	if (true == SkillRenderer1->IsUpdate() && true == SkillRenderer1->IsCurAnimationEnd())
	{
		SkillRenderer1->Off();
	}
	if (true == SkillRenderer2->IsUpdate() && true == SkillRenderer2->IsCurAnimationEnd())
	{
		SkillRenderer2->Off();
	}
	if (true == SkillAfterImageRenderer->IsUpdate() && true == SkillAfterImageRenderer->IsCurAnimationEnd())
	{
		SkillAfterImageRenderer->Off();
	}

	SkillRenderer1->Transform.SetLocalPosition(PlayerPos + Pivot);
	SkillRenderer2->Transform.SetLocalPosition(PlayerPos + Pivot);
}

