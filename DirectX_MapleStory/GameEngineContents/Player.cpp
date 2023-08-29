// PreCompile은 항상 최상단에 두자...
// #include 순서로 오류 발생 가능 << 잡기 정말 힘들다

#include "PreCompile.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();
	MainSpriteRenderer->SetSprite("TestPlayer.png", 0);
}

void Player::Update(float _Delta)
{
	float Speed = 100.0f;

	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::LEFT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::RIGHT * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::UP * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::DOWN * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}

	if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}
}