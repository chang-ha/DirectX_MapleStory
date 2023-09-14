#include "PreCompile.h"
#include "ContentActor.h"
#include "ContentLevel.h"
#include "ContentMap.h"

ContentActor::ContentActor()
{

}

ContentActor::~ContentActor()
{
}

void ContentActor::Start()
{
	// std::shared_ptr<GameEngineLevel> CurLevel = std::make_shared<GameEngineLevel>(GetLevel());
	// CurContentLevel = std::dynamic_pointer_cast<ContentLevel>(CurLevel);
	// ContentLevel* CurLevel = dynamic_cast<ContentLevel*>(GetLevel());
	// if (nullptr != CurLevel)
	// {
	// 	CurContentLevel = std::make_shared<ContentLevel>(CurLevel);
	// }
}

void ContentActor::Update(float _Delta)
{
	IsGround = CheckGround();
	Gravity(_Delta); // AddLocalPosition for MoveVector.Y
	AirResistance(_Delta);
}

void ContentActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	if (true == IsGround && 0 >= MoveVectorForce.Y)
	{
		return;
	}

	GravityForce += GravitySpeed * _Delta;
	if (MAX_GRAVITY_FORCE <= GravityForce)
	{
		GravityForce = MAX_GRAVITY_FORCE;
	}

	MoveVectorForce.Y -= GravityForce * _Delta;
	float MoveVectorForceDelta = MoveVectorForce.Y * _Delta;
	if (MAX_GRAVITY <= MoveVectorForceDelta)
	{
		MoveVectorForceDelta = MAX_GRAVITY;
	}
	if (0.0f > MoveVectorForce.Y)
	{
		GameEngineColor GroundColor = CheckGroundColor();
		float Count = 0.0f;
		for (; Count <= static_cast<int>(-MoveVectorForceDelta); Count += 1.0f)
		{
			if (GROUND_COLOR == GroundColor || FLOOR_COLOR == GroundColor)
			{
				break;
			}
			GroundColor = CheckGroundColor(-float4(0, 1.0f * Count));
		}
		if (0 != Count)
		{
			MoveVectorForceDelta = -1.0f * Count;
		}
		Transform.AddLocalPosition(float4(0, MoveVectorForceDelta));
	}
	else
	{
		Transform.AddLocalPosition(float4(0, MoveVectorForceDelta));
	}
}

void ContentActor::AirResistance(float _Delta)
{
	if (true == IsAirResis)
	{
		switch (AirResisDir)
		{
		case ActorDir::Right:
			MoveVectorForce.X += -ResistanceForce * _Delta;
			if (0.0f >= MoveVectorForce.X)
			{
				MoveVectorForce.X = 0.0f;
			}
			break;
		case ActorDir::Left:
			MoveVectorForce.X += ResistanceForce * _Delta;
			if (0.0f <= MoveVectorForce.X)
			{
				MoveVectorForce.X = 0.0f;
			}
			break;
		case ActorDir::Null:
		default:
			break;
		}

	}

	Transform.AddLocalPosition(float4(MoveVectorForce.X * _Delta, 0));
}

bool ContentActor::CheckGround(float4 PlusCheckPos /*= float4::ZERO*/)
{
	bool Result = false;
	GameEngineColor CheckColor = ContentLevel::CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition() + PlusCheckPos, GROUND_COLOR);
	if (GROUND_COLOR == CheckColor || FLOOR_COLOR == CheckColor)
	{
		Result = true;
	}
	else
	{
		Result = false;
	}

	return Result;
}

GameEngineColor ContentActor::CheckGroundColor(float4 PlusCheckPos /*= float4::ZERO*/)
{
	GameEngineColor CheckColor = ContentLevel::CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition() + PlusCheckPos, GROUND_COLOR);
	return CheckColor;
}