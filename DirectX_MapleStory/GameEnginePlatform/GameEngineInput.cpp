#include "PreCompile.h"
#include "GameEngineInput.h"
#include <GameEngineBase/GameEngineDebug.h>

std::map<int, GameEngineInput::GameEngineKey> GameEngineInput::AllKeys;

GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}


class InputSystemCreator
{
public:
	InputSystemCreator()
	{
		GameEngineInput::InputInit();
	}
};

InputSystemCreator InputInitInst;

void GameEngineInput::InputInit()
{
	static bool Check = false;

	if (true == Check)
	{
		return;
	}


	AllKeys[VK_LBUTTON] = GameEngineKey(VK_LBUTTON);
	AllKeys[VK_RBUTTON] = GameEngineKey(VK_RBUTTON);
	AllKeys[VK_CANCEL] = GameEngineKey(VK_CANCEL);
	AllKeys[VK_MBUTTON] = GameEngineKey(VK_MBUTTON);
	AllKeys[VK_BACK] = GameEngineKey(VK_BACK);
	AllKeys[VK_TAB] = GameEngineKey(VK_TAB);
	AllKeys[VK_CLEAR] = GameEngineKey(VK_CLEAR);
	AllKeys[VK_RETURN] = GameEngineKey(VK_RETURN);
	AllKeys[VK_SHIFT] = GameEngineKey(VK_SHIFT);
	AllKeys[VK_CONTROL] = GameEngineKey(VK_CONTROL);
	AllKeys[VK_MENU] = GameEngineKey(VK_MENU);
	AllKeys[VK_PAUSE] = GameEngineKey(VK_PAUSE);
	AllKeys[VK_CAPITAL] = GameEngineKey(VK_CAPITAL);
	AllKeys[VK_KANA] = GameEngineKey(VK_KANA);
	AllKeys[VK_HANGEUL] = GameEngineKey(VK_HANGEUL);
	AllKeys[VK_HANGUL] = GameEngineKey(VK_HANGUL);
	AllKeys[VK_IME_ON] = GameEngineKey(VK_IME_ON);
	AllKeys[VK_JUNJA] = GameEngineKey(VK_JUNJA);
	AllKeys[VK_FINAL] = GameEngineKey(VK_FINAL);
	AllKeys[VK_HANJA] = GameEngineKey(VK_HANJA);
	AllKeys[VK_KANJI] = GameEngineKey(VK_KANJI);
	AllKeys[VK_IME_OFF] = GameEngineKey(VK_IME_OFF);
	AllKeys[VK_ESCAPE] = GameEngineKey(VK_ESCAPE);
	AllKeys[VK_CONVERT] = GameEngineKey(VK_CONVERT);
	AllKeys[VK_NONCONVERT] = GameEngineKey(VK_NONCONVERT);
	AllKeys[VK_ACCEPT] = GameEngineKey(VK_ACCEPT);
	AllKeys[VK_MODECHANGE] = GameEngineKey(VK_MODECHANGE);
	AllKeys[VK_SPACE] = GameEngineKey(VK_SPACE);
	AllKeys[VK_PRIOR] = GameEngineKey(VK_PRIOR);
	AllKeys[VK_NEXT] = GameEngineKey(VK_NEXT);
	AllKeys[VK_END] = GameEngineKey(VK_END);
	AllKeys[VK_HOME] = GameEngineKey(VK_HOME);
	AllKeys[VK_LEFT] = GameEngineKey(VK_LEFT);
	AllKeys[VK_UP] = GameEngineKey(VK_UP);
	AllKeys[VK_RIGHT] = GameEngineKey(VK_RIGHT);
	AllKeys[VK_DOWN] = GameEngineKey(VK_DOWN);
	AllKeys[VK_SELECT] = GameEngineKey(VK_SELECT);
	AllKeys[VK_PRINT] = GameEngineKey(VK_PRINT);
	AllKeys[VK_EXECUTE] = GameEngineKey(VK_EXECUTE);
	AllKeys[VK_SNAPSHOT] = GameEngineKey(VK_SNAPSHOT);
	AllKeys[VK_INSERT] = GameEngineKey(VK_INSERT);
	AllKeys[VK_DELETE] = GameEngineKey(VK_DELETE);
	AllKeys[VK_HELP] = GameEngineKey(VK_HELP);
	AllKeys[VK_LWIN] = GameEngineKey(VK_LWIN);
	AllKeys[VK_RWIN] = GameEngineKey(VK_RWIN);
	AllKeys[VK_APPS] = GameEngineKey(VK_APPS);
	AllKeys[VK_SLEEP] = GameEngineKey(VK_SLEEP);
	AllKeys[VK_NUMPAD0] = GameEngineKey(VK_NUMPAD0);
	AllKeys[VK_NUMPAD1] = GameEngineKey(VK_NUMPAD1);
	AllKeys[VK_NUMPAD2] = GameEngineKey(VK_NUMPAD2);
	AllKeys[VK_NUMPAD3] = GameEngineKey(VK_NUMPAD3);
	AllKeys[VK_NUMPAD4] = GameEngineKey(VK_NUMPAD4);
	AllKeys[VK_NUMPAD5] = GameEngineKey(VK_NUMPAD5);
	AllKeys[VK_NUMPAD6] = GameEngineKey(VK_NUMPAD6);
	AllKeys[VK_NUMPAD7] = GameEngineKey(VK_NUMPAD7);
	AllKeys[VK_NUMPAD8] = GameEngineKey(VK_NUMPAD8);
	AllKeys[VK_NUMPAD9] = GameEngineKey(VK_NUMPAD9);
	AllKeys[VK_MULTIPLY] = GameEngineKey(VK_MULTIPLY);
	AllKeys[VK_ADD] = GameEngineKey(VK_ADD);
	AllKeys[VK_SEPARATOR] = GameEngineKey(VK_SEPARATOR);
	AllKeys[VK_SUBTRACT] = GameEngineKey(VK_SUBTRACT);
	AllKeys[VK_DECIMAL] = GameEngineKey(VK_DECIMAL);
	AllKeys[VK_DIVIDE] = GameEngineKey(VK_DIVIDE);
	AllKeys[VK_F1] = GameEngineKey(VK_F1);
	AllKeys[VK_F2] = GameEngineKey(VK_F2);
	AllKeys[VK_F3] = GameEngineKey(VK_F3);
	AllKeys[VK_F4] = GameEngineKey(VK_F4);
	AllKeys[VK_F5] = GameEngineKey(VK_F5);
	AllKeys[VK_F6] = GameEngineKey(VK_F6);
	AllKeys[VK_F7] = GameEngineKey(VK_F7);
	AllKeys[VK_F8] = GameEngineKey(VK_F8);
	AllKeys[VK_F9] = GameEngineKey(VK_F9);
	AllKeys[VK_F10] = GameEngineKey(VK_F10);
	AllKeys[VK_F11] = GameEngineKey(VK_F11);
	AllKeys[VK_F12] = GameEngineKey(VK_F12);
	AllKeys[VK_F13] = GameEngineKey(VK_F13);
	AllKeys[VK_F14] = GameEngineKey(VK_F14);
	AllKeys[VK_F15] = GameEngineKey(VK_F15);
	AllKeys[VK_F16] = GameEngineKey(VK_F16);
	AllKeys[VK_F17] = GameEngineKey(VK_F17);
	AllKeys[VK_F18] = GameEngineKey(VK_F18);
	AllKeys[VK_F19] = GameEngineKey(VK_F19);
	AllKeys[VK_F20] = GameEngineKey(VK_F20);
	AllKeys[VK_F21] = GameEngineKey(VK_F21);
	AllKeys[VK_F22] = GameEngineKey(VK_F22);
	AllKeys[VK_F23] = GameEngineKey(VK_F23);
	AllKeys[VK_F24] = GameEngineKey(VK_F24);

	for (int i = 'A'; i <= 'Z'; i++)
	{
		AllKeys[i] = GameEngineKey(i);
	}

	for (int i = '0'; i <= '9'; i++)
	{
		AllKeys[i] = GameEngineKey(i);
	}

	AllKeys['-'] = GameEngineKey(VK_OEM_MINUS);
	AllKeys['='] = GameEngineKey(VK_OEM_PLUS);
	AllKeys[VK_OEM_4] = GameEngineKey(VK_OEM_4); // '['
	AllKeys[VK_OEM_6] = GameEngineKey(VK_OEM_6); // ']'
	// AllKeys['='] = GameEngineKey('=');
}


