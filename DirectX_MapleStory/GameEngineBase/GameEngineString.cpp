#include "PreCompile.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"
#include <Windows.h>

GameEngineString::GameEngineString() 
{
}

GameEngineString::~GameEngineString() 
{
}

// "" => L""

std::wstring GameEngineString::AnsiToUnicode(std::string_view _Text)
{
	// CP_ACP 운영체제가 사용하는거니
	// 아무것도 넣지 않으면 => _Text.c_str()이 몇바이트가 되어야 widechar로 변환할수 있는지를 리턴해줍니다.
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열을 변환할수가 없습니다.");
		return L"";
	}

	// _Text 10
	// Size 30

	std::wstring Result;
	Result.resize(Size);


	Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("문자열을 변환에 실패했습니다.");
		return L"";
	}

	return Result;
}

std::string GameEngineString::UnicodeToAnsi(const std::wstring_view& _Text)
{
	// CP_ACP 운영체제가 사용하는거니
// 아무것도 넣지 않으면 => _Text.c_str()이 몇바이트가 되어야 widechar로 변환할수 있는지를 리턴해줍니다.
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열을 변환할수가 없습니다.");
		return "";
	}

	// _Text 10
	// Size 30

	std::string Result;
	Result.resize(Size);


	Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgBoxAssert("문자열을 변환에 실패했습니다.");
		return "";
	}

	return Result;
}

std::string GameEngineString::UnicodeToUTF8(const std::wstring_view& _Text)
{
	// CP_ACP 운영체제가 사용하는거니
// 아무것도 넣지 않으면 => _Text.c_str()이 몇바이트가 되어야 widechar로 변환할수 있는지를 리턴해줍니다.
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("문자열을 변환할수가 없습니다.");
		return "";
	}

	// _Text 10
	// Size 30

	std::string Result;
	Result.resize(Size);


	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgBoxAssert("문자열을 변환에 실패했습니다.");
		return "";
	}

	return Result;
}

std::string GameEngineString::AnsiToUTF8(std::string_view _Text)
{
	std::wstring UniCode = AnsiToUnicode(_Text);
	return UnicodeToUTF8(UniCode);
}