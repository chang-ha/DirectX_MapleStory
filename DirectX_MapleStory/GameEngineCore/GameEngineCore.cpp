#include "PreCompile.h"
#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>

std::shared_ptr<GameEngineObject> GameEngineCore::CoreObject;
GameEngineTime GameEngineCore::MainTime;
GameEngineWindow GameEngineCore::MainWindow;


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
	MainTime.Update();

	float DeltaTime = MainTime.GetDeltaTime();

	CoreObject->Update(DeltaTime);
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

	// 시간이나 타임
	GameEngineWindow::MessageLoop(_Inst, Start, Update, Release);
}