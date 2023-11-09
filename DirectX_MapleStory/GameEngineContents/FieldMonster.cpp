#include "PreCompile.h"
#include "FieldMonster.h"

FieldMonster::FieldMonster()
{

}

FieldMonster::~FieldMonster()
{

}

void FieldMonster::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentActor::LevelEnd(_NextLevel);
}

void FieldMonster::Start()
{
	ContentActor::Start();

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::monster});

	MonsterCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	MonsterCollision->Transform.SetLocalScale({1, 1});
	// AttackFunction;
	GameEngineInput::AddInputObject(this);
}

void FieldMonster::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1', this))
	{
		ChangeState(FieldMonsterState::Ready);
	}

	if (true == GameEngineInput::IsDown('2', this))
	{
		ChangeState(FieldMonsterState::Idle);
	}

	if (true == GameEngineInput::IsDown('3', this))
	{
		ChangeState(FieldMonsterState::Move);
	}

	if (true == GameEngineInput::IsDown('4', this))
	{
		ChangeState(FieldMonsterState::Attack);
	}

	if (true == GameEngineInput::IsDown('5', this))
	{
		ChangeState(FieldMonsterState::Death);
	}
	ContentActor::Update(_Delta);
	StateUpdate(_Delta);
}

void FieldMonster::Release()
{
	ContentActor::Release();
}

void FieldMonster::ChangeState(FieldMonsterState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case FieldMonsterState::Ready:
			ReadyEnd();
			break;
		case FieldMonsterState::Idle:
			IdleEnd();
			break;
		case FieldMonsterState::Move:
			MoveEnd();
			break;
		case FieldMonsterState::Attack:
			AttackEnd();
			break;
		case FieldMonsterState::Death:
			DeathEnd();
			break;
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 변경하려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case FieldMonsterState::Ready:
			ReadyStart();
			break;
		case FieldMonsterState::Idle:
			IdleStart();
			break;
		case FieldMonsterState::Move:
			MoveStart();
			break;
		case FieldMonsterState::Attack:
			AttackStart();
			break;
		case FieldMonsterState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void FieldMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case FieldMonsterState::Ready:
		return ReadyUpdate(_Delta);
	case FieldMonsterState::Idle:
		return IdleUpdate(_Delta);
	case FieldMonsterState::Move:
		return MoveUpdate(_Delta);
	case FieldMonsterState::Attack:
		return AttackUpdate(_Delta);
	case FieldMonsterState::Death:
		return DeathUpdate(_Delta);
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void FieldMonster::Init(std::string_view _MonsterName)
{
	if (nullptr == GameEngineSprite::Find(std::string(_MonsterName) + "_Death"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Monster\\" + std::string(_MonsterName));
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder(std::string(_MonsterName) + "_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	if (nullptr != GameEngineSprite::Find(std::string(_MonsterName) + "_Ready"))
	{
		MainSpriteRenderer->CreateAnimation("Ready", std::string(_MonsterName) + "_Ready", 0.12f, -1, -1, false);
	}

	MainSpriteRenderer->CreateAnimation("Idle", std::string(_MonsterName) + "_Idle", 0.18f);
	MainSpriteRenderer->CreateAnimation("Move", std::string(_MonsterName) + "_Move", 0.15f);
	MainSpriteRenderer->CreateAnimation("Attack", std::string(_MonsterName) + "_Attack");
	MainSpriteRenderer->CreateAnimation("Death", std::string(_MonsterName) + "_Ready");

	ReadyStart();
}

void FieldMonster::ReadyStart()
{
	MainSpriteRenderer->SetPivotValue({0.5f, 0.9f});
	MainSpriteRenderer->ChangeAnimation("Ready");
}
	
void FieldMonster::IdleStart()
{
	MainSpriteRenderer->SetPivotValue({0.5f, 0.96f});
	MainSpriteRenderer->ChangeAnimation("Idle");
}

void FieldMonster::MoveStart()
{
	MainSpriteRenderer->ChangeAnimation("Move");

}

void FieldMonster::AttackStart()
{
	MainSpriteRenderer->ChangeAnimation("Attack");

}

void FieldMonster::DeathStart()
{

	MainSpriteRenderer->ChangeAnimation("Death");
}

void FieldMonster::ReadyUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(FieldMonsterState::Idle);
	}
}

void FieldMonster::IdleUpdate(float _Delta)
{

}

void FieldMonster::MoveUpdate(float _Delta)
{

}

void FieldMonster::AttackUpdate(float _Delta)
{

}

void FieldMonster::DeathUpdate(float _Delta)
{

}

void FieldMonster::ReadyEnd()
{

}

void FieldMonster::IdleEnd()
{

}

void FieldMonster::MoveEnd()
{

}

void FieldMonster::AttackEnd()
{

}

void FieldMonster::DeathEnd()
{

}