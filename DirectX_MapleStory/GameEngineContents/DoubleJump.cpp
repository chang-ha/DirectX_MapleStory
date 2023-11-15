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

void DoubleJump::UseSkill()
{
	ContentSkill::UseSkill();

	On();
	SkillRenderer1->On();
	SkillRenderer2->On();
	SkillAfterImageRenderer->On();

	std::string AniDir = "";
	if (GameEngineInput::IsPress(VK_UP, this))
	{
		AniDir = "Up_";
		SkillRenderer1->SetPivotValue({ 0.5f, 0.0f });
		SkillRenderer2->SetPivotValue({ 0.5f, 0.0f });
		Pivot = float4(0, PlayerScale.hY());
	}
	else
	{
		ActorDir Dir = Player::MainPlayer->GetDir();
		switch (Dir)
		{
		case ActorDir::Right:
			SkillLeftFlip();
			SkillRenderer1->SetPivotValue({ 0.0f, 0.5f });
			SkillRenderer2->SetPivotValue({ 0.0f, 0.5f });
			Pivot = PlayerScale.Half();
			break;
		case ActorDir::Left:
			SkillRightFlip();
			SkillRenderer1->SetPivotType(PivotType::Left);
			SkillRenderer2->SetPivotType(PivotType::Left);
			Pivot = float4(-PlayerScale.hX(), PlayerScale.hY());
			break;
		case ActorDir::Null:
		default:
			MsgBoxAssert("존재하지 않는 방향으로 스킬을 사용할 수 없습니다.");
			break;
		}
	}
	SkillRenderer1->ChangeAnimation(AniDir + "Effect1", true, 0);
	SkillRenderer2->ChangeAnimation(AniDir + "Effect2", true, 0);
	SkillAfterImageRenderer->ChangeAnimation(AniDir + "AfterImage", true, 0);
	PlayerPos.Z = RenderDepth::skill;
	SkillAfterImageRenderer->Transform.SetLocalPosition(PlayerPos);
}

void DoubleJump::EndSkill()
{
	ContentSkill::EndSkill();
	Off();
}

void DoubleJump::Start() 
{
	MP = 0;
	GameEngineInput::AddInputObject(this);
	ContentSkill::Start();

	if (nullptr == GameEngineSprite::Find("DoubleJump_Effect1"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\DoubleJump");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("DoubleJump_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	SkillRenderer1->CreateAnimation("Effect1", "DoubleJump_Effect1", ANI_SPEED);
	SkillRenderer1->CreateAnimation("Up_Effect1", "DoubleJump_Up_Effect1", ANI_SPEED);
	SkillRenderer2->CreateAnimation("Effect2", "DoubleJump_Effect2", ANI_SPEED);
	SkillRenderer2->CreateAnimation("Up_Effect2", "DoubleJump_Up_Effect2", ANI_SPEED);
	SkillAfterImageRenderer->CreateAnimation("AfterImage", "DoubleJump_AfterImage", ANI_SPEED);
	SkillAfterImageRenderer->CreateAnimation("Up_AfterImage", "DoubleJump_Up_AfterImage", ANI_SPEED);
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
			EndSkill();
		}
	);
}

void DoubleJump::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	float4 Pos = PlayerPos + Pivot;
	Pos.Z = RenderDepth::skill;
	SkillRenderer1->Transform.SetLocalPosition(Pos);
	SkillRenderer2->Transform.SetLocalPosition(Pos);
}

void DoubleJump::Init()
{
	Key = 'D';
	InputTypeValue = -1;
	SkillCoolDown = 0.0f;
	UseState = PlayerState::Jump;
	ChangeState = PlayerState::Null;
}