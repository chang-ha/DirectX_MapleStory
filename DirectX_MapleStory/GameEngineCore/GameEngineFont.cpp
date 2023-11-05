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

	D3D11_BLEND_DESC blendDesc = { 0, };
	for (int i = 0; i < 4; ++i)
	{
		blendDesc.RenderTarget[i].BlendEnable = true;
		blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ONE;
	}

	if (S_OK != GameEngineFont::Factory->CreateFontWrapper(GameEngineCore::GetDevice(), WPath.c_str(), blendDesc, &Font))
	{
		MsgBoxAssert("폰트 생성 실패");
		return;
	}
}

void GameEngineFont::FontDraw(const std::string& _Text, float _FontScale, const float4& _Pos, const float4& _Color, FW1_TEXT_FLAG _Flag)
{
	std::wstring Text = GameEngineString::AnsiToUnicode(_Text);

	FontDraw(Text, _FontScale, _Pos, _Color, _Flag);
}

void GameEngineFont::FontDraw(const std::wstring& _Text, float _FontScale, const float4& _Pos, const float4& _Color, FW1_TEXT_FLAG _Flag)
{
	Font->DrawString(GameEngineCore::GetContext(), _Text.c_str(), _FontScale, _Pos.X, _Pos.Y, _Color.ColorToUint(), _Flag);
}