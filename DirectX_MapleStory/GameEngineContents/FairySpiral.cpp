#include "PreCompile.h"
#include "FairySpiral.h"
#include "Player.h"

FairySpiral::FairySpiral()
{
	
}

FairySpiral::~FairySpiral()
{

}

void FairySpiral::Init()
{
	
}

void FairySpiral::UseSkill()
{
	ContentSkill::UseSkill();
	SkillRenderer1->On();

	ActorDir Dir = Player::MainPlayer->GetDir();
	switch (Dir)
	{
	case ActorDir::Right:
		SkillRenderer1->SetPivotType(PivotType::Right);
		SetScaleSkillRenderer({ -1.0f, 1.0f });
		break;
	case ActorDir::Left:
		SkillRenderer1->SetPivotType(PivotType::Right);
		SetScaleSkillRenderer({ 1.0f, 1.0f });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향으로 스킬을 사용할 수 없습니다.");
		break;
	}

	SkillRenderer1->ChangeAnimation("Attack", true, 0);
}

void FairySpiral::EndSkill()
{
	ContentSkill::EndSkill();
}

void FairySpiral::Start()
{
	ContentSkill::Start();
	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentResources");
	Dir.MoveChild("ContentResources\\Textures\\Skill\\FairySprial");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Childs = Directorys[i];
		GameEngineSprite::CreateFolder("FairySprial_" + Childs.GetFileName(), Childs.GetStringPath());
	}

	SkillRenderer1->CreateAnimation("Attack", "FairySprial_Attack", 0.06f);
	SkillRenderer1->SetEndEvent("Attack", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer1->Off();
			EndSkill();
		}
	);
}

void FairySpiral::Update(float _Delta)
{
	ContentSkill::Update(_Delta);
	SkillRenderer1->Transform.SetLocalPosition(PlayerPos + Pivot);
}