#pragma once

#include <Windows.h>
#include <map>
#include <string>
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
class GameEngineInput
{
private:
	class GameEngineKey 
	{
		friend GameEngineInput;

		bool Down = false;
		bool Press = false;
		bool Up = false;
		bool Free = true;

		// 의미가 없다고 봐요.
		float PressTime = 0.0f;

		int Key = -1;

		bool KeyCheck() 
		{
			return 0 != GetAsyncKeyState(Key);
		}

		void Reset() 
		{
			if (true == Press)
			{
				Down = false;
				Press = false;
				Up = true;
				Free = true;
			}
			else if (true == Up)
			{
				Down = false;
				Press = false;
				Up = false;
				Free = true;
			}
		}

		void Update(float _DeltaTime);

	public:
		GameEngineKey() 
			: Key(-1)
		{

		}

		GameEngineKey(int _Key) 
			: Key(_Key)
		{

		}
	};

public:
	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

	static void InputInit();
	static void Update(float _DeltaTime);
	static void Reset();

	static bool IsDown(int _Key, void* _Ptr);
	static bool IsUp(int _Key, void* _Ptr);
	static bool IsPress(int _Key, void* _Ptr);
	static bool IsFree(int _Key, void* _Ptr);

	static void AddInputObject(void* _Ptr);
	static void IsOnlyInputObject(void* _Ptr);

protected:

private:
	static std::map<int, GameEngineKey> AllKeys;
	// 이 주소값인 객체만 입력을 받을거다 
	static std::map<void*, bool> InputObject;
};

#define InputIsDown(Value) GameEngineInput::IsDown(Value, this)
#define InputIsUp(Value) GameEngineInput::IsUp(Value, this)
#define InputIsPress(Value) GameEngineInput::IsPress(Value, this)
#define InputIsFree(Value) GameEngineInput::IsFree(Value, this)
