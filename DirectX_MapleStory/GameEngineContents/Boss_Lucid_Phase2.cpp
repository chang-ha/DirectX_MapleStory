#include "PreCompile.h"
#include "Boss_Lucid_Phase2.h"
#include "PhantasmalWind.h"
#include "ContentLevel.h"
#include "Lucid_Phase2.h"

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
	PhantasmalWind::AllAngleValue = true;

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
	BossRenderer->CreateAnimation("PhantasmalWind", "Lucid_Phase2_PhantasmalWind");
	BossRenderer->CreateAnimation("Summon_Dragon", "Lucid_Phase2_Summon_Dragon");
	BossRenderer->ChangeAnimation("Idle");
	IdleStart();

	BossCollision->Transform.SetLocalScale({ 70, 130 });
	BossCollision->Transform.SetLocalPosition({ -5, 60});

	// Renderer Event
	BossRenderer->SetFrameEvent("PhantasmalWind", 22, [&](GameEngineRenderer* _Renderer)
		{
			for (size_t i = 0; i < 6; i++)
			{
				std::shared_ptr<PhantasmalWind> Wind = ContentLevel::CurContentLevel->CreateActor<PhantasmalWind>(UpdateOrder::Monster);
				Wind->Transform.SetLocalPosition(Transform.GetWorldPosition() + float4{ 0, 50 });
				Wind->SetSpeed(200.0f);
			}
		}
	);

	BossRenderer->SetEndEvent("Summon_Dragon", [&](GameEngineRenderer* _Renderer)
		{
			Lucid_Phase2* Map = dynamic_cast<Lucid_Phase2*>(ContentLevel::CurContentLevel);
			Map->CallDragon();
		}
	);
}

void Boss_Lucid_Phase2::Update(float _Delta)
{
	BaseBossActor::Update(_Delta);
	StateUpdate(_Delta);

	if (true == GameEngineInput::IsDown('4', this))
	{
		ChangeState(LucidState::Idle);
	}

	if (true == GameEngineInput::IsDown('5',this))
	{
		ChangeState(LucidState::PhantasmalWind);
	}

	if (true == GameEngineInput::IsDown('6', this))
	{
		ChangeState(LucidState::Summon_Dragon);
	}
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
		case LucidState::PhantasmalWind:
			PhantasmalWindEnd();
			break;
		case LucidState::Summon_Dragon:
			Summon_DragonEnd();
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
		case LucidState::PhantasmalWind:
			PhantasmalWindStart();
			break;
		case LucidState::Summon_Dragon:
			Summon_DragonStart();
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
	case LucidState::PhantasmalWind:
		return PhantasmalWindUpdate(_Delta);
	case LucidState::Summon_Dragon:
		return Summon_DragonUpdate(_Delta);
	case LucidState::Summon_Golem:
		return Summon_GolemUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

///// Start

void Boss_Lucid_Phase2::IdleStart()
{
	BossRenderer->ChangeAnimation("Idle");

	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.33f, 0.63f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.67f, 0.63f });
		BossRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void Boss_Lucid_Phase2::DeathStart()
{
}

void Boss_Lucid_Phase2::PhantasmalWindStart()
{
	BossRenderer->ChangeAnimation("PhantasmalWind");

	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.47f, 0.68f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.53f, 0.68f });
		BossRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void Boss_Lucid_Phase2::Summon_DragonStart()
{
	BossRenderer->ChangeAnimation("Summon_Dragon");

	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.595f, 0.758f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.405f, 0.758f });
		BossRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void Boss_Lucid_Phase2::Summon_GolemStart()
{
}

///// Update

void Boss_Lucid_Phase2::IdleUpdate(float _Delta)
{
}

void Boss_Lucid_Phase2::DeathUpdate(float _Delta)
{

}

void Boss_Lucid_Phase2::PhantasmalWindUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase2::Summon_DragonUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase2::Summon_GolemUpdate(float _Delta)
{
}

///// End

void Boss_Lucid_Phase2::IdleEnd()
{

}

void Boss_Lucid_Phase2::PhantasmalWindEnd()
{

}

void Boss_Lucid_Phase2::DeathEnd()
{
}

void Boss_Lucid_Phase2::Summon_DragonEnd()
{

}

void Boss_Lucid_Phase2::Summon_GolemEnd()
{

}
