#include "PreCompile.h"
#include "Player.h"
#include "ContentMap.h"
#include "SkillManager.h"
#include "Arrow.h"

#define JUMP_HEIGHT 500.0f
#define JUMP_DIS 200.0f

#define DOUBLE_JUMP_DIS 300.0f
#define DOUBLE_JUMP_HEIGHT 120.0f

#define LADDER_JUMP_HEIGHT 300.0f

#define WINDWALK_XVECTOR 1000.0f

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
	}
	else if (PlayerState::Ladder == State)
	{
		if (/*ActorDir::Left == Dir &&*/ GameEngineInput::IsPress(VK_LEFT, this))
		{
			PlusMoveVectorForce(float4(-JUMP_DIS, LADDER_JUMP_HEIGHT));
		}
		else if (/*ActorDir::Right == Dir &&*/ GameEngineInput::IsPress(VK_RIGHT, this))
		{
			PlusMoveVectorForce(float4(JUMP_DIS, LADDER_JUMP_HEIGHT));
		}
	}
}

void Player::DownStart()
{
	MainSpriteRenderer->ChangeAnimation("Down");
}

void Player::LadderStart()
{
	float4 CurPos = Transform.GetWorldPosition();
	Transform.SetLocalPosition(float4(CurPos.X + LadderPivot, CurPos.Y, CurPos.Z));
	MainSpriteRenderer->ChangeAnimation("Ladder");
	GravityOff();
}

void Player::AttackStart()
{
	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("Shoot");
	AlertTime = ALERT_TIME;
}

void Player::ShootingStart()
{
	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("Shooting");
	SkillManager::PlayerSkillManager->UseSkill("SongOfHeaven");
	AlertTime = ALERT_TIME;
}

void Player::Attack2Start()
{
	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("FairySpiral");
	SkillManager::PlayerSkillManager->UseSkill("FairySpiral");
	AlertTime = ALERT_TIME;
}

