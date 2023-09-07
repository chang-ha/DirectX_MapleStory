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

	// UIī�޶�
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
		// ���۷����� �޴´�.
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
	// ī�޶�� Object�� Childs�ε� �����ǰ� Level�� Cameras�ε� �����ǰ� �־ Release()�� 2�� ������� 
	//		<< �ƴϸ� ī�޶� �����ϴ� std::shared_ptr�� �޸𸮿��� ���� �Ȼ���� (ex : Renderer)
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
	// Level�� Release()�� ȣ������ ������
	MsgBoxAssert("������ ���� ��Ģ�� �����Ҽ� �����ϴ�.");
}

void GameEngineLevel::PushCollision(std::shared_ptr<GameEngineCollision> _Collision)
{
	if (nullptr == _Collision)
	{
		MsgBoxAssert("�������� �ʴ� �ݸ����� �������� �߽��ϴ�.");
		return;
	}

	if (false == CollisionGroups.contains(_Collision->GetOrder()))
	{
		CollisionGroups[_Collision->GetOrder()] = std::shared_ptr<GameEngineCollisionGroup>();
	}
	CollisionGroups[_Collision->GetOrder()]->PushCollision(_Collision);
}
