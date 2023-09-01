#include "PreCompile.h"
#include "Player.h"

#define JUMP_HEIGHT 400.0f
#define JUMP_ACC 200.0f
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
			PlusGravity(float4(-JUMP_ACC, JUMP_HEIGHT));
		}
		else if (GameEngineInput::IsPress(VK_RIGHT))
		{
			PlusGravity(float4(JUMP_ACC, JUMP_HEIGHT));
		}
		else
		{
			PlusGravity(float4(0, JUMP_HEIGHT));
		}
	}
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
	if (0.0f == GetGravityForce().Y)
	{
		ChangeState(PlayerState::Idle);
	}

	if ((0 < GetGravityForce().X && GameEngineInput::IsFree(VK_RIGHT)) || (0 > GetGravityForce().X && GameEngineInput::IsFree(VK_LEFT)))
	{
		SetGravityX(0.0f);
	}

	if (GameEngineInput::IsPress(VK_LEFT))
	{
		// PlusGravity(float4::LEFT * _Delta * AirSpeed);
		Transform.AddLocalPosition(float4::LEFT * _Delta * AirSpeed);
	}
	else if (GameEngineInput::IsPress(VK_RIGHT))
	{
		// PlusGravity(float4::RIGHT * _Delta * AirSpeed);
		Transform.AddLocalPosition(float4::RIGHT * _Delta * AirSpeed);
	}
}

void Player::DownUpdate(float _Delta)
{
	if (GameEngineInput::IsFree(VK_DOWN) || GameEngineInput::IsUp(VK_DOWN))
	{
		ChangeState(PlayerState::Idle);
	}
}