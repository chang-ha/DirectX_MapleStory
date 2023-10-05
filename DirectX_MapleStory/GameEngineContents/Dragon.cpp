#include "PreCompile.h"
#include "Dragon.h"

#define DELAY_TIME 1.0f

Dragon::Dragon()
{

}

Dragon::~Dragon()
{

}

void Dragon::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Dragon::Start()
{
	BreathRenderers.resize(7);
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		BreathRenderers[i] = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MonsterAttack);
	}

	DragonRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	DragonRenderer->AutoSpriteSizeOn();
	DragonRenderer->SetPivotType(PivotType::Bottom);

	if (nullptr == GameEngineSprite::Find("Lucid_Phase1_Dragon_Move"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase1_Dragon");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_Phase1_Dragon_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	DragonRenderer->CreateAnimation("Idle", "Lucid_Phase1_Dragon_Move", 0, 0, 0, false);
	DragonRenderer->CreateAnimation("Move", "Lucid_Phase1_Dragon_Move", 0.15f);
	DragonRenderer->CreateAnimation("Breath", "Lucid_Phase1_Dragon_Breath", 0.15f, 0, 35, false);
	IdleStart();

	// Breath
	DragonRenderer->SetFrameEvent("Breath", 10, [&](GameEngineSpriteRenderer*)
		{
			BreathOn();
			switch (Dir)
			{
			case ActorDir::Right:
				DragonRenderer->SetPivotValue({ 0.65f, 0.8f });
				break;
			case ActorDir::Left:
				DragonRenderer->SetPivotValue({ 0.35f, 0.8f });
				break;
			case ActorDir::Null:
			default:
				MsgBoxAssert("존재하지 않는 방향입니다.");
				break;
			}
		}
	);

	DragonRenderer->SetFrameEvent("Breath", 33, [&](GameEngineSpriteRenderer*)
		{
			BreathOff();
		}
	);

	// Create Animation
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		BreathRenderers[i]->CreateAnimation("Attack", "Lucid_Phase1_Dragon_Attack", 0.15f);
		BreathRenderers[i]->ChangeAnimation("Attack");
		BreathRenderers[i]->AutoSpriteSizeOn();
		BreathRenderers[i]->Off();
	}

	Delay = DELAY_TIME;
}

void Dragon::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Dragon::SetDir(ActorDir _Dir)
{
	Dir = _Dir;
	switch (Dir)
	{
		break;
	case ActorDir::Right:
		DragonRenderer->LeftFlip();
		RightBreath();
		break;
	case ActorDir::Left:
		DragonRenderer->RightFlip();
		LeftBreath();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void Dragon::ChangeState(DragonState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case DragonState::Idle:
			IdleEnd();
			break;
		case DragonState::Down:
			DownEnd();
			break;
		case DragonState::Up:
			UpEnd();
			break;
		case DragonState::Breath:
			BreathEnd();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 변경하려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case DragonState::Idle:
			IdleStart();
			break;
		case DragonState::Down:
			DownStart();
			break;
		case DragonState::Up:
			UpStart();
			break;
		case DragonState::Breath:
			BreathStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Dragon::StateUpdate(float _Delta)
{
	switch (State)
	{
	case DragonState::Idle:
		return IdleUpdate(_Delta);
	case DragonState::Down:
		return DownUpdate(_Delta);
	case DragonState::Up:
		return UpUpdate(_Delta);
	case DragonState::Breath:
		return BreathUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void Dragon::IdleStart()
{
	DragonRenderer->ChangeAnimation("Idle");
}

void Dragon::DownStart()
{
	DragonRenderer->ChangeAnimation("Move");
}

void Dragon::UpStart()
{
	DragonRenderer->ChangeAnimation("Move");
}

void Dragon::BreathStart()
{
	DragonRenderer->ChangeAnimation("Breath");
	switch (Dir)
	{
	case ActorDir::Right:
		DragonRenderer->SetPivotValue({ 0.63f, 0.88f });
		break;
	case ActorDir::Left:
		DragonRenderer->SetPivotValue({ 0.37f, 0.88f });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void Dragon::IdleUpdate(float _Delta)
{

}

void Dragon::DownUpdate(float _Delta)
{
	if (0.0f >= Delay)
	{
		ChangeState(DragonState::Breath);
		Delay = DELAY_TIME;
	}

	if (-750.0f > Transform.GetWorldPosition().Y)
	{
		Transform.SetLocalPosition({ Transform.GetWorldPosition().X, -750.0f });
		Delay -= _Delta;
	}

	Transform.AddLocalPosition({0, -Speed * _Delta});
}

void Dragon::UpUpdate(float _Delta)
{
	Delay -= _Delta;
	if (0.0f >= Delay)
	{
		Transform.AddLocalPosition({ 0, Speed * _Delta });
	}

	if (200.0f <= Transform.GetWorldPosition().Y)
	{
		Transform.SetLocalPosition({ Transform.GetWorldPosition().X, 200.0f });
		ChangeState(DragonState::Idle);
	}
}

void Dragon::BreathUpdate(float _Delta)
{
	if (true == DragonRenderer->IsCurAnimationEnd())
	{
		ChangeState(DragonState::Up);
	}
}

void Dragon::IdleEnd()
{

}

void Dragon::DownEnd()
{

}

void Dragon::UpEnd()
{
	Delay = DELAY_TIME;
}

void Dragon::BreathEnd()
{
	DragonRenderer->SetPivotType(PivotType::Bottom);
}

void Dragon::BreathOn()
{
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		BreathRenderers[i]->On();
	}
}

void Dragon::BreathOff()
{
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		BreathRenderers[i]->Off();
	}
}

void Dragon::RightBreath()
{
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		BreathRenderers[i]->Transform.SetLocalPosition({ 380 + 190 * static_cast<float>(i), -120});
		BreathRenderers[i]->LeftFlip();
		BreathRenderers[i]->SetPivotValue({ 1.0f, 1.0f });
	}
}

void Dragon::LeftBreath()
{
	for (size_t i = 0; i < BreathRenderers.size(); i++)
	{
		BreathRenderers[i]->Transform.SetLocalPosition({ -380 - 190 * static_cast<float>(i), -120 });
		BreathRenderers[i]->RightFlip();
		BreathRenderers[i]->SetPivotValue({ 0.0f, 1.0f });
	}
}