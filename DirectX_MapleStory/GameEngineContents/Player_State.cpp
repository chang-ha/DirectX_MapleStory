#include "PreCompile.h"
#include "Player.h"

#define JUMP_HEIGHT 500.0f
#define JUMP_DISTANCE 200.0f
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
	if (false == IsGround)
	{
		return;
	}

	if (GameEngineInput::IsPress(VK_LEFT))
	{
		PlusMoveVectorForce(float4(-JUMP_DISTANCE, JUMP_HEIGHT));
	}
	else if (GameEngineInput::IsPress(VK_RIGHT))
	{
		PlusMoveVectorForce(float4(JUMP_DISTANCE, JUMP_HEIGHT));
	}
	else
	{
		PlusMoveVectorForce(float4(0, JUMP_HEIGHT));
	}
	GroundJump = true;
}

void Player::DownStart()
{
	MainSpriteRenderer->ChangeAnimation("Down");
}

void Player::IdleUpdate(float _Delta)
{
	if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeState(PlayerState::Walk);
	}

	if (GameEngineInput::IsDown('D') || GameEngineInput::IsPress('D'))
	{
		ChangeState(PlayerState::Jump);
	}

	if (GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeState(PlayerState::Down);
	}
}

void Player::AlertUpdate(float _Delta)
{
	
}

void Player::WalkUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	if (GameEngineInput::IsPress(VK_LEFT))
	{
		MovePos += float4::LEFT * _Delta * Speed;
	}
	else if (GameEngineInput::IsPress(VK_RIGHT))
	{
		MovePos += float4::RIGHT * _Delta * Speed;
	}

	if (GameEngineInput::IsDown('D') || GameEngineInput::IsPress('D'))
	{
		ChangeState(PlayerState::Jump);
	}

	if (0.0f == MovePos.X)
	{
		ChangeState(PlayerState::Idle);
	}
	Transform.AddLocalPosition(MovePos);
}

void Player::JumpUpdate(float _Delta)
{
	if (0.0f == GetMoveVectorForce().Y)
	{
		ChangeState(PlayerState::Idle);
		GroundJump = false;
		DoubleJump = false;
	}

	if (false == DoubleJump)
	{
		if (GameEngineInput::IsDown('D'))
		{
			DoubleJump = true;
			if (GameEngineInput::IsPress(VK_UP))
			{
				PlusMoveVectorForce(float4(0, JUMP_HEIGHT * 0.3f));
			}
			else if (GameEngineInput::IsPress(VK_LEFT))
			{
				PlusMoveVectorForce(float4(-JUMP_DISTANCE * 1.5f, JUMP_HEIGHT * 0.25f));
			}
			else if (GameEngineInput::IsPress(VK_RIGHT))
			{
				PlusMoveVectorForce(float4(JUMP_DISTANCE * 1.5f, JUMP_HEIGHT * 0.25f));
			}
			GravityReset();
		}
	}

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

	if (GameEngineInput::IsDown('D'))
	{
		if (GameEngineInput::IsPress(VK_UP))
		{
			GravityReset();
			PlusMoveVectorForce(float4(0, JUMP_HEIGHT));
		}
	}
}

void Player::DownUpdate(float _Delta)
{
	if (GameEngineInput::IsFree(VK_DOWN) || GameEngineInput::IsUp(VK_DOWN))
	{
		ChangeState(PlayerState::Idle);
	}
}