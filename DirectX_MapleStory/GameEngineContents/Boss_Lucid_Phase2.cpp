#include "PreCompile.h"
#include "Boss_Lucid_Phase2.h"
#include "PhantasmalWind.h"
#include "ContentLevel.h"
#include "Lucid_Phase2.h"
#include "Lucid_BodySlam.h"

Boss_Lucid_Phase2::Boss_Lucid_Phase2()
{

}

Boss_Lucid_Phase2::~Boss_Lucid_Phase2()
{

}

void Boss_Lucid_Phase2::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseBossActor::LevelStart(_PrevLevel);

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

	if (nullptr == GameEngineSprite::Find("Lucid_BodySlam"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase2_BodySlam");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_BodySlam_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	BossRenderer->CreateAnimation("Idle", "Lucid_Phase2_Idle");
	BossRenderer->CreateAnimation("Death", "Lucid_Phase2_Death");
	BossRenderer->CreateAnimation("PhantasmalWind", "Lucid_Phase2_PhantasmalWind");
	BossRenderer->CreateAnimation("Summon_Dragon", "Lucid_Phase2_Summon_Dragon");
	BossRenderer->CreateAnimation("Laser", "Lucid_Phase2_Laser", 0.09f, -1, -1, false);
	BossRenderer->CreateAnimation("BodySlam", "Lucid_Phase2_BodySlam");
	BossRenderer->ChangeAnimation("Idle");
	IdleStart();

	BossCollision->Transform.SetLocalScale({ 70, 130 });
	BossCollision->Transform.SetLocalPosition({ -5, 60 });

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

	// Laser Render Event
	BossRenderer->SetFrameEvent("Laser", 16, [&](GameEngineRenderer* _Renderer)
		{
			BossCollision->Off();
		}
	);

	BossRenderer->SetFrameEvent("Laser", 32, [&](GameEngineRenderer* _Renderer)
		{
			Lucid_Phase2* Map = dynamic_cast<Lucid_Phase2*>(ContentLevel::CurContentLevel);
			Map->LucidLaserOff();
		}
	);

	BossRenderer->SetFrameEvent("Laser", 37, [&](GameEngineRenderer* _Renderer)
		{
			BossCollision->On();
		}
	);
	//

	// BodySlam Render Evnet
	BossRenderer->SetFrameEvent("BodySlam", 3, [&](GameEngineRenderer* _Renderer)
		{
			BossCollision->Off();
		}
	);

	BossRenderer->SetFrameEvent("BodySlam", 14, [&](GameEngineRenderer* _Renderer)
		{
			ContentLevel::CurContentLevel->CreateActor<Lucid_BodySlam>(UpdateOrder::Monster);
		}
	);

	BossRenderer->SetFrameEvent("BodySlam", 25, [&](GameEngineRenderer* _Renderer)
		{
			BossCollision->On();
		}
	);
	//

	BossRenderer->SetEndEvent("Summon_Dragon", [&](GameEngineRenderer* _Renderer)
		{
			Lucid_Phase2* Map = dynamic_cast<Lucid_Phase2*>(ContentLevel::CurContentLevel);
			Map->CallDragon();
		}
	);

	/// Animation Detail
	std::shared_ptr<GameEngineFrameAnimation> _Animation = BossRenderer->FindAnimation("Laser");
	_Animation->Inter[30] = 15.0f;

	_Animation = BossRenderer->FindAnimation("BodySlam");
	_Animation->Inter[14] = 20.0f;
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

	if (true == GameEngineInput::IsDown('7', this))
	{
		ChangeState(LucidState::Laser);
	}

	if (true == GameEngineInput::IsDown('8', this))
	{
		ChangeState(LucidState::BodySlam);
	}

	if (true == GameEngineInput::IsDown('0', this))
	{
		ChangeState(LucidState::Death);
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
		case LucidState::Laser:
			LaserEnd();
			break;
		case LucidState::BodySlam:
			BodySlamEnd();
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
		case LucidState::Laser:
			LaserStart();
			break;
		case LucidState::BodySlam:
			BodySlamStart();
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
	case LucidState::Laser:
		return LaserUpdate(_Delta);
	case LucidState::BodySlam:
		return BodySlamUpdate(_Delta);
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
	BossRenderer->ChangeAnimation("Death");

	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.463f, 0.62f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.537f, 0.62f });
		BossRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
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

void Boss_Lucid_Phase2::LaserStart()
{
	BossRenderer->ChangeAnimation("Laser");
	Lucid_Phase2* Map = dynamic_cast<Lucid_Phase2*>(ContentLevel::CurContentLevel);
	Map->LucidLaserOn();

	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.483f, 0.75f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.517f, 0.75f });
		BossRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void Boss_Lucid_Phase2::BodySlamStart()
{
	BossRenderer->ChangeAnimation("BodySlam");
	// Lucid_Phase2* Map = dynamic_cast<Lucid_Phase2*>(ContentLevel::CurContentLevel);
	// Map->LucidLaserOn();

	switch (Dir)
	{
	case ActorDir::Right:
		BossRenderer->SetPivotValue({ 0.375f, 0.566f });
		BossRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		BossRenderer->SetPivotValue({ 0.625f, 0.566f });
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

void Boss_Lucid_Phase2::LaserUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase2::BodySlamUpdate(float _Delta)
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
void Boss_Lucid_Phase2::DeathEnd()
{
}

void Boss_Lucid_Phase2::PhantasmalWindEnd()
{

}

void Boss_Lucid_Phase2::LaserEnd()
{

}

void Boss_Lucid_Phase2::BodySlamEnd()
{

}

void Boss_Lucid_Phase2::Summon_DragonEnd()
{

}

void Boss_Lucid_Phase2::Summon_GolemEnd()
{

}
