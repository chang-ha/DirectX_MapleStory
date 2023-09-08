#include "PreCompile.h"
#include "Player.h"
#include "ContentMap.h"
#include "SkillManager.h"

#define JUMP_HEIGHT 500.0f
#define JUMP_DIS 200.0f

#define DOUBLE_JUMP_DIS 350.0f
#define DOUBLE_JUMP_HEIGHT 100.0f

#define LADDER_JUMP_HEIGHT 300.0f

#define UP_PIXEL_LIMIT 4
#define DOWN_PIXEL_LIMIT 4
// State함수들 구현
void Player::IdleStart()
{
	MainSpriteRenderer->ChangeAnimation("Idle");
}

void Player::AlertStart()
{
	MainSpriteRenderer->ChangeAnimation("Alert");
}

void Player::WalkStart()
{
	MainSpriteRenderer->ChangeAnimation("Walk");
}

void Player::JumpStart()
{
	MainSpriteRenderer->ChangeAnimation("Jump");

	if (true == IsGround)
	{
		if (GameEngineInput::IsPress(VK_LEFT))
		{
			PlusMoveVectorForce(float4(-JUMP_DIS, JUMP_HEIGHT));
		}
		else if (GameEngineInput::IsPress(VK_RIGHT))
		{
			PlusMoveVectorForce(float4(JUMP_DIS, JUMP_HEIGHT));
		}
		else
		{
			PlusMoveVectorForce(float4(0, JUMP_HEIGHT));
		}
		GroundJump = true;
	}
	else if (PlayerState::Ladder == State)
	{
		if (GameEngineInput::IsPress(VK_LEFT))
		{
			PlusMoveVectorForce(float4(-JUMP_DIS, LADDER_JUMP_HEIGHT));
		}
		else if (GameEngineInput::IsPress(VK_RIGHT))
		{
			PlusMoveVectorForce(float4(JUMP_DIS, LADDER_JUMP_HEIGHT));
		}
	}
}

void Player::DownStart()
{
	MainSpriteRenderer->ChangeAnimation("Down");
	MainSpriteRenderer->Transform.SetLocalPosition({ -PlayerScale.hX() * 0.45f, PlayerScale.hY() * 0.6f });
}

void Player::LadderStart()
{
	float4 CurPos = Transform.GetWorldPosition();
	Transform.SetLocalPosition(float4(CurPos.X + LadderPivot, CurPos.Y, CurPos.Z));
	MainSpriteRenderer->ChangeAnimation("Ladder");
	GravityOff();
}

void Player::IdleEnd()
{

}

void Player::AlertEnd()
{

}

void Player::WalkEnd()
{

}

void Player::JumpEnd()
{
	GravityReset();
	MoveVectorForceReset();
	GroundJump = false;
	DoubleJump = false;
}

void Player::DownEnd()
{
	MainSpriteRenderer->Transform.SetLocalPosition({ 0, PlayerScale.hY() });
}

void Player::LadderEnd()
{
	GravityReset();
	MoveVectorForceReset();
	GravityOn();
	MainSpriteRenderer->AnimationPauseOff();
	if (true == GameEngineInput::IsPress(VK_UP))
	{
		// 발판의 픽셀(3픽셀)로 올라가기 위해 +4을 해주었음 << 추후 보강
		Transform.AddLocalPosition(float4(0, 4.0f));
	}
}

void Player::IdleUpdate(float _Delta)
{
	if (GameEngineInput::IsPress(VK_DOWN))
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
	
	if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeState(PlayerState::Walk);
		return;
	}

	if ((GameEngineInput::IsDown('D') || GameEngineInput::IsPress('D')) && GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeState(PlayerState::Jump);
		return;
	}
}

void Player::AlertUpdate(float _Delta)
{
	
}

