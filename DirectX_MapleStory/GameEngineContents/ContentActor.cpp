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
}

void ContentActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	GameEngineColor GroundColor = ContentLevel::CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition(), GameEngineColor(255, 255, 255, 255));
	if (GameEngineColor(255, 255, 255, 255) == GroundColor && GravityForce.Y <= 0.0f)
	{
		GravityReset();
		return;
	}

	GravityForce.Y -= _Delta * GravitySpeed;
	Transform.AddLocalPosition(GravityForce * _Delta);
}