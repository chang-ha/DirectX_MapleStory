#include "PreCompile.h"
#include "Player.h"
#include "ContentMap.h"
#include "SkillManager.h"
#include "Arrow.h"

#define JUMP_HEIGHT 500.0f
#define JUMP_DIS 50.0f

#define DOUBLE_JUMP_DIS 500.0f
#define DOUBLE_JUMP_HEIGHT 150.0f
#define DOUBLE_JUMP_MAXHEIGHT 400.0f
#define DOUBLE_JUMP_MIN_DIS 500.0f

#define LADDER_JUMP_DIS 200.0f
#define LADDER_JUMP_HEIGHT 300.0f

#define WINDWALK_XVECTOR 1000.0f

// State함수들 구현
void Player::IdleStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.3f, 1.0f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.7f, 1.0f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
	MainSpriteRenderer->ChangeAnimation("Idle");
}

void Player::AlertStart()
{
	MainSpriteRenderer->ChangeAnimation("Alert");
	MainSpriteRenderer->SetPivotType(PivotType::Bottom);
}

void Player::WalkStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.3f, 1.0f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.7f, 1.0f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
	MainSpriteRenderer->ChangeAnimation("Walk");
}

void Player::JumpStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.55f, 0.73f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.45f, 0.73f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	MainSpriteRenderer->ChangeAnimation("Jump");

	if (true == IsGround)
	{
		if (ActorDir::Left == Dir && GameEngineInput::IsPress(VK_LEFT, this))
		{
			PlusMoveVectorForce(float4(-JUMP_DIS, JUMP_HEIGHT));
		}
		else if (ActorDir::Right == Dir && GameEngineInput::IsPress(VK_RIGHT, this))
		{
			PlusMoveVectorForce(float4(JUMP_DIS, JUMP_HEIGHT));
		}
		else
		{
			PlusMoveVectorForce(float4(0, JUMP_HEIGHT));
		}
		GroundJump = true;
		CharPlayer.SetVolume(GlobalValue::SkillVolume);
		CharPlayer = GameEngineSound::SoundPlay("Jump.mp3");
	}
	else if (PlayerState::Ladder & State)
	{
		if (/*ActorDir::Left == Dir &&*/ GameEngineInput::IsPress(VK_LEFT, this))
		{
			PlusMoveVectorForce(float4(-LADDER_JUMP_DIS, LADDER_JUMP_HEIGHT));
		}
		else if (/*ActorDir::Right == Dir &&*/ GameEngineInput::IsPress(VK_RIGHT, this))
		{
			PlusMoveVectorForce(float4(LADDER_JUMP_DIS, LADDER_JUMP_HEIGHT));
		}
	}
}

void Player::DownStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.7f, 1.0f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.3f, 1.0f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	MainSpriteRenderer->ChangeAnimation("Down");
	HitCollision->Transform.SetLocalScale({ 32, 40 });
	HitCollision->Transform.SetLocalPosition({ 0, 20 });
}

void Player::LadderStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.33f, 1.0f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.67f, 1.0f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	float4 CurPos = Transform.GetWorldPosition();
	Transform.SetLocalPosition(float4(CurPos.X + LadderPivot, CurPos.Y, CurPos.Z));
	MainSpriteRenderer->ChangeAnimation("Ladder");
	GravityOff();
	IsDirCheck = false;
}

void Player::SongOfHeavenStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.77f, 0.653f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.23f, 0.653f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("SongOfHeaven");
	AlertTime = ALERT_TIME;
}

void Player::FairySpiralStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.47f, 0.71f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.53f, 0.71f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("FairySpiral");
	AlertTime = ALERT_TIME;
}

void Player::WindWalkStart()
{
	MoveVectorForceReset();
	GravityOff();
	IsDirCheck = false;
	IsGroundVectorReset = false;
	if (true == IsGround)
	{
		switch (Dir)
		{
		case ActorDir::Right:
			MainSpriteRenderer->SetPivotValue({ 0.37f, 1.0f });
			MainSpriteRenderer->LeftFlip();
			break;
		case ActorDir::Left:
			MainSpriteRenderer->SetPivotValue({ 0.63f, 1.0f });
			MainSpriteRenderer->RightFlip();
			break;
		case ActorDir::Null:
		default:
			MsgBoxAssert("존재하지 않는 방향입니다.");
			break;
		}
		MainSpriteRenderer->ChangeAnimation("WindWalk");
	}
	else
	{
		MainSpriteRenderer->ChangeAnimation("Jump");
		IsGroundCheck = false;
		// 경사면 오차용
		PlusMoveVectorForce({0, 0.000001f});
	}
	switch (Dir)
	{
	case ActorDir::Right:
		PlusMoveVectorForce(float4(WINDWALK_XVECTOR));
		break;
	case ActorDir::Left:
		PlusMoveVectorForce(float4(-WINDWALK_XVECTOR));
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}
	AirResisOn(Dir, WINDWALK_XVECTOR * 1.8f);
}

void Player::HowlingGaleStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.77f, 0.65f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.23f, 0.65f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("HowlingGale");
	AlertTime = ALERT_TIME;
}