void Player::WindWalkStart()
{
	IsDirCheck = false;
	SkillManager::PlayerSkillManager->UseSkill("WindWalk");
	if (true == IsGround)
	{
		MainSpriteRenderer->ChangeAnimation("WindWalk");
	}
	else
	{
		MainSpriteRenderer->ChangeAnimation("Jump");
	}
	MoveVectorForceReset();
	GravityOff();
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

void Player::ShootStart()
{
	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("Shoot");
	SkillManager::PlayerSkillManager->UseSkill("HowlingGale");
	AlertTime = ALERT_TIME;
}

void Player::VortexSphereStart()
{
	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("VortexSphere");
	SkillManager::PlayerSkillManager->UseSkill("VortexSphere");
	AlertTime = ALERT_TIME;
}

void Player::MercilessWindsStart()
{
	IsDirCheck = false;
	MainSpriteRenderer->ChangeAnimation("MercilessWinds");
	SkillManager::PlayerSkillManager->UseSkill("MercilessWinds");
	AlertTime = ALERT_TIME;
}

void Player::MonsoonStart()
{
	MainSpriteRenderer->ChangeAnimation("Monsoon");
	SkillManager::PlayerSkillManager->UseSkill("Monsoon");
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

}

void Player::LadderEnd()
{
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

void Player::AttackEnd()
{
	IsDirCheck = true;
}

void Player::ShootingEnd()
{
	IsDirCheck = true;
}

void Player::Attack2End()
{
	IsDirCheck = true;
}

void Player::WindWalkEnd()
{
	IsDirCheck = true;
	MoveVectorForceReset();
	GravityOn();
	AirResisOff();
}

void Player::ShootEnd()
{
	IsDirCheck = true;
	// MainSpriteRenderer->ChangeAnimation("Shoot");
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

}

void Player::IdleUpdate(float _Delta)
{
	if (State == PlayerState::Idle && 0.0f < AlertTime)
	{
		ChangeState(PlayerState::Alert);
		return;
	}

	///////////// Skill Code
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::WindWalk);
		return;
	}

	if (GameEngineInput::IsPress('A', this))
	{
		ChangeState(PlayerState::Shooting);
		return;
	}

	if (GameEngineInput::IsDown('F', this))
	{
		ChangeState(PlayerState::Shoot);
		return;
	}


	if (GameEngineInput::IsDown(VK_SHIFT, this) || GameEngineInput::IsPress(VK_SHIFT, this))
	{
		ChangeState(PlayerState::Attack2);
		return;
	}

	if (true == GameEngineInput::IsPress('S', this))
	{
		ChangeState(PlayerState::VortexSphere);
		return;
	}

	if (true == GameEngineInput::IsDown('E', this))
	{
		SkillManager::PlayerSkillManager->UseSkill("PhalanxCharge");
		AlertTime = ALERT_TIME;
		return;
	}

	if (true == GameEngineInput::IsDown('R', this))
	{
		ChangeState(PlayerState::MercilessWinds);
		return;
	}

	if (true == GameEngineInput::IsDown('W', this))
	{
		ChangeState(PlayerState::Monsoon);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_CONTROL, this))
	{
		ChangeState(PlayerState::Attack);
		return;
	}
	/////////////

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
	///////////// Skill Code
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::WindWalk);
		return;
	}

	if (GameEngineInput::IsPress('A', this))
	{
		ChangeState(PlayerState::Shooting);
		return;
	}

	if (GameEngineInput::IsDown('F', this))
	{
		ChangeState(PlayerState::Shoot);
		return;
	}


	if (GameEngineInput::IsDown(VK_SHIFT, this) || GameEngineInput::IsPress(VK_SHIFT, this))
	{
		ChangeState(PlayerState::Attack2);
		return;
	}

	if (true == GameEngineInput::IsPress('S', this))
	{
		ChangeState(PlayerState::VortexSphere);
		return;
	}

	if (true == GameEngineInput::IsDown('E', this))
	{
		SkillManager::PlayerSkillManager->UseSkill("PhalanxCharge");
		AlertTime = ALERT_TIME;
		return;
	}

	if (true == GameEngineInput::IsDown('R', this))
	{
		ChangeState(PlayerState::MercilessWinds);
		return;
	}

	if (true == GameEngineInput::IsDown('W', this))
	{
		ChangeState(PlayerState::Monsoon);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_CONTROL, this))
	{
		ChangeState(PlayerState::Attack);
		return;
	}
	/////////////

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

	if ((GameEngineInput::IsPress(VK_LEFT, this) || GameEngineInput::IsPress(VK_RIGHT, this)))
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
	///////////// Skill Code
	if (GameEngineInput::IsDown(VK_SPACE, this))
	{
		ChangeState(PlayerState::WindWalk);
		return;
	}

	if (GameEngineInput::IsDown(VK_SHIFT, this) || GameEngineInput::IsPress(VK_SHIFT, this))
	{
		ChangeState(PlayerState::Attack2);
		return;
	}

	if (true == GameEngineInput::IsPress('S', this))
	{
		ChangeState(PlayerState::VortexSphere);
		return;
	}

	if (true == GameEngineInput::IsDown('R', this))
	{
		ChangeState(PlayerState::MercilessWinds);
		return;
	}

	if (true == GameEngineInput::IsDown('W', this))
	{
		ChangeState(PlayerState::Monsoon);
		return;
	}
	/////////////

	if (true == IsGround && 0 >= GetMoveVectorForce().Y)
	{
		ChangeToIdle();
		//GravityReset();
		//MoveVectorForceReset();
		//GroundJump = false;
		//DoubleJump = false;
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

	if (GameEngineInput::IsDown('D', this))
	{
		GravityReset();
		SkillManager::PlayerSkillManager->UseSkill("DoubleJump");
		DoubleJump = true;
		if (GameEngineInput::IsPress(VK_UP, this))
		{
			PlusMoveVectorForce(float4(0, JUMP_HEIGHT * 1.3f));
		}
		else if (GameEngineInput::IsPress(VK_LEFT, this))
		{
			PlusMoveVectorForce(float4(-DOUBLE_JUMP_DIS, DOUBLE_JUMP_HEIGHT));
		}
		else if (GameEngineInput::IsPress(VK_RIGHT, this))
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
	}
}

void Player::DownUpdate(float _Delta)
{
	if (GameEngineInput::IsFree(VK_DOWN, this) || GameEngineInput::IsUp(VK_DOWN, this))
	{
		ChangeToIdle();
		return;
	}

	else if (GameEngineInput::IsDown('D', this) || GameEngineInput::IsPress('D', this))
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
		if (GameEngineInput::IsDown('D', this))
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
		ChangeToIdle();
		return;
	}
}

void Player::AttackUpdate(float _Delta)
{
	if (true == MainSpriteRenderer->IsCurAnimationEnd())
	{
		GetLevel()->CreateActor<Arrow>(UpdateOrder::Arrow);
		ChangeToIdle();
	}
}

void Player::ShootingUpdate(float _Delta)
{
	if (true == GameEngineInput::IsFree('A', this))
	{
		SkillManager::PlayerSkillManager->EndSkill("SongOfHeaven");
		ChangeToIdle();
	}
}

void Player::Attack2Update(float _Delta)
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
	float4 MovePos = GetMoveVectorForce().X * _Delta;
	GameEngineColor CheckColor = GROUND_COLOR;

	if (0.0f == GetMoveVectorForce().X)
	{
		ChangeToIdle();
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
}

void Player::ShootUpdate(float _Delta)
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
