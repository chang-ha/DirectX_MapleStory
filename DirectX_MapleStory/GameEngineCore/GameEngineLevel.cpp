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
		// 메인카메라만 프리카메라 기능 사용 가능
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

		// 레퍼런스로 받는다.
		std::shared_ptr<GameEngineCamera>& Camera = CameraPair.second;
		Camera->Render(_Delta);
	}

	LevelRenderTarget->PostEffect(_Delta);

	GameEngineCore::GetBackBufferRenderTarget()->Copy(0, LevelRenderTarget, 0);

	if (true == IsDebug)
	{
		GameEngineCore::GetBackBufferRenderTarget()->Setting();
		// true면 Debug를 그림
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
	// 카메라는 Object의 Childs로도 관리되고 Level의 Cameras로도 관리되고 있어서 Release()를 2번 해줘야함 
	//		<< 아니면 카메라가 관리하는 std::shared_ptr이 메모리에서 절대 안사라짐 (ex : Renderer)
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
		CollisionGroups[_Collision->GetOrder()] = std::make_shared<GameEngineCollisionGroup>();
	}
	CollisionGroups[_Collision->GetOrder()]->PushCollision(_Collision);
}
