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
	// �����忡�� ���� �߻��� ���� �ذ��� ����
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
		// �浹�� ���ߴµ� set�� �����͸� ������ �ִ� == �浹���̴ٰ� �浹 ����
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
		// ResultCollision == ���� �浹�� �ֵ�

		for (int i = 0; i < ResultCollision.size(); i++)
		{
			std::shared_ptr<GameEngineCollision> _Other = ResultCollision[i];
			// GameEngineCollision* _Other = ResultCollision[i].get();
			// �浹�� �ߴµ� set�� �����͸� ������ ���� �ʴ´� == ó�� �浹�� ��
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
				// �浹�� �߰�, set�� �����͵� ��� �ִ´� == �浹���� ��
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
		MsgBoxAssert("�������� �ʴ� �ݸ����� �������� �߽��ϴ�.");
		return;
	}

	Collisions.push_back(_Collision);
}
