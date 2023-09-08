#include "PreCompile.h"
#include "ContentSkill.h"

ContentSkill::ContentSkill()
{

}

ContentSkill::~ContentSkill()
{

}

void ContentSkill::Start()
{
	SkillRenderer1 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Skill);
	SkillRenderer2 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Skill);
	SkillAfterImageRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Skill);
	SkillRenderer1->Off();
	SkillRenderer2->Off();
	SkillAfterImageRenderer->Off();
}

void ContentSkill::Update(float _Delta)
{

}
