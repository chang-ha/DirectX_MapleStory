#include "PreCompile.h"
#include "SkillManager.h"
#include "ContentSkill.h"
#include "DoubleJump.h"
#include "SongOfHeaven.h"

SkillManager* SkillManager::PlayerSkillManager = nullptr;

SkillManager::SkillManager()
{

}

SkillManager::~SkillManager()
{

}

void SkillManager::UseSkill(std::string_view _SkillName)
{
	if (false == AllSkills.contains(_SkillName.data()))
	{
		MsgBoxAssert("�������� �ʴ� ��ų�� ����Ϸ��� �߽��ϴ�.");
		return;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[_SkillName.data()];
	Skill->On();
	Skill->UseSkill();
}

void SkillManager::EndSkill(std::string_view _SkillName)
{
	if (false == AllSkills.contains(_SkillName.data()))
	{
		MsgBoxAssert("�������� �ʴ� ��ų�� �������� �߽��ϴ�.");
		return;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[_SkillName.data()];
	Skill->EndSkill();
}

bool SkillManager::IsSkillUsing(std::string_view _SkillName)
{
	if (false == AllSkills.contains(_SkillName.data()))
	{
		MsgBoxAssert("�������� �ʴ� ��ų�� ��������� Ȯ���Ϸ��� �߽��ϴ�.");
		return false;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[_SkillName.data()];
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