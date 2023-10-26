#include "PreCompile.h"
#include "GameEngineFont.h"

IFW1Factory* GameEngineFont::Factory = nullptr;

class FontFactoryCreator
{
public:
	FontFactoryCreator()
	{
		FW1CreateFactory(FW1_VERSION, &GameEngineFont::Factory);
	}

	~FontFactoryCreator()
	{
		if (nullptr != GameEngineFont::Factory)
		{
			// 다시 사용할때 비어있다는것을 알려주기 위해서
			// 프로그램이 종료될때 되는것.
			GameEngineFont::Factory->Release();
			GameEngineFont::Factory = nullptr;
		}
	}
};

FontFactoryCreator InitFont;

GameEngineFont::GameEngineFont()
{

}

GameEngineFont::~GameEngineFont()
{
	if (nullptr != Font)
	{
		Font->Release();
		Font = nullptr;
	}
}



void GameEngineFont::ResLoad(const std::string_view& _Path)
{
	// 블랜드 추가가 필요하다.

	std::wstring WPath = GameEngineString::AnsiToUnicode(_Path);

	if (S_OK != GameEngineFont::Factory->CreateFontWrapper(GameEngineCore::GetDevice(), WPath.c_str(), &Font))
	{
		MsgBoxAssert("폰트 생성 실패");
	}
}

void GameEngineFont::FontDraw(const std::string& _Text, float _FontScale, const float4& _Pos, const float4& _Color, FW1_TEXT_FLAG _Flag)
{
	std::wstring Text = GameEngineString::AnsiToUnicode(_Text);

	Font->DrawString(GameEngineCore::GetContext(), Text.c_str(), _FontScale, _Pos.X, _Pos.Y, _Color.ColorToUint(), _Flag);
}