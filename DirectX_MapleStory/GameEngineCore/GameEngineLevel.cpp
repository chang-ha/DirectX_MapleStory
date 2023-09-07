#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineCore.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineCollisionGroup.h"
#include "GameEngineCollision.h"

GameEngineLevel::GameEngineLevel() 
{
	// Main
	{
		std::shared_ptr<GameEngineCamera> NewCamera = CreateCamera(0, 0);
	}

	{
		std::shared_ptr<GameEngineCamera> NewCamera = CreateCamera(0, 100);
	}

	// UI카메라
	// CreateActor<GameEngineCamera>(100);
}

std::shared_ptr<GameEngineCamera> GameEngineLevel::CreateCamera(int _Order, int _CameraOrder)
{
	std::shared_ptr<GameEngineCamera> NewCamera = CreateActor<GameEngineCamera>(_Order);
	NewCamera->SetCameraOrder(_CameraOrder);
	return NewCamera;
}

GameEngineLevel::~GameEngineLevel() 
{
}

void GameEngineLevel::AllUpdate(float _Delta)
{
	Update(_Delta);

	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;
		float TimeScale = GameEngineCore::MainTime.GetTimeScale(_Pair.first);
		for (std::shared_ptr<GameEngineObject>& _Actor : Group)
		{
			if (false == _Actor->IsUpdate())
			{
				continue;
			}

			_Actor->AddLiveTime(_Delta);
			_Actor->AllUpdate(_Delta);
		}
	}
}

void GameEngineLevel::Render(float _Delta)
{
	for (std::pair<const int, std::shared_ptr<class GameEngineCamera>>& CameraPair : Cameras)
	{
		// 레퍼런스로 받는다.
		std::shared_ptr<GameEngineCamera>& Camera = CameraPair.second;
		Camera->Render(_Delta);
	}
}


void GameEngineLevel::ActorInit(std::shared_ptr<class GameEngineActor> _Actor, int _Order)
{
	_Actor->SetParent(this, _Order);
	_Actor->Start();
}

void GameEngineLevel::AllReleaseCheck()
{
	// 카메라는 Object의 Childs로도 관리되고 Level의 Cameras로도 관리되고 있어서 Release()를 2번 해줘야함 
	//		<< 아니면 카메라가 관리하는 std::shared_ptr이 메모리에서 절대 안사라짐 (ex : Renderer)
	for (std::pair<const int, std::shared_ptr<class GameEngineCamera>>& Pair : Cameras)
	{
		Pair.second->AllReleaseCheck();
	}

	for (std::pair<const int, std::shared_ptr<class GameEngineCollisionGroup>>& Pair : CollisionGroups)
	{
		Pair.second->AllReleaseCheck();
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

void GameEngineLevel::Release()
{
	// Level의 Release()는 호출하지 마세요
	MsgBoxAssert("레벨은 엔진 규칙상 삭제할수 없습니다.");
}

void GameEngineLevel::PushCollision(std::shared_ptr<GameEngineCollision> _Collision)
{
	if (nullptr == _Collision)
	{
		MsgBoxAssert("존재하지 않는 콜리전을 넣으려고 했습니다.");
		return;
	}

	if (false == CollisionGroups.contains(_Collision->GetOrder()))
	{
		CollisionGroups[_Collision->GetOrder()] = std::shared_ptr<GameEngineCollisionGroup>();
	}
	CollisionGroups[_Collision->GetOrder()]->PushCollision(_Collision);
}
