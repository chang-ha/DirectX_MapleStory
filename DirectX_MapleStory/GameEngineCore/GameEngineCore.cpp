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
	// ��üũ ���ְ�
	GameEngineDebug::LeckCheck();

	// ������ �����
	MainWindow.Open(_WindowName, _Inst);
	MainWindow.SetPosAndScale(_Pos, _Size);

	// �ð��̳� Ÿ��
	GameEngineWindow::MessageLoop(_Inst, Start, Update, Release);
}