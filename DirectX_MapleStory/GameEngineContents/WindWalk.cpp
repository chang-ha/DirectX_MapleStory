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
	
	ActorDir Dir = Player::MainPlayer->GetDir();

	switch (Dir)
	{
	case ActorDir::Right:
		SkillRenderer1->LeftFlip();
		SkillAfterImageRenderer->LeftFlip();
		SkillRenderer1->SetPivotValue(float4(0.75f, 0.6f));
		break;
	case ActorDir::Left:
		SkillRenderer1->RightFlip();
		SkillAfterImageRenderer->RightFlip();
		SkillRenderer1->SetPivotValue(float4(0.75f, 0.6f));
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	SkillRenderer1->ChangeAnimation("Effect1", true);
	SkillAfterImageRenderer->ChangeAnimation("AfterImage", true);
	SkillAfterImageRenderer->Transform.SetLocalPosition(PlayerPos);
}

void WindWalk::EndSkill()
{
	ContentSkill::EndSkill();
}

void WindWalk::Start()
{
	ContentSkill::Start();
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentResources");
	Dir.MoveChild("ContentResources\\Textures\\Skill\\WindWalk");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Childs = Directorys[i];
		GameEngineSprite::CreateFolder("WindWalk_" + Childs.GetFileName(), Childs.GetStringPath());
	}

	SkillRenderer1->CreateAnimation("Effect1", "WindWalk_Effect1", ANI_SPEED);
	SkillAfterImageRenderer->CreateAnimation("AfterImage", "WindWalk_AfterImage", ANI_SPEED);
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
	SkillRenderer1->Transform.SetLocalPosition(PlayerPos);

}
