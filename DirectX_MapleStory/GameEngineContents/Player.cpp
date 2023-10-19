// PreCompile은 항상 최상단에 두자...
// #include 순서로 오류 발생 가능 << 잡기 정말 힘들다

#include "PreCompile.h"

#include <GameEngineCore\GameEngineCamera.h>

#include "Player.h"
#include "ContentLevel.h"
#include "ContentMap.h"

Player* Player::MainPlayer = nullptr;

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentActor::LevelStart(_PrevLevel);
	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	MainPlayer = this;
}

void Player::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentActor::LevelEnd(_NextLevel);
	Death();
}

void Player::Start()
{
	ContentActor::Start();
	GameEngineInput::AddInputObject(this);
	if (nullptr == MainSpriteRenderer)
	{
		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PLAY);
		MainSpriteRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::play});
	}

	// Create Sprite 
	if (nullptr == GameEngineSprite::Find("Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Character");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& ChildDir = Directorys[i];
			GameEngineSprite::CreateFolder(ChildDir.GetStringPath());
		}
	}

	// Create Animation
	{
		MainSpriteRenderer->CreateAnimation("Idle", "Idle", IDLE_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Alert", "Alert", IDLE_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Walk", "Walk", WALK_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Shoot", "Shoot1", SHOOT1_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Shooting", "Shoot1", 0.1f, 1, 1);
		MainSpriteRenderer->CreateAnimation("Rope", "Rope", ROPE_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Ladder", "Ladder", ROPE_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Attack1", "Attack1", ATT_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Attack2", "Attack2", 0.05f);
		MainSpriteRenderer->CreateAnimation("Attack3", "Attack3", ATT_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Down_Attack", "Down_Attack", DOWN_ATT_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Down", "Down");
		MainSpriteRenderer->CreateAnimation("Jump", "Jump");
		MainSpriteRenderer->CreateAnimation("WindWalk", "WindWalk");
		MainSpriteRenderer->CreateAnimation("FairySpiral", "FairySpiral");
		MainSpriteRenderer->CreateAnimation("VortexSphere", "VortexSphere", 0.2f);
		MainSpriteRenderer->CreateAnimation("MercilessWinds", "MercilessWinds", 0.4f);
		MainSpriteRenderer->CreateAnimation("Monsoon", "Monsoon", 0.05f);
		
		std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Idle");
		PlayerScale = Sprite->GetSpriteData(0).GetScale();
	}
	MainSpriteRenderer->ChangeAnimation("Idle"); 
	MainSpriteRenderer->AutoSpriteSizeOn();
	State = PlayerState::Idle;
	Dir = ActorDir::Right;
	MainSpriteRenderer->LeftFlip();
	MainSpriteRenderer->SetPivotType(PivotType::Bottom);

	// Animation Speed Setting
	std::shared_ptr<GameEngineFrameAnimation> _Animation = MainSpriteRenderer->FindAnimation("FairySpiral");
	_Animation->Inter[0] = 0.05f;
	_Animation->Inter[1] = 0.05f;

	_Animation = MainSpriteRenderer->FindAnimation("Shoot");
	_Animation->Inter[1] = 0.2f;

	_Animation = MainSpriteRenderer->FindAnimation("VortexSphere");
	_Animation->Inter[2] = 0.2f;

	_Animation = MainSpriteRenderer->FindAnimation("MercilessWinds");
	_Animation->Inter[0] = 0.05f;
	_Animation->Inter[2] = 0.2f;

	_Animation = MainSpriteRenderer->FindAnimation("Monsoon");
	_Animation->Inter[0] = 0.3f;
	_Animation->Inter[2] = 0.8f;
}

void Player::Update(float _Delta)
{
	ContentActor::Update(_Delta);
	DirCheck();
	ChasingCamera(_Delta);
	BlockOutMap();
	LadderCheck();
	StateUpdate(_Delta);

	if ((PlayerState::Down == State || PlayerState::Alert == State || PlayerState::Idle == State || PlayerState::Walk ==  State) && false == IsGround)
	{
		ChangeState(PlayerState::Jump);
	}

	if (true == IsGround && 0.0f >= GetMoveVectorForce().Y && PlayerState::WindWalk != State)
	{
		MoveVectorForceReset();
		GravityReset();
	}
}

