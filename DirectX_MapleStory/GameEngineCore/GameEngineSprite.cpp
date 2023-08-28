#include "PreCompile.h"
#include "GameEngineSprite.h"

float4 SpriteDataInfo::GetScale()
{
	return Texture->GetScale();
}

GameEngineSprite::GameEngineSprite()
{
}

GameEngineSprite::~GameEngineSprite()
{
}

void GameEngineSprite::ResCreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y)
{
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(_Name);

	if (nullptr == Texture)
	{
		MsgBoxAssert("존재하지 않는 텍스쳐로 스프라이트를 만들려고 했습니다.");
		return;
	}

	SpriteDatas.resize(_X * _Y);
	for (unsigned int y = 0; y < _Y; y++)
	{
		for (unsigned int x = 0; x < _X; x++)
		{
			unsigned int Index = (y * _X) + x;
			SpriteDatas[Index].Texture = Texture;
		}
	}
}

const SpriteDataInfo& GameEngineSprite::GetSpriteData(unsigned int _Index)
{
	if (_Index >= SpriteDatas.size())
	{
		MsgBoxAssert("인덱스를 오버해서 스프라이트 데이터를 가져오려고 했습니다.");
		return SpriteDataInfo();
	}

	return SpriteDatas[_Index];
}