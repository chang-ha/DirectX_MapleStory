#include "PreCompile.h"
#include "Player.h"

#define JUMP_HEIGHT 400.0f
#define JUMP_ACC 150.0f
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

void Player::DownStart()
{
	MainSpriteRenderer->ChangeAnimation("Down");
}

void Player::IdleUpdate(float _Delta)
{
	if (GameEngineInput::IsPress(VK_LEFT))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}
	else if (GameEngineInput::IsPress(VK_RIGHT))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsDown('D'))
	{
		ChangeState(PlayerState::Jump);
	}

	if (GameEngineInput::IsPress(VK_DOWN))
	{
		MainSpriteRenderer->ChangeAnimation("Down");
	}
}

void Player::AlertUpdate(float _Delta)
{
	
}

void Player::WalkUpdate(float _Delta)
{

}

void Player::JumpUpdate(float _Delta)
{
	if (0.0f == GetGravityForce().Y)
	{
		ChangeState(PlayerState::Idle);
	}

	if (GameEngineInput::IsPress(VK_LEFT))
	{

		PlusGravity(float4::LEFT * _Delta * AirSpeed);
		// Transform.AddLocalPosition(float4::LEFT * _Delta * AirSpeed);
	}
	else if (GameEngineInput::IsPress(VK_RIGHT))
	{
		PlusGravity(float4::RIGHT * _Delta * AirSpeed);
		// Transform.AddLocalPosition(float4::RIGHT * _Delta * AirSpeed);
	}
}

void Player::DownUpdate(float _Delta)
{
	if (GameEngineInput::IsFree(VK_DOWN))
	{
		MainSpriteRenderer->ChangeAnimation("Idle");
	}
}