#include "PreCompile.h"
#include "ReleaseFunction.h"

void ReleaseFunction::FolderRelease(std::string_view _SpriteName, std::string_view _TextureName)
{
	std::shared_ptr<GameEngineSprite> _Sprite = GameEngineSprite::Find(_SpriteName);
	int SpriteSize = _Sprite->GetSpriteCount();
	for (size_t i = 1; i <= SpriteSize; i++)
	{
		if (10 > i)
		{
			GameEngineTexture::Release(std::string(_TextureName) + "00" + std::to_string(i) + ".png");
		}
		else if (100 > i)
		{
			GameEngineTexture::Release(std::string(_TextureName) + "0" + std::to_string(i) + ".png");
		}
		else
		{
			GameEngineTexture::Release(std::string(_TextureName) + std::to_string(i) + ".png");
		}
	}
	GameEngineSprite::Release(_SpriteName);
}
