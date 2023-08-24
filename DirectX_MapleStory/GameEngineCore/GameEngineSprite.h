#pragma once
#include "GameEngineTexture.h"

class SpriteData
{
	std::shared_ptr<GameEngineTexture> Texture;
};

// 설명 :
class GameEngineSprite : public GameEngineResources<GameEngineSprite>
{
public:
	// constrcuter destructer
	GameEngineSprite();
	~GameEngineSprite();

	// delete Function
	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(GameEngineSprite&& _Other) noexcept = delete;

	// 폴더에 있는 이미지를 전부 불러옴
	static std::shared_ptr<GameEngineSprite> CreateFolder()
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes();
		return NewRes;
	}

	// 스프라이트 1장을 잘라서 사용함
	static std::shared_ptr<GameEngineSprite> CreateCut()
	{
		std::shared_ptr<GameEngineSprite> NewRes = CreateRes();
		return NewRes;
	}
protected:

private:
	std::vector<SpriteData> GameEngineSpriteData;
};

