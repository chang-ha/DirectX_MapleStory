#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "Boss_Lucid_Phase1.h"
#include "PhantasmalWind.h"
#include "ContentLevel.h"
#include "Dragon.h"
#include "Lucid_Phase1.h"
#include "Player.h"
#include "MushRoom.h"
#include "Golem.h"

Boss_Lucid_Phase1::Boss_Lucid_Phase1()
{

}

Boss_Lucid_Phase1::~Boss_Lucid_Phase1()
{

}

void Boss_Lucid_Phase1::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseBossActor::LevelStart(_PrevLevel);
}

void Boss_Lucid_Phase1::LevelEnd(GameEngineLevel* _NextLevel)
{
	BaseBossActor::LevelEnd(_NextLevel);
}

void Boss_Lucid_Phase1::Start()
{
	FlowerRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	TeleportRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	FlowerRenderer->AutoSpriteSizeOn();
	TeleportRenderer->AutoSpriteSizeOn();
	BaseBossActor::Start();

	if (nullptr == GameEngineSprite::Find("Lucid_Phase1_Death"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase1");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_Phase1_" + Childs.GetFileName(), Childs.GetStringPath());
		}

		Dir.MoveParentToExistsChild("Phase1");
		Dir.MoveChild("Attack");
		GameEngineSprite::CreateFolder("Lucid_" + Dir.GetFileName(), Dir.GetStringPath());
	}

	BossRenderer->CreateAnimation("Idle", "Lucid_Phase1_Idle");
	BossRenderer->CreateAnimation("Skill1", "Lucid_Phase1_Skill1", 0.12f);
	BossRenderer->CreateAnimation("Skill2", "Lucid_Phase1_Skill2", 0.09f, -1, -1, false);
	BossRenderer->CreateAnimation("Skill3", "Lucid_Phase1_Skill3", 0.09f);
	BossRenderer->CreateAnimation("Skill4", "Lucid_Phase1_Skill4", 0.09f);
	BossRenderer->CreateAnimation("Death", "Lucid_Phase1_Death", 0.11f, -1, -1, false);
	IdleStart();

	FlowerRenderer->CreateAnimation("Flower", "Lucid_Phase1_Flower", 0.15f);
	FlowerRenderer->SetPivotType(PivotType::Bottom);
	FlowerRenderer->ChangeAnimation("Flower");
	FlowerRenderer->Transform.SetLocalPosition({ -5, 3 });
	
	TeleportRenderer->CreateAnimation("Teleport", "Lucid_Phase1_Teleport", 0.08f);
	TeleportRenderer->ChangeAnimation("Teleport");
	TeleportRenderer->SetPivotValue({0.5f, 0.8f});
	TeleportRenderer->Off();

	BossCollision->Transform.SetLocalScale({150, 400});
	BossCollision->Transform.SetLocalPosition({0, 50});

	// Render Event
	BossRenderer->SetFrameEvent("Skill1", 22, [&](GameEngineRenderer* _Renderer)
		{
			for (size_t i = 0; i < 4; i++)
			{
				std::shared_ptr<PhantasmalWind> Wind = ContentLevel::CurContentLevel->CreateActor<PhantasmalWind>(UpdateOrder::Monster);
				Wind->Transform.SetLocalPosition(Transform.GetWorldPosition() + float4{ 37, 321 });
			}
		}
	);

	BossRenderer->SetEndEvent("Skill2", [&](GameEngineRenderer* _Renderer)
		{
			Lucid_Phase1* Map = dynamic_cast<Lucid_Phase1*>(ContentLevel::CurContentLevel);
			Map->CallDragon();
		}
	);

	BossRenderer->SetFrameEvent("Skill3", 11, [&](GameEngineRenderer* _Renderer)
		{
			GameEngineRandom Random;
			Random.SetSeed(time(nullptr));
			float RandomValue = Random.RandomFloat(400.0f, 1700.0f);
			Player::MainPlayer->Transform.SetLocalPosition({ RandomValue , -500 });
			TeleportRenderer->On();
			Player::MainPlayer->MoveVectorForceReset();
			TeleportRenderer->Transform.SetWorldPosition(Player::MainPlayer->Transform.GetWorldPosition());
		}
	);

	///// TestCode
	BossRenderer->SetFrameEvent("Skill4", 10, [&](GameEngineRenderer* _Renderer)
		{
			switch (State)
			{
			case LucidState::Summon_Mush:
			{
				std::shared_ptr<MushRoom> _Mush = ContentLevel::CurContentLevel->CreateActor<MushRoom>(UpdateOrder::Monster);
				_Mush->SetDir(ActorDir::Left);
				_Mush->Transform.SetLocalPosition(float4(850, -700));

				_Mush = ContentLevel::CurContentLevel->CreateActor<MushRoom>(UpdateOrder::Monster);
				_Mush->SetDir(ActorDir::Right);
				_Mush->Transform.SetLocalPosition(float4(1150, -700));
				break;
			}
			case LucidState::Summon_Golem:
			{
				GameEngineRandom Random;
				for (size_t i = 0; i < 2; i++)
				{
					std::shared_ptr<Golem> _Golem = ContentLevel::CurContentLevel->CreateActor<Golem>(UpdateOrder::Monster);
					Random.SetSeed(reinterpret_cast<long long>(_Golem.get()));
					float RandomValue = Random.RandomFloat(400.0f, 1700.0f);
					_Golem->Transform.SetLocalPosition({ RandomValue , -450 });
				}
				break;
			}
			default:
				break;
			}
		}
	);
	/////

	BossRenderer->SetEndEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			GameEngineCore::ChangeLevel("Lucid_Next");
		}
	);

	TeleportRenderer->SetEndEvent("Teleport", [&](GameEngineRenderer* _Renderer)
		{
			TeleportRenderer->Off();
		}
	);
}

