#include "PreCompile.h"
#include "GameEngineLevel.h"
#include "GameEngineCore.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineCollisionGroup.h"
#include "GameEngineCollision.h"
#include "GameEngineRenderTarget.h"

bool GameEngineLevel::IsDebug = false;

GameEngineLevel::GameEngineLevel()
{
	// Main
	{
		std::shared_ptr<GameEngineCamera> NewCamera = CreateCamera(INT_MIN, ECAMERAORDER::Main);
		// ����ī�޶� ����ī�޶� ��� ��� ����
		GameEngineInput::AddInputObject(NewCamera.get());
	}

	{
		std::shared_ptr<GameEngineCamera> NewCamera = CreateCamera(INT_MIN, ECAMERAORDER::UI);
	}

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	LevelRenderTarget = GameEngineRenderTarget::Create();
	LevelRenderTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
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

void GameEngineLevel::Start()
{
}

void GameEngineLevel::AllUpdate(float _Delta)
{
	GameEngineDebug::GameEngineDebugCore::CurLevel = this;

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
			_Actor->AddLiveTime(_Delta * TimeScale);
			_Actor->AllUpdate(_Delta * TimeScale);
		}
	}
}

void GameEngineLevel::Render(float _Delta)
{
	LevelRenderTarget->Clear();
		
	for (std::pair<const int, std::shared_ptr<class GameEngineCamera>>& CameraPair : Cameras)
	{
		if (nullptr == CameraPair.second)
		{
			continue;
		}

		// ���۷����� �޴´�.
		std::shared_ptr<GameEngineCamera>& Camera = CameraPair.second;
		Camera->Render(_Delta);
	}

	LevelRenderTarget->PostEffect(_Delta);

	GameEngineCore::GetBackBufferRenderTarget()->Copy(0, LevelRenderTarget, 0);

	if (true == IsDebug)
	{
		GameEngineCore::GetBackBufferRenderTarget()->Setting();
		// true�� Debug�� �׸�
		GameEngineDebug::GameEngineDebugCore::DebugRender();
	}
}


void GameEngineLevel::ActorInit(std::shared_ptr<class GameEngineActor> _Actor, int _Order, std::string_view _Name/* = ""*/)
{
	_Actor->SetName(_Name);
	_Actor->SetParent(this, _Order);
	_Actor->Start();
}

void GameEngineLevel::AllReleaseCheck()
{
	// ī�޶�� Object�� Childs�ε� �����ǰ� Level�� Cameras�ε� �����ǰ� �־ Release()�� 2�� ������� 
	//		<< �ƴϸ� ī�޶� �����ϴ� std::shared_ptr�� �޸𸮿��� ���� �Ȼ���� (ex : Renderer)
	for (std::pair<const int, std::shared_ptr<class GameEngineCamera>>& Pair : Cameras)
	{
		if (nullptr == Pair.second)
		{
			continue;
		}

		Pair.second->AllReleaseCheck();
	}

	for (std::pair<const int, std::shared_ptr<class GameEngineCollisionGroup>>& Pair : CollisionGroups)
	{
		if (nullptr == Pair.second)
		{
			continue;
		}

		Pair.second->AllReleaseCheck();
	}

	for (std::pair<const int, std::list<std::shared_ptr<GameEngineObject>>>& _Pair : Childs)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = _Pair.second;

		std::list<std::shared_ptr<GameEngineObject>>::iterator Start = Group.begin();
		std::list<std::shared_ptr<GameEngineObject>>::iterator End = Group.end();

		for (; Start != End;)
		{
			(*Start)->AllReleaseCheck();

			if (false == (*Start)->IsDeath())
			{
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
		CollisionGroups[_Collision->GetOrder()] = std::make_shared<GameEngineCollisionGroup>();
	}
	CollisionGroups[_Collision->GetOrder()]->PushCollision(_Collision);
}
