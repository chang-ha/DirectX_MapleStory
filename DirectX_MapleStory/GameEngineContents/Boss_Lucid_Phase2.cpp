#include "PreCompile.h"
#include "Boss_Lucid_Phase2.h"

Boss_Lucid_Phase2::Boss_Lucid_Phase2()
{

}

Boss_Lucid_Phase2::~Boss_Lucid_Phase2()
{

}

void Boss_Lucid_Phase2::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseBossActor::LevelStart(_PrevLevel);
}

void Boss_Lucid_Phase2::LevelEnd(GameEngineLevel* _NextLevel)
{
	BaseBossActor::LevelEnd(_NextLevel);
}

void Boss_Lucid_Phase2::Start()
{
	GameEngineInput::AddInputObject(this);

	BaseBossActor::Start();

	if (nullptr == GameEngineSprite::Find("Lucid_Phase2_Death"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase2");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_Phase2_" + Childs.GetFileName(), Childs.GetStringPath());
		}

		if (nullptr == GameEngineSprite::Find("Lucid_Attack"))
		{
			Dir.MoveParentToExistsChild("Phase2");
			Dir.MoveChild("Attack");
			GameEngineSprite::CreateFolder("Lucid_" + Dir.GetFileName(), Dir.GetStringPath());
		}
	}

	BossRenderer->CreateAnimation("Idle", "Lucid_Phase2_Idle");
	BossRenderer->ChangeAnimation("Idle");
}

void Boss_Lucid_Phase2::Update(float _Delta)
{
	BaseBossActor::Update(_Delta);
	StateUpdate(_Delta);
}


void Boss_Lucid_Phase2::ChangeState(LucidState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case LucidState::Idle:
			IdleEnd();
			break;
		case LucidState::Death:
			DeathEnd();
			break;
		case LucidState::Summon_Golem:
			Summon_GolemEnd();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 변경하려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case LucidState::Idle:
			IdleStart();
			break;
		case LucidState::Death:
			DeathStart();
			break;
		case LucidState::Summon_Golem:
			Summon_GolemStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Boss_Lucid_Phase2::StateUpdate(float _Delta)
{
	switch (State)
	{
	case LucidState::Idle:
		return IdleUpdate(_Delta);
	case LucidState::Death:
		return DeathUpdate(_Delta);
	case LucidState::Summon_Golem:
		return Summon_GolemUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}



void Boss_Lucid_Phase2::IdleStart()
{
}

void Boss_Lucid_Phase2::DeathStart()
{
}

void Boss_Lucid_Phase2::Summon_GolemStart()
{
}


void Boss_Lucid_Phase2::IdleUpdate(float _Delta)
{
}

void Boss_Lucid_Phase2::DeathUpdate(float _Delta)
{

}

void Boss_Lucid_Phase2::Summon_GolemUpdate(float _Delta)
{
}

void Boss_Lucid_Phase2::IdleEnd()
{

}

void Boss_Lucid_Phase2::DeathEnd()
{
}

void Boss_Lucid_Phase2::Summon_GolemEnd()
{

}