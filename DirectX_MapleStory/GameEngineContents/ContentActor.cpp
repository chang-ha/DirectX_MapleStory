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
	ContentLevel* CurLevel = dynamic_cast<ContentLevel*>(GetLevel());
	CurContentLevel = std::shared_ptr<ContentLevel>(CurLevel);
}

void ContentActor::Update(float _Delta)
{
	Gravity(_Delta);
	// AirResistence(_Delta);
}

void ContentActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	GravityForce.Y -= _Delta * GravitySpeed;
	Transform.AddLocalPosition(GravityForce * _Delta);

	GameEngineColor GroundColor = CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition(), GameEngineColor(255, 255, 255, 255));
	if (GameEngineColor(255, 255, 255, 255) == GroundColor && GravityForce.Y <= 0.0f)
	{
		GravityReset();
	}

	//if (GameEngineColor(255, 255, 255, 255) != GroundColor)
	//{
	//	GravityForce.Y -= _Delta * GravitySpeed;
	//	Transform.AddLocalPosition(GravityForce * _Delta);
	//}
	//else
	//{
	//	GravityReset();
	//}
}

//void ContentActor::AirResistence(float _Delta)
//{
//	if (0 == GravityForce.Y)
//	{
//		return;
//	}
//
//	if (0 > GravityForce.X)
//	{
//		GravityForce.X += AIR_RES_SPEED * _Delta;
//		if (0 <= GravityForce.X)
//		{
//			GravityForce.X = 0.0f;
//		}
//	}
//	else if (0 < GravityForce.X)
//	{
//		GravityForce.X -= AIR_RES_SPEED * _Delta;
//		if (0 >= GravityForce.X)
//		{
//			GravityForce.X = 0.0f;
//		}
//	}
//}