void Boss_Lucid_Phase1::Update(float _Delta)
{
	BaseBossActor::Update(_Delta);
	StateUpdate(_Delta);

	// TestCode
	if (true == GameEngineInput::IsDown('5'))
	{
		ChangeState(LucidState::Skill1);
	}

	if (true == GameEngineInput::IsDown('6'))
	{
		ChangeState(LucidState::Skill2);
	}

	if (true == GameEngineInput::IsDown('7'))
	{
		ChangeState(LucidState::Skill3);
	}

	if (true == GameEngineInput::IsDown('8'))
	{
		ChangeState(LucidState::Summon_Mush);
	}

	if (true == GameEngineInput::IsDown('9'))
	{
		ChangeState(LucidState::Idle);
	}

	if (true == GameEngineInput::IsDown('0'))
	{
		ChangeState(LucidState::Death);
	}
}

void Boss_Lucid_Phase1::ChangeState(LucidState _State)
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
		case LucidState::Skill1:
			Skill1End();
			break;
		case LucidState::Skill2:
			Skill2End();
			break;
		case LucidState::Skill3:
			Skill3End();
			break;
		case LucidState::Summon_Mush:
			Summon_MushEnd();
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
		case LucidState::Skill1:
			Skill1Start();
			break;
		case LucidState::Skill2:
			Skill2Start();
			break;
		case LucidState::Skill3:
			Skill3Start();
			break;
		case LucidState::Summon_Mush:
			Summon_MushStart();
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

