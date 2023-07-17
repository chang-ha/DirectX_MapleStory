#pragma once
#include <string>

// ���� :
class GameEngineString
{
public:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();

	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;

	static std::string ToUpperReturn(const std::string_view& _Value) 
	{
		std::string UpperString = std::string(_Value);

		for (size_t i = 0; i < UpperString.size(); i++)
		{
			UpperString[i] = toupper(UpperString[i]);
		}

		return UpperString;
	}

	// Ansi�� ��Ƽ����Ʈ ���ڵ��� �ٸ��̸�
	static std::wstring AnsiToUnicode(const std::string_view& _Text);

	static std::string UnicodeToAnsi(const std::wstring_view& _Text);

	static std::string UnicodeToUTF8(const std::wstring_view& _Text);

	static std::string AnsiToUTF8(const std::string_view& _Text);

protected:

private:

};