void Player::WalkUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	float4 MoveDir = float4::ZERO;
	GameEngineColor CheckColor = GROUND_COLOR;

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
		MsgBoxAssert("존재하지 않는 방향입니다.");
		break;
	}

	if ((GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT)))
	{
		MovePos += MoveDir * _Delta * Speed;
	}

	// 올라가는 경사면
	CheckColor = CheckGroundColor(MovePos + float4::UP);
	if ((GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
	{
		float UpYPivot = 1.0f;
		GameEngineColor PivotColor = GROUND_COLOR;
		while (UP_PIXEL_LIMIT >= UpYPivot && (GROUND_COLOR == PivotColor || FLOOR_COLOR == PivotColor))
		{
			++UpYPivot;
			PivotColor = CheckGroundColor(MovePos + float4(0, UpYPivot));
		}

		while (UP_PIXEL_LIMIT >= UpYPivot && (GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
		{
			MovePos += float4::UP;
			CheckColor = CheckGroundColor(MovePos + float4::UP);
		}

		//while (UP_PIXEL_LIMIT + 1 <= UpYPivot && (GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor))
		//{
		//	MovePos -= MoveDir * 0.1f;
		//	CheckColor = CheckGroundColor(MovePos + float4::UP);
		//}
	}

	// 내려가는 경사면
	CheckColor = CheckGroundColor(MovePos);
	if ((GROUND_COLOR != CheckColor && FLOOR_COLOR != CheckColor))
	{
		float DownYPivot = 0.0f;
		GameEngineColor PivotColor = LADDER_COLOR;
		while (-DOWN_PIXEL_LIMIT < DownYPivot && (GROUND_COLOR != PivotColor && FLOOR_COLOR != PivotColor))
		{
			--DownYPivot;
			PivotColor = CheckGroundColor(MovePos + float4(0, DownYPivot));
		}

		while (-DOWN_PIXEL_LIMIT < DownYPivot && (GROUND_COLOR != CheckColor && FLOOR_COLOR != CheckColor))
		{
			MovePos += float4::DOWN;
			CheckColor = CheckGroundColor(MovePos);
		}
	}
	Transform.AddLocalPosition(MovePos);

	if (GameEngineInput::IsDown('D') || GameEngineInput::IsPress('D'))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (GameEngineInput::IsFree(VK_LEFT) && GameEngineInput::IsFree(VK_RIGHT))
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == IsLadder && (GameEngineInput::IsPress(VK_UP) || GameEngineInput::IsPress(VK_DOWN)))
	{
		ChangeState(PlayerState::Ladder);
		return;
	}
}

void Player::JumpUpdate(float _Delta)
{
	if (true == IsGround && 0 >= GetMoveVectorForce().Y)
	{
		ChangeState(PlayerState::Idle);
		return;
	}
	
	// Ladder
	if (true == IsLadder && GameEngineInput::IsPress(VK_UP))
	{
		ChangeState(PlayerState::Ladder);
		return;
	}

	// Move
	if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
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
			Transform.AddLocalPosition(MoveDir * _Delta * JumpAirSpeed);
			break;
		case false:
			Transform.AddLocalPosition(MoveDir * _Delta * AirSpeed);
			break;
		}
	}

	////// Double Jump
	if (true == DoubleJump)
	{
		return;
	}

	if (GameEngineInput::IsDown('D'))
	{
		SkillManager::PlayerSkillManager->UseSkill("DoubleJump");
		DoubleJump = true;
		if (GameEngineInput::IsPress(VK_UP))
		{
			PlusMoveVectorForce(float4(0, JUMP_HEIGHT * 1.3f));
		}
		else if (GameEngineInput::IsPress(VK_LEFT))
		{
			PlusMoveVectorForce(float4(-DOUBLE_JUMP_DIS, DOUBLE_JUMP_HEIGHT));
		}
		else if (GameEngineInput::IsPress(VK_RIGHT))
		{
			PlusMoveVectorForce(float4(DOUBLE_JUMP_DIS, DOUBLE_JUMP_HEIGHT));
		}
		else
		{
			switch (Dir)
			{
			case ActorDir::Right:
				PlusMoveVectorForce(float4(DOUBLE_JUMP_DIS * 1.5f, DOUBLE_JUMP_HEIGHT));
				break;
			case ActorDir::Left:
				PlusMoveVectorForce(float4(-DOUBLE_JUMP_DIS * 1.5f, DOUBLE_JUMP_HEIGHT));
				break;
			case ActorDir::Null:
			default:
				break;
			}
		}
		GravityReset();
	}
}

void Player::DownUpdate(float _Delta)
{
	if (GameEngineInput::IsFree(VK_DOWN) || GameEngineInput::IsUp(VK_DOWN))
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	else if (GameEngineInput::IsDown('D') || GameEngineInput::IsPress('D'))
	{
		if (false == CheckGround(float4(0, -3)))
		{
			IsGround = false;
			ChangeState(PlayerState::Jump);
			Transform.AddLocalPosition(float4(0, -3));
			return;
		}
	}
}

void Player::LadderUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	if (GameEngineInput::IsPress(VK_UP))
	{
		MainSpriteRenderer->AnimationPauseOff();
		MovePos += float4::UP * _Delta * Speed;
	}
	else if (GameEngineInput::IsPress(VK_DOWN))
	{
		MainSpriteRenderer->AnimationPauseOff();
		MovePos += float4::DOWN * _Delta * Speed;
	}
	else if (GameEngineInput::IsPress(VK_RIGHT) || GameEngineInput::IsPress(VK_LEFT))
	{
		if (GameEngineInput::IsDown('D'))
		{
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
		ChangeState(PlayerState::Idle);
		return;
	}
}