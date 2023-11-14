#include "PreCompile.h"
#include "ContentSkill.h"
#include "Player.h"


ContentSkill::ContentSkill()
{

}

ContentSkill::~ContentSkill()
{

}

void ContentSkill::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void ContentSkill::Start()
{
	if (nullptr == SkillRenderer1)
	{
		SkillRenderer1 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::SKILL);
		SkillRenderer1->Transform.SetLocalPosition({0, 0, RenderDepth::skill});
		SkillRenderer1->AutoSpriteSizeOn();
		SkillRenderer1->Off();
	}

	if (nullptr == SkillRenderer2)
	{
		SkillRenderer2 = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::SKILL);
		SkillRenderer2->Transform.SetLocalPosition({ 0, 0, RenderDepth::skill });
		SkillRenderer2->AutoSpriteSizeOn();
		SkillRenderer2->Off();
	}

	if (nullptr == SkillAfterImageRenderer)
	{
		SkillAfterImageRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::SKILL);
		SkillAfterImageRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::skill });
		SkillAfterImageRenderer->AutoSpriteSizeOn();
		SkillAfterImageRenderer->Off();
	}
}

void ContentSkill::Update(float _Delta)
{
	PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
	PlayerPos.Z = 0.0f;

	SkillRenderer1->GetColorData().MulColor.A = GlobalValue::SkillEffectAlpha;
	SkillRenderer2->GetColorData().MulColor.A = GlobalValue::SkillEffectAlpha;
	SkillAfterImageRenderer->GetColorData().MulColor.A = GlobalValue::SkillEffectAlpha;
}

void ContentSkill::Release()
{
	if (nullptr != SkillRenderer1)
	{
		SkillRenderer1->Death();
		SkillRenderer1 = nullptr;
	}

	if (nullptr != SkillRenderer2)
	{
		SkillRenderer2->Death();
		SkillRenderer2 = nullptr;
	}

	if (nullptr != SkillAfterImageRenderer)
	{
		SkillAfterImageRenderer->Death();
		SkillAfterImageRenderer = nullptr;
	}
}

void ContentSkill::UseSkill()
{
	IsSkillStart = true;
	IsSkillEnd = false;
	PlayerDir = Player::MainPlayer->GetDir();
	PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
	PlayerScale = Player::MainPlayer->GetPlayerScale();
	SkillCurCoolDown = SkillCoolDown;
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