void Boss_Lucid_Phase1::StateUpdate(float _Delta)
{
	switch (State)
	{
	case LucidState::Idle:
		return IdleUpdate(_Delta);
	case LucidState::Death:
		return DeathUpdate(_Delta);
	case LucidState::Skill1:
		return Skill1Update(_Delta);
	case LucidState::Skill2:
		return Skill2Update(_Delta);
	case LucidState::Skill3:
		return Skill3Update(_Delta);
	case LucidState::Summon_Mush:
		return Summon_MushUpdate(_Delta);
	case LucidState::Summon_Golem:
		return Summon_GolemUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}


void Boss_Lucid_Phase1::IdleStart()
{
	BossRenderer->SetPivotType(PivotType::Center);
	BossRenderer->Transform.SetLocalPosition({ 37, 321 });
	BossRenderer->ChangeAnimation("Idle");
	FlowerRenderer->On();
}

void Boss_Lucid_Phase1::DeathStart()
{
	BossRenderer->SetPivotType(PivotType::Bottom);
	BossRenderer->Transform.SetLocalPosition({});
	BossRenderer->ChangeAnimation("Death");
	FlowerRenderer->Off();
}

void Boss_Lucid_Phase1::Skill1Start()
{
	BossRenderer->SetPivotValue({ 0.433f, 0.677f });
	BossRenderer->ChangeAnimation("Skill1");
}

void Boss_Lucid_Phase1::Skill2Start()
{
	BossRenderer->SetPivotValue({ 0.274f, 0.706f });
	BossRenderer->ChangeAnimation("Skill2");
}

void Boss_Lucid_Phase1::Skill3Start()
{
	BossRenderer->SetPivotValue({ 0.215f, 0.648f });
	BossRenderer->ChangeAnimation("Skill3");
}

void Boss_Lucid_Phase1::Summon_MushStart()
{
	BossRenderer->SetPivotValue({ 0.452f, 0.444f });
	BossRenderer->ChangeAnimation("Skill4");
}

void Boss_Lucid_Phase1::Summon_GolemStart()
{
	BossRenderer->SetPivotValue({ 0.452f, 0.444f });
	BossRenderer->ChangeAnimation("Skill4");
}


void Boss_Lucid_Phase1::IdleUpdate(float _Delta)
{
	Skill1Cooldown -= _Delta;
	Skill2Cooldown -= _Delta;
	TeleportCooldown -= _Delta;
	MushCooldown -= _Delta;
	GolemCooldown -= _Delta;

	if (0.0f >= TeleportCooldown)
	{
		ChangeState(LucidState::Skill3);
		TeleportCooldown = Teleport_Cooldown;
	}

	if (0.0f >= Skill1Cooldown)
	{
		ChangeState(LucidState::Skill1);
		Skill1Cooldown = Skill1_Colldown;
	}

	if (0.0f >= Skill2Cooldown)
	{
		ChangeState(LucidState::Skill2);
		Skill2Cooldown = Skill2_Cooldown;
	}

	if (0.0f >= MushCooldown)
	{
		ChangeState(LucidState::Summon_Mush);
		MushCooldown = Summon_Mush_Cooldown;
	}

	if (0.0f >= GolemCooldown)
	{
		ChangeState(LucidState::Summon_Golem);
		GolemCooldown = Summon_Golem_Cooldown;
	}
}

void Boss_Lucid_Phase1::DeathUpdate(float _Delta)
{
	
}

void Boss_Lucid_Phase1::Skill1Update(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase1::Skill2Update(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase1::Skill3Update(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase1::Summon_MushUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase1::Summon_GolemUpdate(float _Delta)
{
	if (true == BossRenderer->IsCurAnimationEnd())
	{
		ChangeState(LucidState::Idle);
	}
}

void Boss_Lucid_Phase1::IdleEnd()
{

}

void Boss_Lucid_Phase1::DeathEnd()
{
	BossRenderer->Transform.SetLocalPosition({ 37, 321 });
	FlowerRenderer->On();
}

void Boss_Lucid_Phase1::Skill1End()
{

}

void Boss_Lucid_Phase1::Skill2End()
{

}

void Boss_Lucid_Phase1::Skill3End()
{

}

void Boss_Lucid_Phase1::Summon_MushEnd()
{

}

void Boss_Lucid_Phase1::Summon_GolemEnd()
{

}