void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	if (true == KeyCheck())
	{
		// 키가 눌렸다.

		PressTime += _DeltaTime;

		// 여태까지 키가 눌렸던적이 없다는 거죠.
		if (true == Free)
		{
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else if (true == Down)
		{
			Down = false;
			Press = true;
			Up = false;
			Free = false;
		}

	}
	else
	{
		PressTime = 0.0f;
		// 키가 눌리지 않았다.
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
}

void GameEngineInput::Reset()
{
	std::map<int, GameEngineKey>::iterator StartIter = AllKeys.begin();
	std::map<int, GameEngineKey>::iterator EndIter = AllKeys.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		StartIter->second.Reset();
	}

}

void GameEngineInput::Update(float _DeltaTime)
{
	std::map<int, GameEngineKey>::iterator StartIter = AllKeys.begin();
	std::map<int, GameEngineKey>::iterator EndIter = AllKeys.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		StartIter->second.Update(_DeltaTime);
	}

}

bool GameEngineInput::IsDown(int _Key)
{
	if (AllKeys.end() == AllKeys.find(_Key))
	{
		MsgBoxAssert("아직 처리하지 못하는 키입니다." + std::to_string(_Key));
	}

	return AllKeys[_Key].Down;
}
bool GameEngineInput::IsUp(int _Key)
{
	if (AllKeys.end() == AllKeys.find(_Key))
	{
		MsgBoxAssert("아직 처리하지 못하는 키입니다." + std::to_string(_Key));
	}

	return AllKeys[_Key].Up;
}
bool GameEngineInput::IsPress(int _Key)
{
	if (AllKeys.end() == AllKeys.find(_Key))
	{
		MsgBoxAssert("아직 처리하지 못하는 키입니다." + std::to_string(_Key));
	}

	return AllKeys[_Key].Press;
}
bool GameEngineInput::IsFree(int _Key)
{
	if (AllKeys.end() == AllKeys.find(_Key))
	{
		MsgBoxAssert("아직 처리하지 못하는 키입니다." + std::to_string(_Key));
	}

	return AllKeys[_Key].Free;
}

