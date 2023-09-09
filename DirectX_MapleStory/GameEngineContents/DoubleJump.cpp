#include "PreCompile.h"
#include "DoubleJump.h"
#include "Player.h"

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
	ActorDir Dir = Player::MainPlayer->GetDir();

	if (GameEngineInput::IsPress(VK_UP))
	{
		SkillRenderer1->ChangeAnimation("Up_Effect1");
		SkillRenderer2->ChangeAnimation("Up_Effect2");
		SkillAfterImageRenderer->ChangeAnimation("Up_AfterImage");
		SkillAfterImageRenderer->Transform.SetLocalPosition(PlayerPos);
		SkillRenderer1->SetPivotType(PivotType::Top);
		SkillRenderer2->SetPivotType(PivotType::Top);
		SkillAfterImageRenderer->SetPivotType(PivotType::Top);
		Pivot = float4(0, PlayerScale.hY());
		return;
	}
	else
	{
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
	SkillRenderer1->ChangeAnimation("Effect1");
	SkillRenderer2->ChangeAnimation("Effect2");
	SkillAfterImageRenderer->ChangeAnimation("AfterImage");
	SkillAfterImageRenderer->Transform.SetLocalPosition(PlayerPos);
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

	SkillRenderer1->CreateAnimation("Effect1", "Effect1");
	SkillRenderer1->CreateAnimation("Up_Effect1", "Up_Effect1");
	SkillRenderer2->CreateAnimation("Effect2", "Effect2");
	SkillRenderer2->CreateAnimation("Up_Effect2", "Up_Effect2");
	SkillAfterImageRenderer->CreateAnimation("AfterImage", "AfterImage");
	SkillAfterImageRenderer->CreateAnimation("Up_AfterImage", "Up_AfterImage");
}

void DoubleJump::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
	SkillRenderer1->Transform.SetLocalPosition(PlayerPos + Pivot);
	SkillRenderer2->Transform.SetLocalPosition(PlayerPos + Pivot);
}

