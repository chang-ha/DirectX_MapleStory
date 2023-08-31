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
}

void ContentActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	GameEngineColor GroundColor = CurContentLevel->GetCurMap()->GetColor(Transform.GetWorldPosition(), GameEngineColor(255, 255, 255, 255));

	if (GameEngineColor(255, 255, 255, 255) != GroundColor)
	{
		GravityForce.Y -= _Delta * 100.0f;
		Transform.AddLocalPosition(GravityForce * _Delta);
	}
	else
	{
		GravityForce = 0.0f;
	}
}
