// PreCompile은 항상 최상단에 두자...
// #include 순서로 오류 발생 가능 << 잡기 정말 힘들다

#include "PreCompile.h"

#include <GameEngineCore\GameEngineCamera.h>

#include "Player.h"
#include "ContentLevel.h"
#include "ContentMap.h"
#include "GlobalValue.h"

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::LevelStart(GameEngineLevel* _PrevLevel)
{
	CurMapScale = ContentLevel::CurContentLevel->GetCurMap()->GetMapScale();
}

void Player::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Player::Start()
{
	ContentActor::Start();
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(RenderOrder::Play));
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
		MainSpriteRenderer->CreateAnimation("Attack2", "Attack2", ATT_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Attack3", "Attack3", ATT_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Down_Attack", "Down_Attack", DOWN_ATT_ANI_SPEED);
		MainSpriteRenderer->CreateAnimation("Down", "Down");
		MainSpriteRenderer->CreateAnimation("Jump", "Jump");
		std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Idle");
		PlayerScale = Sprite->GetSpriteData(0).GetScale();
	}
	MainSpriteRenderer->ChangeAnimation("Idle"); 
	MainSpriteRenderer->AutoSpriteSizeOn();
	State = PlayerState::Idle;
	Dir = ActorDir::Left;
	MainSpriteRenderer->Transform.SetLocalPosition({ 0, PlayerScale.hY()});
}

void Player::Update(float _Delta)
{
	ContentActor::Update(_Delta);
	StateUpdate(_Delta);
	CheckGround();
	DirCheck();
	ChasingCamera(_Delta);
	BlockOutMap();

	if ((PlayerState::Idle == State || PlayerState::Walk ==  State) && false == IsGround)
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

	//if (GameEngineInput::IsDown('3'))
	//{
	//	MainSpriteRenderer->ChangeAnimation("Shoot1");
	//}

	//if (GameEngineInput::IsDown('4'))
	//{
	//	MainSpriteRenderer->ChangeAnimation("Rope");
	//}

	//if (GameEngineInput::IsDown('5'))
	//{
	//	MainSpriteRenderer->ChangeAnimation("Ladder");
	//}

	//if (GameEngineInput::IsDown('6'))
	//{
	//	MainSpriteRenderer->ChangeAnimation("Attack1");
	//}

	//if (GameEngineInput::IsDown('7'))
	//{
	//	MainSpriteRenderer->ChangeAnimation("Attack2");
	//}

	//if (GameEngineInput::IsDown('8'))
	//{
	//	MainSpriteRenderer->ChangeAnimation("Attack3");
	//}

	//if (GameEngineInput::IsDown('9'))
	//{
	//	MainSpriteRenderer->ChangeAnimation("Down_Attack");
	//}


}

void Player::DirCheck()
{
	ActorDir CheckDir = ActorDir::Null;
	// bool ChangeDir = false;

	if (true == GameEngineInput::IsPress(VK_LEFT))
	{
		CheckDir = ActorDir::Left;
	}
	else if (true == GameEngineInput::IsPress(VK_RIGHT))
	{
		CheckDir = ActorDir::Right;
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
	float4 PlayerPos = Transform.GetWorldPosition();
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 MovePos = (PlayerPos - CameraPos) * 0.5f * CameraSpeed * _Delta;
	GetLevel()->GetMainCamera()->Transform.AddLocalPosition(MovePos);
	CameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
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

	// Need Text More
	CurPos.Y *= -1.0f;
	if (0 >= CurPos.Y - PlayerScale.hY())
	{
		Transform.SetLocalPosition(float4{ CurPos.X, PlayerScale.hY() });
	}
	else if (CurMapScale.Y <= CurPos.Y + PlayerScale.hY())
	{
		Transform.SetLocalPosition(float4{ CurPos.X, CurMapScale.Y - PlayerScale.hY() });
	}
}

void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
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
	case PlayerState::Null:
	default:
		MsgBoxAssert("존재하지 않는 상태값으로 Update를 돌릴 수 없습니다.");
		break;
	}
}

void Player::CheckGround()
{
	GameEngineColor GroundColor = ContentLevel::CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition(), GameEngineColor(255, 255, 255, 255));
	if (GameEngineColor(255, 255, 255, 255) == GroundColor)
	{
		IsGround = true;
	}
	else
	{
		IsGround = false;
	}
}