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

	GravityForce += _Delta * GravitySpeed;
	if (MAX_GRAVITY <= GravityForce)
	{
		GravityForce = MAX_GRAVITY;
	}
	// MoveVectorForce -= GravityForce * _Delta;
	float Count = 0.0f;
	float GravityForceDelta = GravityForce * _Delta; 
	GameEngineColor GroundColor;
	while (1.0f >= Count && 0.0f >= (MoveVectorForce.Y - GravityForceDelta))
	{
		GroundColor = ContentLevel::CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition() + float4(0, GravityForceDelta * Count), GROUND_COLOR);
		if ((GROUND_COLOR == GroundColor || FLOOR_COLOR == GroundColor))
		{
			break;
		}
		Count += 0.1f;
	}
	if (0 == Count)
	{
		MoveVectorForce.Y -= GravityForceDelta;
	}
	else
	{
		MoveVectorForce.Y -= GravityForceDelta * Count;
	}
	Transform.AddLocalPosition(MoveVectorForce * _Delta);

	if ((GROUND_COLOR == GroundColor || FLOOR_COLOR == GroundColor))
	{
		GravityReset();
		MoveVectorForceReset();
	}

	//GameEngineColor GroundColor = ContentLevel::CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition(), GROUND_COLOR);
	//if ((GROUND_COLOR == GroundColor || FLOOR_COLOR == GroundColor))
	//{
	//	return;
	//}
	// 1. 아래에 박히는 경우
	// -> Vector가 너무 커서 아래에 박혀버림
	// -> 한번에 이동하지 말고 나눠서 이동해야 하나?
	// -> 아님 박혔을때 끌어 올려야 하나?


	// 2. 그냥 지나치는 경우
	// -> 위와 동일하게 Vector가 너무 커서 그냥 지나쳐 버림
	// -> 이것도 위와 비슷하게 해결 가능할듯


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