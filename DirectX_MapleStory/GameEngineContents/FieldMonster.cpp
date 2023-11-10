#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

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
	HP = 1;

	ContentActor::Start();

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::monster });

	MonsterCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	MonsterCollision->Transform.SetLocalScale({ 1, 1 });
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

	if (true == GameEngineInput::IsDown('6', this))
	{
		ChangeDir();
	}

	ContentActor::Gravity(_Delta);
	IsGround = ContentActor::CheckGround();
	//if (true == IsGround)
	//{
	//	GravityOff();
	//	GravityReset();
	//}
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
	MainSpriteRenderer->CreateAnimation("Death", std::string(_MonsterName) + "_Death");

	IsGroundVectorReset = false;
	ReadyStart();
}

void FieldMonster::ChangeDir()
{
	MoveVectorForce.X *= -1.0f;

	switch (Dir)
	{
	case ActorDir::Right:
		Dir = ActorDir::Left;
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Left:
		Dir = ActorDir::Right;
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}


void FieldMonster::ReadyStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		break;
	}

	MainSpriteRenderer->SetPivotValue({ 0.5f, 0.9f });
	MainSpriteRenderer->ChangeAnimation("Ready");
}

void FieldMonster::IdleStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		break;
	}

	MainSpriteRenderer->SetPivotValue({ 0.5f, 0.97f });
	MainSpriteRenderer->ChangeAnimation("Idle");
}

void FieldMonster::MoveStart()
{
	MoveVectorForce.Y = 0.0f;
	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this));
	int RandomInt = Random.RandomInt(0, 1);
	if (0 == RandomInt)
	{
		Dir = ActorDir::Left;
	}
	else
	{
		Dir = ActorDir::Right;
	}

	MainSpriteRenderer->SetPivotValue({ 0.5f, 0.96f });
	MainSpriteRenderer->ChangeAnimation("Move");
	switch (Dir)
	{
		break;
	case ActorDir::Right:
		MoveVectorForce.X = Speed;
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MoveVectorForce.X = -Speed;
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
}

void FieldMonster::AttackStart()
{
	switch (Dir)
	{
		break;
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.662f, 0.858f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.338f, 0.858f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	MainSpriteRenderer->ChangeAnimation("Attack");
}

void FieldMonster::DeathStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.465f, 0.94f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.535f, 0.94f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		break;
	}

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
	float MovePosDelta = MoveVectorForce.X * _Delta;
	if (0.0f == MovePosDelta)
	{
		return;
	}

	float Count = 0.0f;
	for (; abs(Count) < abs(MovePosDelta);)
	{
		// MOVE_CHECK_FLOAT씩 이동하면서 땅 체크
		float4 MovePos = float4::ZERO;
		GameEngineColor CheckColor = GameEngineColor(0, 0, 0, 0);

		if (0.0f > MovePosDelta)
		{
			Count -= MOVE_CHECK_FLOAT;
			MovePos = -MOVE_CHECK_FLOAT;
			if (Count < MovePosDelta)
			{
				MovePos = MovePosDelta - (Count + MOVE_CHECK_FLOAT);
				Count = MovePosDelta;
			}
		}
		else if (0.0f < MovePosDelta)
		{
			Count += MOVE_CHECK_FLOAT;
			MovePos = MOVE_CHECK_FLOAT;
			if (Count > MovePosDelta)
			{
				MovePos = MovePosDelta - (Count - MOVE_CHECK_FLOAT);
				Count = MovePosDelta;
			}
		}

		CheckColor = CheckGroundColor(MovePos + float4::UP);
		UpYPivot = 1.0f;
		if ((GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
		{
			// 내 위에 땅이 몇 블록인지 체크
			GameEngineColor PivotColor = GROUND_COLOR;
			while (UP_PIXEL_LIMIT >= UpYPivot && (GROUND_COLOR == PivotColor || FLOOR_COLOR == PivotColor))
			{
				++UpYPivot;
				PivotColor = CheckGroundColor(MovePos + float4(0, UpYPivot));
			}

			// 올라가는 경사면 타는 중이면 1칸씩 올려줌
			while (0.0f == MoveVectorForce.Y && UP_PIXEL_LIMIT >= UpYPivot && (GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
			{
				MovePos += float4::UP;
				CheckColor = CheckGroundColor(MovePos + float4::UP);
			}

			// 5칸이상이 땅이면 벽으로 인식
			if (UP_PIXEL_LIMIT < UpYPivot && true == WallCheck)
			{
				MovePos = float4::ZERO;
				ChangeDir();
				IsWall = true;
				break;
			}
		}

		CheckColor = CheckGroundColor(MovePos);
		DownYPivot = 0.0f;
		if ((GROUND_COLOR != CheckColor && FLOOR_COLOR != CheckColor))
		{
			GameEngineColor PivotColor = LADDER_COLOR;
			while (-DOWN_PIXEL_LIMIT < DownYPivot && (GROUND_COLOR != PivotColor && FLOOR_COLOR != PivotColor))
			{
				--DownYPivot;
				PivotColor = CheckGroundColor(MovePos + float4(0, DownYPivot));
			}

			// 내려가는 경사면 타는 중이면 1칸씩 내려줌
			while (0.0f == MoveVectorForce.Y && -DOWN_PIXEL_LIMIT < DownYPivot && (GROUND_COLOR != CheckColor && FLOOR_COLOR != CheckColor))
			{
				MovePos += float4::DOWN;
				CheckColor = CheckGroundColor(MovePos);
			}

			// 5칸이상이 바닥이면 절벽으로 인식
			if (-DOWN_PIXEL_LIMIT >= DownYPivot)
			{
				MovePos = float4::ZERO;
				ChangeDir();
				break;
			}
		}

		Transform.AddLocalPosition(MovePos);
	}
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