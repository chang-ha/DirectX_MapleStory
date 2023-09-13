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
	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
	MainPlayer = this;
}

void Player::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Player::Start()
{
	ContentActor::Start();
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Play);
	MainSpriteRenderer->SetSamplerState(SamplerOption::POINT);

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
		MainSpriteRenderer->CreateAnimation("Attack2", "Attack2", 0.1f);
		MainSpriteRenderer->CreateAnimation("Attack3", "Attack3", ATT_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Down_Attack", "Down_Attack", DOWN_ATT_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Down", "Down");
		MainSpriteRenderer->CreateAnimation("Jump", "Jump");
		std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Idle");
		PlayerScale = Sprite->GetSpriteData(0).GetScale();
		Sprite = nullptr;
	}
	MainSpriteRenderer->ChangeAnimation("Idle"); 
	MainSpriteRenderer->AutoSpriteSizeOn();
	State = PlayerState::Idle;
	Dir = ActorDir::Left; 
	MainSpriteRenderer->SetPivotType(PivotType::Bottom);

	// Event Setting
	MainSpriteRenderer->SetFrameEvent("Shoot", 1, std::bind(&Player::AttackEvent, this, std::placeholders::_1));
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

	//if (GameEngineInput::IsPress('Q'))
	//{
	//	Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	//}

	//if (GameEngineInput::IsPress('E'))
	//{
	//	Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	//}

}

void Player::DirCheck()
{
	ActorDir CheckDir = ActorDir::Null;
	// bool ChangeDir = false;

	if (true == GameEngineInput::IsPress(VK_LEFT))
	{
		CheckDir = ActorDir::Left;
		Transform.SetLocalScale(float4(1.0f, 1.0f));
	} 
	else if (true == GameEngineInput::IsPress(VK_RIGHT))
	{
		CheckDir = ActorDir::Right;
		Transform.SetLocalScale(float4(-1.0f, 1.0f));
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
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(CameraPos);
}

void Player::BlockOutMap()
{
	float4 CurPos = Transform.GetWorldPosition();
	if (0 >= CurPos.X - PlayerScale.hX())
	{
		Transform.SetLocalPosition(float4{ PlayerScale.hX(), CurPos.Y });
	}
	else if (CurMapScale.X <= CurPos.X + PlayerScale.hX())
	{
		Transform.SetLocalPosition(float4{ CurMapScale.X - PlayerScale.hX(), CurPos.Y });
	}

	// Need Test More
	CurPos.Y *= -1.0f;
	if (0 >= CurPos.Y - PlayerScale.hY())
	{
		Transform.SetLocalPosition(float4{ CurPos.X, -PlayerScale.hY() });
		MoveVectorForceReset();
	}
	else if (CurMapScale.Y <= CurPos.Y + PlayerScale.hY())
	{
		Transform.SetLocalPosition(float4{ CurPos.X, CurMapScale.Y - PlayerScale.hY() });
	}
}

void Player::LadderCheck()
{
	//if (PlayerState::Alert != State && PlayerState::Down != State && PlayerState::Idle != State && PlayerState::Jump != State && PlayerState::Walk != State)
	//{
	//	return;
	//}

	float YPivot = 0.0f;
	if (GameEngineInput::IsPress(VK_UP))
	{
		YPivot = LADDER_Y_PIVOT;
	}
	else if(GameEngineInput::IsPress(VK_DOWN))
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

void Player::ChangeToIdle()
{
	GravityReset();
	MoveVectorForceReset();
	GroundJump = false;
	DoubleJump = false;
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
	case PlayerState::Null:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}
