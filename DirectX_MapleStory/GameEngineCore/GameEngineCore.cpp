#include "PreCompile.h"
#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>

std::shared_ptr<GameEngineObject> GameEngineCore::CoreObject;
GameEngineTime GameEngineCore::MainTime;
GameEngineWindow GameEngineCore::MainWindow;
GameEngineDevice GameEngineCore::MainDevice;

std::shared_ptr<GameEngineLevel> GameEngineCore::CurLevel;
std::shared_ptr<GameEngineLevel> GameEngineCore::NextLevel;
std::map<std::string, std::shared_ptr<GameEngineLevel>> GameEngineCore::AllLevel;



GameEngineCore::GameEngineCore() 
{
}

GameEngineCore::~GameEngineCore() 
{
}

void GameEngineCore::Start() 
{
	CoreObject->Start();
}

void GameEngineCore::Update() 
{

	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			//CurLevel->LevelEnd(NextLevel);
			//CurLevel->ActorLevelEnd();
		}

		// NextLevel->OverCheck(CurLevel);

		//NextLevel->LevelStart(CurLevel);
		//NextLevel->ActorLevelStart();

		CurLevel = NextLevel;

		NextLevel = nullptr;
		MainTime.Reset();
	}

	MainTime.Update();
	float DeltaTime = MainTime.GetDeltaTime();
	GameEngineSound::Update();
	GameEngineInput::Update(DeltaTime);
	CoreObject->Update(DeltaTime);

	if (true == GameEngineWindow::IsFocus())
	{
		GameEngineInput::Update(DeltaTime);
	}
	else
	{
		GameEngineInput::Reset();
	}

	CurLevel->AddLiveTime(DeltaTime);
	CurLevel->AllUpdate(DeltaTime);

	MainDevice.RenderStart();

	CurLevel->Render(DeltaTime);

	MainDevice.RenderEnd();
}

void GameEngineCore::Release() 
{
	CoreObject->Release();
}

void GameEngineCore::EngineProcess(HINSTANCE _Inst, const std::string& _WindowName, float4 _Pos, float4 _Size)
{
	// 릭체크 해주고
	GameEngineDebug::LeckCheck();

	// 윈도우 만들고
	MainWindow.Open(_WindowName, _Inst);
	MainWindow.SetPosAndScale(_Pos, _Size);
	MainDevice.Initiallize(MainWindow);

	// 시간이나 타임
	GameEngineWindow::MessageLoop(_Inst, Start, Update, Release);
}

void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level)
{
	_Level->Start();
}