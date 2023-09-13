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
	PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
	PlayerScale = Player::MainPlayer->GetPlayerScale();
}

void ContentSkill::SetScaleSkillRenderer(const float4& _Scale)
{
	// 좌우이미지 변경용
	SkillRenderer1->Transform.SetLocalScale(_Scale);
	SkillRenderer2->Transform.SetLocalScale(_Scale);
	SkillAfterImageRenderer->Transform.SetLocalScale(_Scale);
}