void Player::Release()
{
	if (nullptr != MainSpriteRenderer)
	{
		MainSpriteRenderer->Death();
		MainSpriteRenderer = nullptr;
	}
}

void Player::DirCheck()
{
	if (false == IsDirCheck)
	{
		return;
	}

	ActorDir CheckDir = ActorDir::Null;
	// bool ChangeDir = false;

	if (true == GameEngineInput::IsPress(VK_LEFT, this))
	{
		CheckDir = ActorDir::Left;
		MainSpriteRenderer->RightFlip();
	} 
	else if (true == GameEngineInput::IsPress(VK_RIGHT, this))
	{
		CheckDir = ActorDir::Right;
		MainSpriteRenderer->LeftFlip();
	}

	if (ActorDir::Null != CheckDir)
	{
		Dir = CheckDir;
		// ChangeDir = true;
	}

	//if (PlayerDir::Null != CheckDir && true == ChangeDir)
	//{
	//	ChangeAnimationState(CurState);
	//}
}

void Player::ChasingCamera(float _Delta)
{
	if (true == GetLevel()->GetMainCamera()->IsFreeCamera())
	{
		return;
	}

	float4 StartPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 EndPos = Transform.GetWorldPosition();
	float4 MovePos = float4::LerpClamp(StartPos, EndPos, CameraSpeed * _Delta);
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(MovePos);
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	// Right Left
	if (GlobalValue::WinScale.hX() >= CameraPos.X)
	{
		CameraPos.X = GlobalValue::WinScale.hX();
	}
	else if (CurMapScale.X - GlobalValue::WinScale.hX() <= CameraPos.X)
	{
		CameraPos.X = CurMapScale.X - GlobalValue::WinScale.hX();
	}

	// Up Down
	if (GlobalValue::WinScale.hY() >= -CameraPos.Y)
	{
		CameraPos.Y = -GlobalValue::WinScale.hY();
	}
	else if (CurMapScale.Y - GlobalValue::WinScale.hY() <= -CameraPos.Y)
	{
		CameraPos.Y = -(CurMapScale.Y - GlobalValue::WinScale.hY());
	}

	CameraPos.Z = 0.0f;
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(CameraPos);
}

void Player::BlockOutMap()
{
	float4 CurPos = Transform.GetWorldPosition();
	if (0 > CurPos.X - PlayerScale.hX())
	{
		Transform.SetLocalPosition(float4{ PlayerScale.hX(), CurPos.Y });
		MoveVectorForceXReset();
	}
	else if (CurMapScale.X <= CurPos.X + PlayerScale.hX())
	{
		Transform.SetLocalPosition(float4{ CurMapScale.X - PlayerScale.hX(), CurPos.Y });
		MoveVectorForceXReset();
	}

	// Need Test More
	CurPos.Y *= -1.0f;
	if (0 > CurPos.Y - PlayerScale.hY())
	{
		Transform.SetLocalPosition(float4{ CurPos.X, -PlayerScale.hY() });
		MoveVectorForceYReset();
	}
	else if (CurMapScale.Y <= CurPos.Y + PlayerScale.hY())
	{
		Transform.SetLocalPosition(float4{ CurPos.X, - CurMapScale.Y});
		MoveVectorForceYReset();
	}
}

void Player::LadderCheck()
{
	//if (PlayerState::Alert != State && PlayerState::Down != State && PlayerState::Idle != State && PlayerState::Jump != State && PlayerState::Walk != State)
	//{
	//	return;
	//}

	float YPivot = 0.0f;
	if (GameEngineInput::IsPress(VK_UP, this))
	{
		YPivot = LADDER_Y_PIVOT;
	}
	else if(GameEngineInput::IsPress(VK_DOWN, this))
	{
		YPivot = -LADDER_Y_PIVOT;
	}

	IsLadder = false;
	for (float i = -2.0f; i < 4.0f; i += 1.0f)
	{
		GameEngineColor CheckColor = CheckGroundColor(float4(i, YPivot));
		if (LADDER_COLOR == CheckColor)
		{
			IsLadder = true;
			LadderPivot = i;
			return;
		}
	}
}

