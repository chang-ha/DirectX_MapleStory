#pragma once
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

// 설명 :
class GameEngineCore
{
	friend class GameEngineLevel;

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


	// GameEngineCoreObject를 상속받은 클래스만 템플릿으로 사용 가능하다.
	template<typename ObjectType>
	static void EngineStart(HINSTANCE _Inst) 
	{
		CoreObject = std::make_shared<ObjectType>();
		EngineProcess(_Inst, ObjectType::GetWindowTitle(), ObjectType::GetStartWindowPos(), ObjectType::GetStartWindowSize());
	}


	template<typename LevelType>
	static void CreateLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		// 이미 내부에 TitleLevel이 존재한다.
		if (AllLevel.end() != AllLevel.find(Upper))
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel은 이미 존재합니다.");
			return;
		}

		std::shared_ptr<GameEngineLevel> NewLevel = std::make_shared<LevelType>();
		LevelInit(NewLevel);
		AllLevel.insert(std::make_pair(Upper, NewLevel));
	}

	static void ChangeLevel(const std::string& _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);

		std::map<std::string, std::shared_ptr<GameEngineLevel>>::iterator Finditer = AllLevel.find(Upper);

		// 이미 내부에 TitleLevel이 존재한다.
		if (AllLevel.end() == Finditer)
		{
			MsgBoxAssert(Upper + "의 이름을 가진 GameEngineLevel은 존재하지 않습니다.");
			return;
		}

		NextLevel = Finditer->second;
	}

protected:

private:


	static void EngineProcess(HINSTANCE _Inst, const std::string& _Name, float4 _Pos, float4 _Size);
	static std::shared_ptr<GameEngineObject> CoreObject;

	static void LevelInit(std::shared_ptr<GameEngineLevel> _Level);

	static std::shared_ptr<GameEngineLevel> CurLevel;
	static std::shared_ptr<GameEngineLevel> NextLevel;
	static std::map<std::string, std::shared_ptr<GameEngineLevel>> AllLevel;


	static void Start();
	static void Update();
	static void Release();
	


};

