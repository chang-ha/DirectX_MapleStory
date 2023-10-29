#pragma once
#include <string>
#include <format>

// 설명 :
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

	static std::string ToUpperReturn(std::string_view _Value) 
	{
		std::string UpperString = std::string(_Value);

		for (size_t i = 0; i < UpperString.size(); i++)
		{
			UpperString[i] = toupper(UpperString[i]);
		}

		return UpperString;
	}

	template <typename... _Types>
	static std::string Format(const std::format_string<_Types...> _Fmt, _Types... _Args)
	{
		// std::format
		return std::vformat(_Fmt.get(), _STD make_format_args(_Args...));
	}

	// Ansi는 멀티바이트 인코딩의 다른이름
	static std::wstring AnsiToUnicode(std::string_view _Text);

	static std::string UnicodeToAnsi(const std::wstring_view& _Text);

	static std::string UnicodeToUTF8(const std::wstring_view& _Text);

	static std::string AnsiToUTF8(std::string_view _Text);

protected:

private:

};