void Player::VortexSphereStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.77f, 0.65f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.23f, 0.65f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("VortexSphere");
	AlertTime = ALERT_TIME;
}

void Player::MercilessWindsStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.66f, 0.78f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.34f, 0.78f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("MercilessWinds");
	AlertTime = ALERT_TIME;
}

void Player::MonsoonStart()
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.66f, 0.78f });
		MainSpriteRenderer->LeftFlip();
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.34f, 0.78f });
		MainSpriteRenderer->RightFlip();
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("Monsoon");
	AlertTime = ALERT_TIME;
}

void Player::IdleEnd()
{

}

void Player::AlertEnd()
{
	Player::IdleEnd();
}

void Player::WalkEnd()
{
}

void Player::JumpEnd()
{
}

void Player::DownEnd()
{
	HitCollision->Transform.SetLocalScale({ 32, 70 });
	HitCollision->Transform.SetLocalPosition({ 0, 35 });
}

void Player::LadderEnd()
{
	IsDirCheck = true;
	GravityReset();
	MoveVectorForceReset();
	GravityOn();
	MainSpriteRenderer->AnimationPauseOff();
	if (true == GameEngineInput::IsPress(VK_UP, this))
	{
		// 발판의 픽셀(3픽셀)로 올라가기 위해 +4을 해주었음 << 추후 보강
		Transform.AddLocalPosition(float4(0, 4.0f));
	}
}

void Player::SongOfHeavenEnd()
{
	IsDirCheck = true;
}

void Player::FairySpiralEnd()
{
	IsDirCheck = true;
}

void Player::WindWalkEnd()
{
	IsDirCheck = true;
	IsGroundCheck = true;
	IsGroundVectorReset = true;
	MoveVectorForceReset();
	GravityOn();
	AirResisOff();
}

void Player::HowlingGaleEnd()
{
	IsDirCheck = true;
}

void Player::VortexSphereEnd()
{
	IsDirCheck = true;
}

void Player::MercilessWindsEnd()
{
	IsDirCheck = true;
}

void Player::MonsoonEnd()
{
	IsDirCheck = true;
}

void Player::IdleUpdate(float _Delta)
{
	if ((PlayerState::Idle & State) && (0.0f < AlertTime))
	{
		ChangeState(PlayerState::Alert);
		return;
	}

	if (GameEngineInput::IsPress(VK_DOWN, this))
	{
		if (false == IsLadder)
		{
			ChangeState(PlayerState::Down);
			return;
		}
		else if (true == IsLadder)
		{
			ChangeState(PlayerState::Ladder);
			return;
		}
	}
	
	if (GameEngineInput::IsPress(VK_LEFT, this) || GameEngineInput::IsPress(VK_RIGHT, this))
	{
		ChangeState(PlayerState::Walk);
		return;
	}

	if ((GameEngineInput::IsDown('D', this) || GameEngineInput::IsPress('D', this)) && GameEngineInput::IsFree(VK_DOWN, this))
	{
		ChangeState(PlayerState::Jump);
		return;
	}
}

void Player::AlertUpdate(float _Delta)
{
	AlertTime -= _Delta;
	if (0.0f >= AlertTime)
	{
		ChangeState(PlayerState::Idle);
	}
	IdleUpdate(_Delta);
}

void Player::WalkUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float MoveDir = 0.0f;
	GameEngineColor CheckColor = GROUND_COLOR;

	switch (Dir)
	{
	case ActorDir::Right:
		MoveDir = 1.0f;
		MainSpriteRenderer->SetPivotValue({ 0.33f, 1.0f });
		break;
	case ActorDir::Left:
		MoveDir = -1.0f;
		MainSpriteRenderer->SetPivotValue({ 0.67f, 1.0f });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	if ((GameEngineInput::IsPress(VK_LEFT, this) || GameEngineInput::IsPress(VK_RIGHT, this)))
	{
		SetMoveVectorXForce(MoveDir * Speed);
	}

	if (GameEngineInput::IsDown('D', this) || GameEngineInput::IsPress('D', this))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (GameEngineInput::IsFree(VK_LEFT, this) && GameEngineInput::IsFree(VK_RIGHT, this))
	{
		ChangeToIdle();
		return;
	}

	if (true == IsLadder && (GameEngineInput::IsPress(VK_UP, this) || GameEngineInput::IsPress(VK_DOWN, this)))
	{
		ChangeState(PlayerState::Ladder);
		return;
	}
}