bool Player::CheckGround(float4 PlusCheckPos /*= float4::ZERO*/)
{
	if (0.0f != SkipGround && SkipGround <= Transform.GetWorldPosition().Y)
	{
		return false;
	}
	else if (0.0f != SkipGround && SkipGround > Transform.GetWorldPosition().Y)
	{
		SkipGround = 0.0f;
	}
	return ContentActor::CheckGround(PlusCheckPos);
}

void Player::ChangeToIdle()
{
	//GravityReset();
	//MoveVectorForceReset();
	if (true == IsGround)
	{
		GroundJump = false;
		DoubleJump = false;
	}

	if (0.0f < AlertTime)
	{
		ChangeState(PlayerState::Alert);
	}
	else
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		// State End
		switch (State)
		{
		case PlayerState::Idle:
			IdleEnd();
			break;
		case PlayerState::Alert:
			AlertEnd();
			break;
		case PlayerState::Walk:
			WalkEnd();
			break;
		case PlayerState::Jump:
			JumpEnd();
			break;
		case PlayerState::Down:
			DownEnd();
			break;
		case PlayerState::Ladder:
			LadderEnd();
			break;
		case PlayerState::Attack:
			AttackEnd();
			break;
		case PlayerState::Shooting:
			ShootingEnd();
			break;
		case PlayerState::Attack2:
			Attack2End();
			break;
		case PlayerState::WindWalk:
			WindWalkEnd();
			break;
		case PlayerState::Shoot:
			ShootEnd();
			break;
		case PlayerState::VortexSphere:
			VortexSphereEnd();
			break;
		case PlayerState::MercilessWinds:
			MercilessWindsEnd();
			break;
		case PlayerState::Monsoon:
			MonsoonEnd();
			break;
		case PlayerState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값을 끝내려고 했습니다.");
			break;
		}

		// State Start
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Alert:
			AlertStart();
			break;
		case PlayerState::Walk:
			WalkStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Down:
			DownStart();
			break;
		case PlayerState::Ladder:
			LadderStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		case PlayerState::Shooting:
			ShootingStart();
			break;
		case PlayerState::Attack2:
			Attack2Start();
			break;
		case PlayerState::WindWalk:
			WindWalkStart();
			break;
		case PlayerState::Shoot:
			ShootStart();
			break;
		case PlayerState::VortexSphere:
			VortexSphereStart();
			break;
		case PlayerState::MercilessWinds:
			MercilessWindsStart();
			break;
		case PlayerState::Monsoon:
			MonsoonStart();
			break;
		case PlayerState::Null:
		default:
			MsgBoxAssert("존재하지 않는 상태값으로 변경하려고 했습니다.");
			break;
		}
	}

	State = _State;
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Alert:
		return AlertUpdate(_Delta);
	case PlayerState::Walk:
		return WalkUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
	case PlayerState::Down:
		return DownUpdate(_Delta);
	case PlayerState::Ladder:
		return LadderUpdate(_Delta);
	case PlayerState::Attack:
		return AttackUpdate(_Delta);
	case PlayerState::Shooting:
		return ShootingUpdate(_Delta);
	case PlayerState::Attack2:
		return Attack2Update(_Delta);
	case PlayerState::WindWalk:
		return WindWalkUpdate(_Delta);
	case PlayerState::Shoot:
		return ShootUpdate(_Delta);
	case PlayerState::VortexSphere:
		return VortexSphereUpdate(_Delta);
	case PlayerState::MercilessWinds:
		return MercilessWindsUpdate(_Delta);
	case PlayerState::Monsoon:
		return MonsoonUpdate(_Delta);
	case PlayerState::Null:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}
