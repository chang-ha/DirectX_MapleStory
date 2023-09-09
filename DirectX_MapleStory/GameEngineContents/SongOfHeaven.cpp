#include "PreCompile.h"
#include "SongOfHeaven.h"
#include "Player.h"

#define PIVOT_PLUSX 20.0f
#define PIVOT_PLUSY 5.0f

SongOfHeaven::SongOfHeaven()
{
	
}

SongOfHeaven::~SongOfHeaven()
{

}

void SongOfHeaven::Init()
{

}

void SongOfHeaven::UseSkill()
{
	if (true == IsSkillStart)
	{
		return;
	}
	ContentSkill::UseSkill();

	SkillRenderer1->On();
	ActorDir Dir = Player::MainPlayer->GetDir();

	switch (Dir)
	{
	case ActorDir::Right:
		SetScaleSkillRenderer({ -1.0f, 1.0f });
		Pivot = float4(PlayerScale.hX() + PIVOT_PLUSX, PlayerScale.hY() - PIVOT_PLUSY);
		break;
	case ActorDir::Left:
		SetScaleSkillRenderer({ 1.0f, 1.0f });
		Pivot = float4(-PlayerScale.hX() - PIVOT_PLUSX, PlayerScale.hY() - PIVOT_PLUSY);
		break;
	case ActorDir::Null:
	default:
		break;
	}
	SkillRenderer1->ChangeAnimation("Ready");
}

void SongOfHeaven::Start()
{
	ContentSkill::Start();

	GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentResources");
	Dir.MoveChild("ContentResources\\Textures\\Skill\\SongOfHeaven");
	std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

	for (size_t i = 0; i < Directorys.size(); i++)
	{
		GameEngineDirectory& Childs = Directorys[i];
		GameEngineSprite::CreateFolder(Childs.GetStringPath());
	}

	SkillRenderer1->CreateAnimation("Ready", "Ready", 0.08f, -1, -1, false);
	SkillRenderer1->CreateAnimation("Attack", "Attack");
	SkillRenderer1->CreateAnimation("End", "End", 0.08f, -1, -1, false);
}

void SongOfHeaven::Update(float _Delta)
{
	ContentSkill::Update(_Delta);

	if (true == SkillRenderer1->IsUpdate() && true == IsSkillEnd && true == SkillRenderer1->IsCurAnimationEnd())
	{
		SkillRenderer1->Off();
	}
	else if (true == IsSkillEnd)
	{
		SkillRenderer1->ChangeAnimation("End");
	}

	if (false == IsSkillStart)
	{
		return;
	}

	if (true == SkillRenderer1->IsCurAnimationEnd())
	{
		Pivot = float4(0, PlayerScale.hY());
		SkillRenderer1->ChangeAnimation("Attack");
	}
	PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
	SkillRenderer1->Transform.SetLocalPosition(PlayerPos + Pivot);
}