void Player::JumpUpdate(float _Delta)
{
	switch (Dir)
	{
	case ActorDir::Right:
		MainSpriteRenderer->SetPivotValue({ 0.55f, 0.73f });
		break;
	case ActorDir::Left:
		MainSpriteRenderer->SetPivotValue({ 0.45f, 0.73f });
		break;
	case ActorDir::Null:
	default:
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	if (true == IsGround && 0 >= GetMoveVectorForce().Y)
	{
		MoveVectorForceReset();
		GravityReset();
		ChangeToIdle();
		return;
	}
	
	// Ladder
	if (true == IsLadder && GameEngineInput::IsPress(VK_UP, this))
	{
		ChangeState(PlayerState::Ladder);
		GravityReset();
		MoveVectorForceReset();
		GroundJump = false;
		DoubleJump = false;
		return;
	}

	// Move
	if (GameEngineInput::IsPress(VK_LEFT, this) || GameEngineInput::IsPress(VK_RIGHT, this))
	{
		float4 MoveDir = float4::ZERO;

		switch (Dir)
		{
		case ActorDir::Right:
			MoveDir = float4::RIGHT;
			break;
		case ActorDir::Left:
			MoveDir = float4::LEFT;
			break;
		case ActorDir::Null:
		default:
			break;
		}

		switch (GroundJump)
		{
		case true:
			MoveVectorForce += MoveDir * _Delta * JumpAirSpeed;
			break;
		case false:
			MoveVectorForce += MoveDir * _Delta * AirSpeed;
			break;
		}
	}

	////// Double Jump
	if (true == DoubleJump)
	{
		return;
	}

	if (GameEngineInput::IsDown('D', this))
	{
		GravityReset();
		SkillManagerActor->UseSkill("DoubleJump");
		DoubleJump = true;
		CharPlayer = GameEngineSound::SoundPlay("Double_Jump.mp3");
		CharPlayer.SetVolume(GlobalValue::SkillVolume);

		if (true == GameEngineInput::IsPress(VK_UP, this))
		{
			PlusMoveVectorForce(float4(0, JUMP_HEIGHT /** 1.3f*/));
			return;
		}
		MoveVectorForceXReset();

		switch (Dir)
		{
		case ActorDir::Right:	
			PlusMoveVectorForce(float4(DOUBLE_JUMP_DIS, DOUBLE_JUMP_HEIGHT));
			break;
		case ActorDir::Left:
			PlusMoveVectorForce(float4(-DOUBLE_JUMP_DIS , DOUBLE_JUMP_HEIGHT));
			break;
		case ActorDir::Null:
		default:
			MsgBoxAssert("존재하지 않는 방향입니다.");
			break;
		}

		if (DOUBLE_JUMP_HEIGHT > MoveVectorForce.Y)
		{
			MoveVectorForce.Y = DOUBLE_JUMP_HEIGHT;
		}

		if (DOUBLE_JUMP_MAXHEIGHT < MoveVectorForce.Y)
		{
			MoveVectorForce.Y = DOUBLE_JUMP_MAXHEIGHT;
		}
	}
}

void Player::DownUpdate(float _Delta)
{
	if (GameEngineInput::IsFree(VK_DOWN, this) || GameEngineInput::IsUp(VK_DOWN, this))
	{
		ChangeToIdle();
		return;
	}

	else if ( FLOOR_COLOR == CheckGroundColor() && (GameEngineInput::IsDown('D', this) || GameEngineInput::IsPress('D', this)))
	{
		MoveVectorForceReset();
		PlusMoveVectorForce({0, 150.0f});
		IsGround = false;
		SkipGround = Transform.GetWorldPosition().Y - 3.0f;
		ChangeState(PlayerState::Jump);
		CharPlayer = GameEngineSound::SoundPlay("Jump.mp3");
	}
}

void Player::LadderUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	if (GameEngineInput::IsPress(VK_UP, this))
	{
		MainSpriteRenderer->AnimationPauseOff();
		MovePos += float4::UP * _Delta * Speed;
	}
	else if (GameEngineInput::IsPress(VK_DOWN, this))
	{
		MainSpriteRenderer->AnimationPauseOff();
		MovePos += float4::DOWN * _Delta * Speed;
	}
	else if (GameEngineInput::IsPress(VK_RIGHT, this) || GameEngineInput::IsPress(VK_LEFT, this))
	{
		MainSpriteRenderer->AnimationPauseOn();
		if (GameEngineInput::IsDown('D', this))
		{
			IsDirCheck = true;
			DirCheck();
			ChangeState(PlayerState::Jump);
			return;
		}
	}
	else
	{
		MainSpriteRenderer->AnimationPauseOn();
	}

	Transform.AddLocalPosition(MovePos);
	LadderCheck();
	if (false == IsLadder)
	{
		MoveVectorForceReset();
		ChangeToIdle();
		return;
	}
}

void Player::SongOfHeavenUpdate(float _Delta)
{
	if (true == GameEngineInput::IsFree('A', this))
	{
		SkillManagerActor->EndSkill("SongOfHeaven");
		ChangeToIdle();
	}
}

void Player::FairySpiralUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		if (true == IsGround)
		{
			ChangeToIdle();
		}
		else
		{
			ChangeState(PlayerState::Jump);
		}
	}
}

void Player::WindWalkUpdate(float _Delta)
{
	if (0.0f == GetMoveVectorForce().X)
	{
		ChangeToIdle();
	}
}

void Player::HowlingGaleUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeToIdle();
	}
}

void Player::VortexSphereUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeToIdle();
	}
}

void Player::MercilessWindsUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeToIdle();
	}
}

void Player::MonsoonUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		ChangeToIdle();
	}
}
