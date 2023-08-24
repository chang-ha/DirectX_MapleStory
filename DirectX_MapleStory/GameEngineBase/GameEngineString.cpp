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
	// CP_ACP �ü���� ����ϴ°Ŵ�
	// �ƹ��͵� ���� ������ => _Text.c_str()�� �����Ʈ�� �Ǿ�� widechar�� ��ȯ�Ҽ� �ִ����� �������ݴϴ�.
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ��ȯ�Ҽ��� �����ϴ�.");
		return L"";
	}

	// _Text 10
	// Size 30

	std::wstring Result;
	Result.resize(Size);


	Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ��ȯ�� �����߽��ϴ�.");
		return L"";
	}

	return Result;
}

std::string GameEngineString::UnicodeToAnsi(const std::wstring_view& _Text)
{
	// CP_ACP �ü���� ����ϴ°Ŵ�
// �ƹ��͵� ���� ������ => _Text.c_str()�� �����Ʈ�� �Ǿ�� widechar�� ��ȯ�Ҽ� �ִ����� �������ݴϴ�.
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ��ȯ�Ҽ��� �����ϴ�.");
		return "";
	}

	// _Text 10
	// Size 30

	std::string Result;
	Result.resize(Size);


	Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ��ȯ�� �����߽��ϴ�.");
		return "";
	}

	return Result;
}

std::string GameEngineString::UnicodeToUTF8(const std::wstring_view& _Text)
{
	// CP_ACP �ü���� ����ϴ°Ŵ�
// �ƹ��͵� ���� ������ => _Text.c_str()�� �����Ʈ�� �Ǿ�� widechar�� ��ȯ�Ҽ� �ִ����� �������ݴϴ�.
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ��ȯ�Ҽ��� �����ϴ�.");
		return "";
	}

	// _Text 10
	// Size 30

	std::string Result;
	Result.resize(Size);


	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(), static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);

	if (0 == Size)
	{
		MsgBoxAssert("���ڿ��� ��ȯ�� �����߽��ϴ�.");
		return "";
	}

	return Result;
}

std::string GameEngineString::AnsiToUTF8(std::string_view _Text)
{
	std::wstring UniCode = AnsiToUnicode(_Text);
	return UnicodeToUTF8(UniCode);
}