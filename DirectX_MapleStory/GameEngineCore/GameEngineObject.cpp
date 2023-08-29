#include "PreCompile.h"
#include "GameEngineObject.h"

GameEngineObject::GameEngineObject() 
{
}

GameEngineObject::~GameEngineObject() 
{
}

void GameEngineObject::AllUpdate(float _Delta)
{
	Update(_Delta);

	// ����ִ� �༮���� ���δ� ���Ͱ�����
	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;
		for (std::shared_ptr<GameEngineObject>& _Child : Group)
		{
			if (false == _Child->IsUpdate())
			{
				continue;
			}
			_Child->AddLiveTime(_Delta);
			_Child->Update(_Delta);
		}
	}
}

void GameEngineObject::AllLevelStart(class GameEngineLevel* _PrevLevel)
{
	LevelStart(_PrevLevel);
	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;
		for (std::shared_ptr<GameEngineObject>& _Child : Group)
		{
			if (false == _Child->IsUpdate())
			{
				continue;
			}
			_Child->LevelStart(_PrevLevel);
		}
	}
}
void GameEngineObject::AllLevelEnd(class GameEngineLevel* _NextLevel)
{
	LevelEnd(_NextLevel);
	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;
		for (std::shared_ptr<GameEngineObject>& _Child : Group)
		{
			if (false == _Child->IsUpdate())
			{
				continue;
			}
			_Child->LevelEnd(_NextLevel);
		}
	}
}