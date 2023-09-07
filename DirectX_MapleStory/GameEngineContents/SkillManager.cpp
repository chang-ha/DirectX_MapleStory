#include "PreCompile.h"
#include "SkillManager.h"
#include "ContentSkill.h"
#include "DoubleJump.h"

SkillManager* SkillManager::PlayerSkillManager = nullptr;

SkillManager::SkillManager()
{

}

SkillManager::~SkillManager()
{

}

void SkillManager::Start()
{
	PlayerSkillManager = this;
	CreateSkill<DoubleJump>("DoubleJump");
}

void SkillManager::Update(float _Delta)
{

}

void SkillManager::SkillInit(std::shared_ptr<ContentSkill> _Skill)
{
	_Skill->Init();
}