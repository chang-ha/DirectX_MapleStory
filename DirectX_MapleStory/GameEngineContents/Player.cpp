// PreCompile은 항상 최상단에 두자...
// #include 순서로 오류 발생 가능 << 잡기 정말 힘들다

#include "PreCompile.h"

#include <GameEngineCore/GameEngineRenderer.h>

#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

// Test Code
#include <GameEngineCore/GameEngineTexture.h>

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(0);

		// 자동으로 내부에서 트랜스폼을 이미지 크기로 변경까지 할것이다.
		Renderer->SetSprite("NSet.png");
	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->Transform.SetLocalPosition({ 0, 150, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->Transform.SetLocalPosition({ 0, -150, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->Transform.SetLocalPosition({ -150, 0, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	}

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
		Renderer->Transform.SetLocalPosition({ 150, 0, 0 });
		Renderer->Transform.SetLocalScale({ 50, 50, 100 });
	}
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