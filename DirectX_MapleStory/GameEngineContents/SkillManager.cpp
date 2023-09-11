#include "PreCompile.h"
#include "SkillManager.h"
#include "ContentSkill.h"
#include "DoubleJump.h"
#include "SongOfHeaven.h"
#include "FairySpiral.h"
SkillManager* SkillManager::PlayerSkillManager = nullptr;

SkillManager::SkillManager()
{

}

SkillManager::~SkillManager()
{

}

void SkillManager::UseSkill(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("�������� �ʴ� ��ų�� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()];
	Skill->On();
	Skill->UseSkill();
}

void SkillManager::EndSkill(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("�������� �ʴ� ��ų�� �������� �߽��ϴ�.");
		return;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()];
	Skill->EndSkill();
}

bool SkillManager::IsSkillUsing(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("�������� �ʴ� ��ų�� ��������� Ȯ���Ϸ��� �߽��ϴ�.");
		return false;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()];
	return Skill->IsSkillUsing();
}


void SkillManager::LevelStart(class GameEngineLevel* _PrevLevel)
{
	PlayerSkillManager = this;
}

void SkillManager::LevelEnd(class GameEngineLevel* _NextLevel)
{

}

void SkillManager::Start()
{
	CreateSkill<DoubleJump>("DoubleJump");
	CreateSkill<SongOfHeaven>("SongOfHeaven");
	CreateSkill<FairySpiral>("FairySpiral");
}

void SkillManager::Update(float _Delta)
{

}

void SkillManager::SkillInit(std::shared_ptr<ContentSkill> _Skill)
{
	_Skill->Start();
	_Skill->Init();
	_Skill->Off();
}