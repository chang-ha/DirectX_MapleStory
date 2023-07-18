#pragma once
#include "GameEngineObject.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// ���� :
class GameEngineCore
{
public:
	static GameEngineTime MainTime;
	static GameEngineWindow MainWindow;

	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();

	// delete Function
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;


	// GameEngineCoreObject�� ��ӹ��� Ŭ������ ���ø����� ��� �����ϴ�.
	template<typename ObjectType>
	static void EngineStart(HINSTANCE _Inst) 
	{
		CoreObject = std::make_shared<ObjectType>();
		EngineProcess(_Inst, ObjectType::GetWindowTitle(), ObjectType::GetStartWindowPos(), ObjectType::GetStartWindowSize());
	}

protected:

private:
	static void EngineProcess(HINSTANCE _Inst, const std::string& _Name, float4 _Pos, float4 _Size);
	static std::shared_ptr<GameEngineObject> CoreObject;

	static void Start();
	static void Update();
	static void Release();
	


};

