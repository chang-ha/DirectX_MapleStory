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
	Gravity(_Delta);
	IsGround = CheckGround();
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
	if (MAX_GRAVITY <= GravityForce)
	{
		GravityForce = MAX_GRAVITY;
	}

	MoveVectorForce.Y -= GravityForce * _Delta;
	if (0.0f > MoveVectorForce.Y)
	{
		float4 MoveVectorForceDelta = MoveVectorForce * _Delta;
		GameEngineColor GroundColor = ContentLevel::CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition(), GROUND_COLOR);
		float Count = 0.0f;
		for (; Count <= static_cast<int>(-MoveVectorForceDelta.Y); Count += 1.0f)
		{
			if (GROUND_COLOR == GroundColor || FLOOR_COLOR == GroundColor)
			{
				break;
			}
			GroundColor = ContentLevel::CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition() - float4(0, 1.0f * Count), GROUND_COLOR);
		}
		if (0 != Count)
		{
			MoveVectorForceDelta.Y = -1.0f * Count;
		}
		Transform.AddLocalPosition(MoveVectorForceDelta);
	}
	else
	{
		Transform.AddLocalPosition(MoveVectorForce * _Delta);
	}


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