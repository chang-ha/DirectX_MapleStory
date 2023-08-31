// PreCompile은 항상 최상단에 두자...
// #include 순서로 오류 발생 가능 << 잡기 정말 힘들다

#include "PreCompile.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore\GameEngineSprite.h>

#include "Player.h"

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	ContentActor::Start();
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>();

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

	MainSpriteRenderer->CreateAnimation("Idle", "Idle", IDLE_ANI_SPEED);
	MainSpriteRenderer->CreateAnimation("Alert", "Alert", IDLE_ANI_SPEED);
	MainSpriteRenderer->CreateAnimation("Walk", "Walk", WALK_ANI_SPEED);
	MainSpriteRenderer->CreateAnimation("Shoot1", "Shoot1", SHOOT1_ANI_SPEED);
	MainSpriteRenderer->CreateAnimation("Rope", "Rope", ROPE_ANI_SPEED);
	MainSpriteRenderer->CreateAnimation("Ladder", "Ladder", ROPE_ANI_SPEED);
	MainSpriteRenderer->CreateAnimation("Attack1", "Attack1", ATT_ANI_SPEED);
	MainSpriteRenderer->CreateAnimation("Attack2", "Attack2", ATT_ANI_SPEED);
	MainSpriteRenderer->CreateAnimation("Attack3", "Attack3", ATT_ANI_SPEED);
	MainSpriteRenderer->CreateAnimation("Down_Attack", "Down_Attack", DOWN_ATT_ANI_SPEED);
	MainSpriteRenderer->CreateAnimation("Down", "Down");
	MainSpriteRenderer->CreateAnimation("Jump", "Jump");
	MainSpriteRenderer->ChangeAnimation("Idle"); 
	MainSpriteRenderer->AutoSpriteSizeOn();
}

void Player::Update(float _Delta)
{
	ContentActor::Update(_Delta);
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

	if (GameEngineInput::IsDown('1'))
	{
		MainSpriteRenderer->ChangeAnimation("Idle");
	}

	if (GameEngineInput::IsDown('2'))
	{
		MainSpriteRenderer->ChangeAnimation("Walk");
	}

	if (GameEngineInput::IsDown('3'))
	{
		MainSpriteRenderer->ChangeAnimation("Shoot1");
	}

	if (GameEngineInput::IsDown('4'))
	{
		MainSpriteRenderer->ChangeAnimation("Rope");
	}

	if (GameEngineInput::IsDown('5'))
	{
		MainSpriteRenderer->ChangeAnimation("Ladder");
	}

	if (GameEngineInput::IsDown('6'))
	{
		MainSpriteRenderer->ChangeAnimation("Attack1");
	}

	if (GameEngineInput::IsDown('7'))
	{
		MainSpriteRenderer->ChangeAnimation("Attack2");
	}

	if (GameEngineInput::IsDown('8'))
	{
		MainSpriteRenderer->ChangeAnimation("Attack3");
	}

	if (GameEngineInput::IsDown('9'))
	{
		MainSpriteRenderer->ChangeAnimation("Down_Attack");
	}

	if (GameEngineInput::IsDown(VK_MENU))
	{
		MainSpriteRenderer->ChangeAnimation("Jump");
	}

	if (GameEngineInput::IsDown(VK_DOWN))
	{
		MainSpriteRenderer->ChangeAnimation("Down");
	}
}
