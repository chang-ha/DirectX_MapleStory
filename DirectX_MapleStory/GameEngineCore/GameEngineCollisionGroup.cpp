#include "PreCompile.h"
#include "GameEngineCollisionGroup.h"
#include "GameEngineCollision.h"

GameEngineCollisionGroup::GameEngineCollisionGroup()
{

}

GameEngineCollisionGroup::~GameEngineCollisionGroup()
{

}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision)
{
	for (std::shared_ptr<GameEngineCollision> OtherCollision : Collisions)
	{
		if (OtherCollision == _Collision)
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ _Collision->Transform.ColData, OtherCollision->Transform.ColData, _Collision->GetCollisionType(), OtherCollision ->GetCollisionType()}))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision, const float4& _NextPos)
{
	CollisionData Data = _Collision->Transform.ColData;

	Data.OBB.Center.x += _NextPos.X;
	Data.OBB.Center.y += _NextPos.Y;
	Data.OBB.Center.z += _NextPos.Z;

	for (std::shared_ptr<GameEngineCollision> OtherCollision : Collisions)
	{
		if (OtherCollision == _Collision)
		{
			continue;
		}
			
		if (true == GameEngineTransform::Collision({ Data, OtherCollision->Transform.ColData, _Collision->GetCollisionType(), OtherCollision->GetCollisionType() }))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
{
	// 쓰레드에서 문제 발생시 추후 해결할 예정
	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	for (std::shared_ptr<GameEngineCollision> OtherCollision : Collisions)
	{
		if (OtherCollision == _Collision)
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ _Collision->Transform.ColData , OtherCollision->Transform.ColData, _Collision->GetCollisionType(), OtherCollision->GetCollisionType() }))
		{
			ResultCollision.push_back(OtherCollision);
		}
	}

	if (0 != ResultCollision.size())
	{
		_Function(ResultCollision);
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Collision, const float4& _NextPos, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
{
	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	CollisionData Data = _Collision->Transform.ColData;

	Data.OBB.Center.x += _NextPos.X;
	Data.OBB.Center.y += _NextPos.Y;
	Data.OBB.Center.z += _NextPos.Z;

	for (std::shared_ptr<GameEngineCollision> OtherCollision : Collisions)
	{
		if (OtherCollision == _Collision)
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ Data , OtherCollision->Transform.ColData, _Collision->GetCollisionType(), OtherCollision->GetCollisionType() }))
		{
			ResultCollision.push_back(OtherCollision);
		}
	}

	if (0 != ResultCollision.size())
	{
		_Function(ResultCollision);
	}

	return false;
}

bool GameEngineCollisionGroup::CollisionEvent(std::shared_ptr<GameEngineCollision> _Collision, const EventParameter& _Event)
{
	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	for (std::shared_ptr<GameEngineCollision> OtherCollision : Collisions)
	{
		if (OtherCollision == _Collision)
		{
			continue;
		}

		if (true == GameEngineTransform::Collision({ _Collision->Transform.ColData , OtherCollision->Transform.ColData, _Collision->GetCollisionType(), OtherCollision->GetCollisionType() }))
		{
			ResultCollision.push_back(OtherCollision);
			continue;
		}

		// GameEngineCollision* _Other = OtherCollision.get();
		// 충돌은 안했는데 set에 포인터를 가지고 있다 == 충돌중이다가 충돌 끝남
		if (true == _Collision->Others.contains(OtherCollision))
		{
			_Collision->Others.erase(OtherCollision);
			if (nullptr != _Event.Exit)
			{
				_Event.Exit(_Collision.get(), OtherCollision.get());
				// _Other->Others.erase(_Collision.get());
			}
		}
	}

	if (0 != ResultCollision.size())
	{
		// ResultCollision == 나랑 충돌한 애들

		for (int i = 0; i < ResultCollision.size(); i++)
		{
			std::shared_ptr<GameEngineCollision> _Other = ResultCollision[i];
			// GameEngineCollision* _Other = ResultCollision[i].get();
			// 충돌을 했는데 set에 포인터를 가지고 있지 않는다 == 처음 충돌한 애
			if (false == _Collision->Others.contains(_Other))
			{
				_Collision->Others.insert(_Other);
				if (nullptr != _Event.Enter)
				{
					_Event.Enter(_Collision.get(), _Other.get());
					// _Other->Others.insert(_Collision.get());
				}
			}
			else
			{
				// 충돌을 했고, set에 포인터도 들고 있는다 == 충돌중인 애
				if (nullptr != _Event.Stay)
				{
					_Event.Stay(_Collision.get(), _Other.get());
				}
			}
		}
	}

	return false;
}

void GameEngineCollisionGroup::AllReleaseCheck()
{
	std::list<std::shared_ptr<GameEngineCollision>>::iterator StartIter = Collisions.begin();
	std::list<std::shared_ptr<GameEngineCollision>>::iterator EndIter = Collisions.end();

	for (; StartIter != EndIter; )
	{
		if (false == (*StartIter)->IsDeath())
		{
			++StartIter;
			continue;
		}
		StartIter = Collisions.erase(StartIter);
	}
}

void GameEngineCollisionGroup::PushCollision(std::shared_ptr<GameEngineCollision> _Collision)
{
	if (nullptr == _Collision)
	{
		MsgBoxAssert("존재하지 않는 콜리전을 넣으려고 했습니다.");
		return;
	}

	Collisions.push_back(_Collision);
}
