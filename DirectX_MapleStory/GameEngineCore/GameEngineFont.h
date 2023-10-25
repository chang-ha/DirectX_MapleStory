#pragma once
#include "GameEngineResources.h"

#include <GameEngineCore/ThirdParty/FW1FontWrapper/inc/FW1FontWrapper.h>

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\FW1FontWrapper\\lib\\Debug\\FW1FontWrapper.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\FW1FontWrapper\\lib\\Release\\FW1FontWrapper.lib")
#endif


// 설명 :
class GameEngineFont : public GameEngineResources<GameEngineFont>
{
	friend class FontFactoryCreator;
	// 폰트를 만들어주는 객체
	static IFW1Factory* Factory;

public:
	// constrcuter destructer
	GameEngineFont();
	~GameEngineFont();

	// delete Function
	GameEngineFont(const GameEngineFont& _Other) = delete;
	GameEngineFont(GameEngineFont&& _Other) noexcept = delete;
	GameEngineFont& operator=(const GameEngineFont& _Other) = delete;
	GameEngineFont& operator=(GameEngineFont&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineFont> Load(const std::string_view& _FontName)
	{
		std::shared_ptr<GameEngineFont> Res = GameEngineFont::CreateRes(_FontName);
		Res->ResLoad(_FontName);
		return Res;
	}

protected:

private:
	IFW1FontWrapper* Font = nullptr;
	void ResLoad(const std::string_view& _Path);
};

