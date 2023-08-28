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
		MsgBoxAssert("�������� �ʴ� �ؽ��ķ� ��������Ʈ�� ������� �߽��ϴ�.");
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
		MsgBoxAssert("�ε����� �����ؼ� ��������Ʈ �����͸� ���������� �߽��ϴ�.");
		return SpriteDataInfo();
	}

	return SpriteDatas[_Index];
}