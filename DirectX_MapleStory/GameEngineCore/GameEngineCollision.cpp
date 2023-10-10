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

void GameEngineCollision::Update(float _Delta)
{
	// 함수는 호출되는것 만으로 이미 처리를 한겁니다.
	if (true == GameEngineLevel::IsDebug)
	{
		switch (CollisionType)
		{
		case ColType::SPHERE2D:
			GameEngineDebug::DrawSphere2D(Transform);
			break;
		case ColType::AABBBOX2D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::OBBBOX2D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::SPHERE3D:
			GameEngineDebug::DrawSphere2D(Transform);
			break;
		case ColType::AABBBOX3D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::OBBBOX3D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::MAX:
			break;
		default:
			break;
		}
	}
}

void GameEngineCollision::Release()
{
	//for (GameEngineCollision* Collision : Others)
	//{
	//	Collision->Others.erase(this);
	//}
}

bool GameEngineCollision::Collision(int _Order)
{
	if (false == GetLevel()->CollisionGroups.contains(_Order))
	{
		return false;
	}
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->CollisionGroups[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>());
}

bool GameEngineCollision::Collision(int _Order, const float4& _NextPos)
{
	if (false == GetLevel()->CollisionGroups.contains(_Order))
	{
		return false;
	}
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->CollisionGroups[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _NextPos);
}

bool GameEngineCollision::Collision(int _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
{
	if (false == GetLevel()->CollisionGroups.contains(_Order))
	{
		return false;
	}
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->CollisionGroups[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _Function);
}

bool GameEngineCollision::Collision(int _Order, const float4& _NextPos, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
{
	if (false == GetLevel()->CollisionGroups.contains(_Order))
	{
		return false;
	}
	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->CollisionGroups[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _NextPos, _Function);
}

bool GameEngineCollision::CollisionEvent(int _Order, const EventParameter& _Event)
{
	if (false == GetLevel()->CollisionGroups.contains(_Order))
	{
		return false;
	}

	std::shared_ptr<GameEngineCollisionGroup> OtherGroup = GetLevel()->CollisionGroups[_Order];

	std::set<std::shared_ptr<GameEngineCollision>>::iterator Start = Others.begin();
	std::set<std::shared_ptr<GameEngineCollision>>::iterator End = Others.end();

	for (; Start != End; )
	{
		std::shared_ptr<GameEngineCollision> OtherCol = *Start;

		// 여기서 터질것이다.
		if (false == OtherCol->IsDeath())
		{
			++Start;
			continue;
		}

		Start = Others.erase(Start);
	}

	return OtherGroup->CollisionEvent(GetDynamic_Cast_This<GameEngineCollision>(), _Event);
}
