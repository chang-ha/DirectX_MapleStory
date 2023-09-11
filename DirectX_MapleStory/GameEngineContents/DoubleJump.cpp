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
			Pivot = PlayerScale.Half();
			break;
		case ActorDir::Left:
			SetScaleSkillRenderer({ 1.0f, 1.0f });
			SkillRenderer1->SetPivotType(PivotType::Left);
			SkillRenderer2->SetPivotType(PivotType::Left);
			Pivot = float4(-PlayerScale.hX(), PlayerScale.hY());
			break;
		case ActorDir::Null:
		default:
			MsgBoxAssert("�������� �ʴ� �������� ��ų�� ����� �� �����ϴ�.");
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
	SkillAfterImageRenderer->SetPivotType(PivotType::Center);

	SkillRenderer1->SetEndEvent("Effect1", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer1->Off();
		}
	);

	SkillRenderer1->SetEndEvent("Up_Effect1", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer1->Off();
		}
	);

	SkillRenderer2->SetEndEvent("Effect2", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer2->Off();
		}
	);

	SkillRenderer2->SetEndEvent("Up_Effect2", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer2->Off();
		}
	);

	SkillAfterImageRenderer->SetEndEvent("AfterImage", [&](GameEngineRenderer* _Renderer)
		{
			SkillAfterImageRenderer->Off();
			this->Off();
		}
	);

	SkillAfterImageRenderer->SetEndEvent("Up_AfterImage", [&](GameEngineRenderer* _Renderer)
		{
			SkillAfterImageRenderer->Off();
			this->Off();
		}
	);
}

void DoubleJump::Update(float _Delta)
{
	// ���� �׻� Update�� ����
	// ���� ��ų ���ÿ��� ������Ʈ �������� ����ȭ ����
	//if (false == IsSkillStart)
	//{
	//	return;
	//}

	ContentSkill::Update(_Delta);
	SkillRenderer1->Transform.SetLocalPosition(PlayerPos + Pivot);
	SkillRenderer2->Transform.SetLocalPosition(PlayerPos + Pivot);
}

