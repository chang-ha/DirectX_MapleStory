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

	// 들고있는 녀석들은 전부다 액터겠지만
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
