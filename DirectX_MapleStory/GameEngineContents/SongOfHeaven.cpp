#include "PreCompile.h"
#include "SongOfHeaven.h"
#include "Player.h"
#include "Arrow.h"

#define READY_ANI_SPEED 0.03f
#define ATTACK_ANI_SPEED 0.05f

#define PIVOT_PLUSX 20.0f
#define PIVOT_PLUSY 5.0f

#define PIVOT2_PLUSX 60.0f

SongOfHeaven::SongOfHeaven()
{
	
}

SongOfHeaven::~SongOfHeaven()
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
		MsgBoxAssert("존재하지 않는 방향으로 스킬을 사용할 수 없습니다.");
		break;
	}
	SkillRenderer1->ChangeAnimation("Ready");
}

void SongOfHeaven::EndSkill()
{
	ContentSkill::EndSkill();
	SkillRenderer1->ChangeAnimation("End");
	ActorDir Dir = Player::MainPlayer->GetDir();
	switch (Dir)
	{
	case ActorDir::Right:
		Pivot = float4(PlayerScale.hX() + PIVOT2_PLUSX, PlayerScale.hY());
		break;
	case ActorDir::Left:
		Pivot = float4(-PlayerScale.hX() - PIVOT2_PLUSX, PlayerScale.hY());
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향으로 스킬을 사용할 수 없습니다.");
		break;
	}
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
		GameEngineSprite::CreateFolder("SongOfHeaven_" + Childs.GetFileName(), Childs.GetStringPath());
	}

	SkillRenderer1->CreateAnimation("Ready", "SongOfHeaven_Ready", READY_ANI_SPEED);
	SkillRenderer1->CreateAnimation("Attack", "SongOfHeaven_Attack", ATTACK_ANI_SPEED);
	SkillRenderer1->CreateAnimation("Loop_Attack", "SongOfHeaven_Attack", ATTACK_ANI_SPEED, 11, 16, true);
	SkillRenderer1->CreateAnimation("End", "SongOfHeaven_End", 0.08f);
	SkillRenderer1->SetEndEvent("Ready", [&](GameEngineRenderer* _Renderer) 
		{
			Pivot2 = float4(0, PlayerScale.hY());
			SkillRenderer1->ChangeAnimation("Attack");
		});

	SkillRenderer1->SetEndEvent("Attack", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer1->ChangeAnimation("Loop_Attack");
		});

	SkillRenderer1->SetEndEvent("End", [&](GameEngineRenderer* _Renderer)
		{
			SkillRenderer1->Off();
			this->Off();
		});
}

void SongOfHeaven::Update(float _Delta)
{
	ContentSkill::Update(_Delta);

	if (true == SkillRenderer1->IsCurAnimation("Attack") || true == SkillRenderer1->IsCurAnimation("Loop_Attack"))
	{
		ShootDps -= _Delta;
		if (0.0f >= ShootDps)
		{
			ShootDps = 0.12f;
			GetLevel()->CreateActor<Arrow>(UpdateOrder::Arrow);
		}
	}

	if (true == SkillRenderer1->IsCurAnimation("Attack") || true == SkillRenderer1->IsCurAnimation("Loop_Attack"))
	{
		SkillRenderer1->Transform.SetLocalPosition(PlayerPos + Pivot2);
	}
	else
	{
		SkillRenderer1->Transform.SetLocalPosition(PlayerPos + Pivot);
	}
}