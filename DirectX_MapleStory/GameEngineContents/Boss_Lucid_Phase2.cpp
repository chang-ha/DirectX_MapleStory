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
	BaseBossActor::Start();
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