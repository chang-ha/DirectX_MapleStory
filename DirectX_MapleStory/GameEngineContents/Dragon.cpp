#include "PreCompile.h"
#include "Dragon.h"


Dragon::Dragon()
{

}

Dragon::~Dragon()
{

}

void Dragon::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void Dragon::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Dragon::Start()
{
	DragonRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	DragonRenderer->AutoSpriteSizeOn();
	DragonRenderer->SetPivotType(PivotType::Bottom);
	DragonRenderer->LeftFlip();

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
	DragonRenderer->CreateAnimation("Breath", "Lucid_Phase1_Dragon_Breath");
	DragonRenderer->ChangeAnimation("Idle");
}

void Dragon::Update(float _Delta)
{
	StateUpdate(_Delta);

	// TestCode
	if (true == GameEngineInput::IsDown('K'))
	{
		ChangeState(DragonState::Down);
	}

	if (true == GameEngineInput::IsDown('L'))
	{
		ChangeState(DragonState::Breath);
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
}

void Dragon::IdleUpdate(float _Delta)
{

}

void Dragon::DownUpdate(float _Delta)
{

}

void Dragon::UpUpdate(float _Delta)
{

}

void Dragon::BreathUpdate(float _Delta)
{

}

void Dragon::IdleEnd()
{

}

void Dragon::DownEnd()
{

}

void Dragon::UpEnd()
{

}

void Dragon::BreathEnd()
{

}