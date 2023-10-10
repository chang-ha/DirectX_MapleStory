#include "PreCompile.h"
#include "Golem.h"

Golem::Golem()
{

}

Golem::~Golem()
{

}

void Golem::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentActor::LevelEnd(_NextLevel);
	Death();
}

void Golem::Start()
{
	ContentActor::Start();

	if (nullptr == MainSpriteRenderer)
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
		MainSpriteRenderer->AutoSpriteSizeOn();
	}

	if (nullptr == GolemCollision)
	{
		GolemCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
		GolemCollision->Transform.SetLocalScale({ 150, 200 });
		GolemCollision->Transform.SetLocalPosition({ 0, 100 });
		// GolemCollision->Off();
	}

	if (nullptr == GameEngineSprite::Find("Lucid_Phase1_Golem_Ready"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase1_Golem");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_Phase1_Golem_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	MainSpriteRenderer->CreateAnimation("Ready", "Lucid_Phase1_Golem_Ready", 0.1f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("Revive", "Lucid_Phase1_Golem_Revive", 0.1f, -1, -1, false);
	MainSpriteRenderer->CreateAnimation("Idle", "Lucid_Phase1_Golem_Idle");
	MainSpriteRenderer->CreateAnimation("Attack", "Lucid_Phase1_Golem_Attack");
	MainSpriteRenderer->CreateAnimation("Death", "Lucid_Phase1_Golem_Death");
	MainSpriteRenderer->ChangeAnimation("Ready");
	MainSpriteRenderer->SetPivotValue({0.48f, 0.8f});
	GravityOff();
	MaxGraviry = 100.0f;

	MainSpriteRenderer->SetFrameEvent("Ready", 9, [&](GameEngineSpriteRenderer*)
		{
			GravityOn();
			MoveVectorForce.Y -= 800.0f;
		}
	);
}

void Golem::Update(float _Delta)
{
	ContentActor::Update(_Delta);
	StateUpdate(_Delta);
}

void Golem::Release()
{
	ContentActor::Release();

	if (nullptr != GolemCollision)
	{
		GolemCollision->Death();
		GolemCollision = nullptr;
	}
}

void Golem::ChangeState(GolemState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case GolemState::Ready:
			break;
		case GolemState::Revive:
			break;
		case GolemState::Idle:
			break;
		case GolemState::Attack:
			break;
		case GolemState::Death:
			break;
		case GolemState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값을 끝내려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case GolemState::Ready:
			break;
		case GolemState::Revive:
			ReviveStart();
			break;
		case GolemState::Idle:
			IdleStart();
			break;
		case GolemState::Attack:
			AttackStart();
			break;
		case GolemState::Death:
			DeathStart();
			break;
		case GolemState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값을 시작하려고 했습니다.");
			break;
		}
	}

	State = _State;
}

void Golem::StateUpdate(float _Delta)
{
	switch (State)
	{
	case GolemState::Ready:
		return ReadyUpdate(_Delta);
	case GolemState::Revive:
		return ReviveUpdate(_Delta);
	case GolemState::Idle:
		return IdleUpdate(_Delta);
	case GolemState::Attack:
		return AttackUpdate(_Delta);
	case GolemState::Death:
		return DeathUpdate(_Delta);
	case GolemState::Null:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void Golem::ReadyUpdate(float _Delta)
{
	if (true == IsGround)
	{
		ChangeState(GolemState::Revive);
	}
}

void Golem::ReviveStart()
{
	// GolemCollision->On();
	MainSpriteRenderer->ChangeAnimation("Revive");
	MainSpriteRenderer->SetPivotValue({0.49f, 0.75f});
}

void Golem::IdleStart()
{
	MainSpriteRenderer->ChangeAnimation("Idle");
	MainSpriteRenderer->SetPivotValue({0.49f, 1.0f});
}

void Golem::AttackStart()
{
	MainSpriteRenderer->ChangeAnimation("Attack");
	MainSpriteRenderer->SetPivotValue({ 0.473f, 0.808f });
}

void Golem::DeathStart()
{
	MainSpriteRenderer->ChangeAnimation("Death");
	MainSpriteRenderer->SetPivotValue({ 0.52f, 0.9f });
}

void Golem::ReviveUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(GolemState::Idle);
	}
}

void Golem::IdleUpdate(float _Delta)
{

}

void Golem::AttackUpdate(float _Delta)
{
	
}

void Golem::DeathUpdate(float _Delta)
{

}