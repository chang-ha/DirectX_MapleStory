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

void GameEngineObject::AllReleaseCheck()
{
	if (true == IsDeath())
	{
		AllRelease();
		return;
	}
	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;

		std::list<std::shared_ptr<GameEngineObject>>::iterator Start = Group.begin();
		std::list<std::shared_ptr<GameEngineObject>>::iterator End = Group.end();

		for (; Start != End;)
		{
			if (false == (*Start)->IsDeath())
			{
				(*Start)->AllReleaseCheck();
				++Start;
				continue;
			}
			Start = Group.erase(Start);
		}
	}

}

void GameEngineObject::AllLevelStart(GameEngineLevel* _PrevLevel)
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
void GameEngineObject::AllLevelEnd(GameEngineLevel* _NextLevel)
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

void GameEngineObject::AllRelease()
{
	Release();

	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;
		for (std::shared_ptr<GameEngineObject> Object : Group)
		{
			Object->IsDeathValue = true;
			Object->Parent = nullptr;
			Object->AllRelease();
		}
	}
}