#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "FieldMonster.h"
#include "Player.h"

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
	//Speed = 0.0f;
	//GravityOff();

	HP = 1;

	ContentActor::Start();

	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::monster });

	MonsterCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	MonsterCollision->Off();

	DetectCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Detect);
	DetectCollision->Transform.SetLocalPosition({ 0, 50 });
	DetectCollision->Transform.SetLocalScale({ 300, 50 });
	DetectCollision->Off();

	AttackCollision = CreateComponent<GameEngineCollision>(CollisionOrder::MonsterAttack);
	AttackCollision->Off();

	IsGroundVectorReset = false;
}

void FieldMonster::Update(float _Delta)
{
	// AttackCoolDown -= _Delta;
	ContentActor::Gravity(_Delta);
	IsGround = ContentActor::CheckGround();
	//if (true == IsGround)
	//{
	//	GravityOff();
	//	GravityReset();
	//}
	StateUpdate(_Delta);

	if (0 >= HP)
	{
		ChangeState(FieldMonsterState::Death);
	}

	if (/*0.0f >= AttackCoolDown &&*/ true == DetectCollision->Collision(CollisionOrder::Player))
	{
		ChangeState(FieldMonsterState::Attack);
	}
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

void FieldMonster::Respawn()
{
	On();
	HP = 1;
	ChangeState(FieldMonsterState::Ready);
	// MainSpriteRenderer->On();
}

void FieldMonster::Init(std::string_view _MonsterName)
{
	MonsterName = _MonsterName;
	if (nullptr == GameEngineSprite::Find(std::string(MonsterName) + "_Death"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Monster\\" + std::string(MonsterName));
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder(std::string(MonsterName) + "_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	MainSpriteRenderer->CreateAnimation("Death", std::string(MonsterName) + "_Death");
	MainSpriteRenderer->SetEndEvent("Death", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Off();
			// MainSpriteRenderer->Off();
			// MonsterCollision->Off();
			// DetectCollision->Off();
			// AttackCollision->Off();
		});
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

void FieldMonster::RandomChangeDir()
{
	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this) + time(nullptr));
	int RandomInt = Random.RandomInt(0, 1);
	if (0 == RandomInt)
	{
		ChangeDir();
	}

	return;
}

void FieldMonster::RandomChangeDirTime(float _MinTime, float _MaxTime)
{
	GameEngineRandom Random;
	Random.SetSeed(time(nullptr));
	ChangeDirTime = Random.RandomFloat(_MinTime, _MaxTime);
}

void FieldMonster::ReadyStart()
{
	Dir = ActorDir::Left;
	MainSpriteRenderer->RightFlip();
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
}

void FieldMonster::MoveStart()
{
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

	MainSpriteRenderer->ChangeAnimation("Move");
}

void FieldMonster::AttackStart()
{
	float PlayerPos_X = Player::MainPlayer->Transform.GetWorldPosition().X;
	float CurPos_X = Transform.GetWorldPosition().X;

	if (0 < CurPos_X - PlayerPos_X)
	{
		Dir = ActorDir::Left;
	}
	else
	{
		Dir = ActorDir::Right;
	}

	switch (Dir)
	{
		break;
	case ActorDir::Right:
		MainSpriteRenderer->LeftFlip();
		if (0.0f > MoveVectorForce.X)
		{
			MoveVectorForce.X *= -1.0f;
			RandomChangeDirTime(4.0f, 5.0f);
		}
		break;
	case ActorDir::Left:
		MainSpriteRenderer->RightFlip();
		if (0.0f < MoveVectorForce.X)
		{
			MoveVectorForce.X *= -1.0f;
			RandomChangeDirTime(4.0f, 5.0f);
		}
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
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		break;
	}

	MainSpriteRenderer->ChangeAnimation("Death");
	MonsterCollision->Off();
	DetectCollision->Off();
	AttackCollision->Off();
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
	MoveDelay -= _Delta;

	if (0.0f >= MoveDelay)
	{
		ChangeState(FieldMonsterState::Move);
	}
}

void FieldMonster::MoveUpdate(float _Delta)
{
	ChangeDirTime -= _Delta;
	if (0.0f >= ChangeDirTime)
	{
		RandomChangeDirTime(3.0f, 6.0f);
		RandomChangeDir();
	}

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
		UpYPivot = 1;
		if ((GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
		{
			// 내 위에 땅이 몇 블록인지 체크
			GameEngineColor PivotColor = GROUND_COLOR;
			while (UP_PIXEL_LIMIT >= UpYPivot && (GROUND_COLOR == PivotColor || FLOOR_COLOR == PivotColor))
			{
				++UpYPivot;
				PivotColor = CheckGroundColor(MovePos + float4(0, static_cast<float>(UpYPivot)));
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
				RandomChangeDirTime(2.0f, 4.0f);
				// IsWall = true;
				break;
			}
		}

		CheckColor = CheckGroundColor(MovePos);
		DownYPivot = 0;
		if ((GROUND_COLOR != CheckColor && FLOOR_COLOR != CheckColor))
		{
			GameEngineColor PivotColor = LADDER_COLOR;
			while (-DOWN_PIXEL_LIMIT < DownYPivot && (GROUND_COLOR != PivotColor && FLOOR_COLOR != PivotColor))
			{
				--DownYPivot;
				PivotColor = CheckGroundColor(MovePos + float4(0, static_cast<float>(DownYPivot)));
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
				RandomChangeDirTime(2.0f, 4.0f);
				break;
			}
		}

		Transform.AddLocalPosition(MovePos);
	}
}

void FieldMonster::AttackUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeState(FieldMonsterState::Move);
	}

	AttackFunction.AttackUpdate(AttackCollision, CollisionOrder::Player, MonsterName + "_Attack_Hit", 1, 3, false, PivotType::Center);
}

void FieldMonster::DeathUpdate(float _Delta)
{

}

void FieldMonster::ReadyEnd()
{
	MonsterCollision->On();
	DetectCollision->On();
}

void FieldMonster::IdleEnd()
{
	MoveVectorForce.Y = 0.0f;
	GameEngineRandom Random;
	Random.SetSeed(reinterpret_cast<long long>(this) + time(nullptr));
	int RandomInt = Random.RandomInt(0, 1);
	if (0 == RandomInt)
	{
		Dir = ActorDir::Left;
	}
	else
	{
		Dir = ActorDir::Right;
	}
}

void FieldMonster::MoveEnd()
{
	// ChangeDirTime = 0.0f;
}

void FieldMonster::AttackEnd()
{
	// AttackCoolDown = ATTACK_COOLDOWN;
	AttackCollision->Off();
	AttackFunction.CollisionActor.clear();
}

void FieldMonster::DeathEnd()
{

}