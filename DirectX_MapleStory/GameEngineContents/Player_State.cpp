#include "PreCompile.h"
#include "Player.h"

#define JUMP_HEIGHT 550.0f
#define JUMP_DIS 200.0f
#define DOUBLE_JUMP_DIS 300.0f
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

void Player::DownStart()
{
	MainSpriteRenderer->ChangeAnimation("Down");
	MainSpriteRenderer->Transform.SetLocalPosition({ -PlayerScale.hX() * 0.45f, PlayerScale.hY() * 0.6f });
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

}

void Player::DownEnd()
{
	MainSpriteRenderer->Transform.SetLocalPosition({ 0, PlayerScale.hY() });
}

void Player::IdleUpdate(float _Delta)
{
	if (GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeState(PlayerState::Down);
	}
	
	if (GameEngineInput::IsPress(VK_LEFT) || GameEngineInput::IsPress(VK_RIGHT))
	{
		ChangeState(PlayerState::Walk);
	}

	if ((GameEngineInput::IsDown('D') || GameEngineInput::IsPress('D')) && GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeState(PlayerState::Jump);
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
				PlusMoveVectorForce(float4(0, JUMP_HEIGHT * 1.2f));
			}
			else if (GameEngineInput::IsPress(VK_LEFT))
			{
				PlusMoveVectorForce(float4(-DOUBLE_JUMP_DIS, JUMP_HEIGHT * 0.1f));
			}
			else if (GameEngineInput::IsPress(VK_RIGHT))
			{
				PlusMoveVectorForce(float4(DOUBLE_JUMP_DIS, JUMP_HEIGHT * 0.1f));
			}
			else
			{
				switch (Dir)
				{
				case ActorDir::Right:
					PlusMoveVectorForce(float4(DOUBLE_JUMP_DIS * 1.5f, JUMP_HEIGHT * 0.1f));
					break;
				case ActorDir::Left:
					PlusMoveVectorForce(float4(-DOUBLE_JUMP_DIS * 1.5f, JUMP_HEIGHT * 0.1f));
					break;
				case ActorDir::Null:
				default:
					break;
				}
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
}

void Player::DownUpdate(float _Delta)
{
	if (GameEngineInput::IsFree(VK_DOWN) || GameEngineInput::IsUp(VK_DOWN))
	{
		ChangeState(PlayerState::Idle);
	}

	if (GameEngineInput::IsDown('D') || GameEngineInput::IsPress('D'))
	{
		IsGround = CheckGround(float4(0, -2));
		if (false == IsGround)
		{
			ChangeState(PlayerState::Jump);
			Transform.AddLocalPosition(float4(0, -2));
		}
	}
}