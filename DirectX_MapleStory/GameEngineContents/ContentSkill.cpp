#include "PreCompile.h"
#include "ContentSkill.h"
#include "Player.h"

ContentSkill::ContentSkill()
{

}

ContentSkill::~ContentSkill()
{

}

void ContentSkill::LevelStart(GameEngineLevel* _PrevLevel)
{
	
}

void ContentSkill::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void ContentSkill::Start()
{
	SkillRenderer1 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Skill);
	SkillRenderer2 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Skill);
	SkillAfterImageRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Skill);
	SkillRenderer1->AutoSpriteSizeOn();
	SkillRenderer2->AutoSpriteSizeOn();
	SkillAfterImageRenderer->AutoSpriteSizeOn();
	SkillRenderer1->Off();
	SkillRenderer2->Off();
	SkillAfterImageRenderer->Off();
}

void ContentSkill::Update(float _Delta)
{
	PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
}

void ContentSkill::UseSkill()
{
	IsSkillStart = true;
	IsSkillEnd = false;
	PlayerDir = Player::MainPlayer->GetDir();
	PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
	PlayerScale = Player::MainPlayer->GetPlayerScale();
}

void ContentSkill::SkillLeftFlip()
{
	SkillRenderer1->LeftFlip();
	SkillRenderer2->LeftFlip();
	SkillAfterImageRenderer->LeftFlip();
}

void ContentSkill::SkillRightFlip()
{
	SkillRenderer1->RightFlip();
	SkillRenderer2->RightFlip();
	SkillAfterImageRenderer->RightFlip();
}
