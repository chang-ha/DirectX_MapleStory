#include "PreCompile.h"
#include "GameEngineCollision.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineCollisionGroup.h"

GameEngineCollision::GameEngineCollision()
{

}

GameEngineCollision::~GameEngineCollision()
{

}

void GameEngineCollision::Start()
{
	GetActor()->GetLevel()->PushCollision(GetDynamic_Cast_This<GameEngineCollision>());
}

void GameEngineCollision::Release()
{
	for (GameEngineCollision* Collision : Others)
	{
		Collision->Others.erase(this);
	}
}

bool GameEngineCollision::Collision(int _Order)
{
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->CollisionGroups[_Order];

	if (nullptr == OtherGroup)
	{
		return false;
	}

	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>());
}

bool GameEngineCollision::Collision(int _Order, const float4& _NextPos)
{
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->CollisionGroups[_Order];

	if (nullptr == OtherGroup)
	{
		return false;
	}

	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _NextPos);
}

bool GameEngineCollision::Collision(int _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
{
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->CollisionGroups[_Order];

	if (nullptr == OtherGroup)
	{
		return false;
	}

	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _Function);
}

bool GameEngineCollision::Collision(int _Order, const float4& _NextPos, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
{
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->CollisionGroups[_Order];

	if (nullptr == OtherGroup)
	{
		return false;
	}

	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _NextPos, _Function);
}

bool GameEngineCollision::CollisionEvent(int _Order, const EventParameter& _Event)
{
	if (false == GetLevel()->CollisionGroups.contains(_Order))
	{
		return false;
	}

	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->CollisionGroups[_Order];

	if (nullptr == OtherGroup)
	{
		return false;
	}

	return OtherGroup->CollisionEvent(GetDynamic_Cast_This<GameEngineCollision>(), _Event);
}
