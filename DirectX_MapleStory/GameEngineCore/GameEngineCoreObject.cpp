#include "PreCompile.h"
#include "GameEngineCoreObject.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"

GameEngineCoreObject::GameEngineCoreObject() 
{
}

GameEngineCoreObject::~GameEngineCoreObject() 
{
}

GameEngineLevel* GameEngineCoreObject::GetLevel()
{
	GameEngineObject* Parent = GetParentObject(); 

	while (nullptr != Parent)
	{
		GameEngineLevel* Level = dynamic_cast<GameEngineLevel*>(Parent);
		if (nullptr != Level)
		{
			return Level;
		}

		Parent = Parent->GetParentObject();
	}

	MsgBoxAssert("������ �߰��Ҽ� �������ϴ�.");

	return nullptr;
}

GameEngineActor* GameEngineCoreObject::GetActor()
{
	GameEngineObject* Parent = GetParentObject();

	while (nullptr != Parent)
	{
		GameEngineActor* Actor = dynamic_cast<GameEngineActor*>(Parent);
		if (nullptr != Actor)
		{
			return Actor;
		}

		Parent = Parent->GetParentObject();
	}

	MsgBoxAssert("���͸� �߰��Ҽ� �������ϴ�.");

	return nullptr;
}