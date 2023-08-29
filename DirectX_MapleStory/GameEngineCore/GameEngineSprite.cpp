#include "PreCompile.h"
#include "GameEngineSprite.h"

float4 SpriteData::GetScale()
{
	return Texture->GetScale() * float4( SpritePivot.Scale2DX, SpritePivot.Scale2DY, 1.0f, 0.0f);
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

	float4 Start;
	Start.Pos2DX = 0.0f;
	Start.Pos2DY = 0.0f;
	Start.Scale2DX = 1.0f / _X;
	Start.Scale2DY = 1.0f / _Y;

	SpriteDatas.resize(_X * _Y);
	for (size_t y = 0; y < _Y; y++)
	{
		for (size_t x = 0; x < _X; x++)
		{
			unsigned int Index = static_cast<unsigned int>((y * _X) + x);
			SpriteDatas[Index].Texture = Texture;
			SpriteDatas[Index].SpritePivot = Start;
			Start.Pos2DX += Start.Scale2DX;
		}
		Start.Pos2DX = 0.0f;
		Start.Pos2DY += Start.Scale2DY;
	}
}

SpriteData GameEngineSprite::GetSpriteData(unsigned int _Index)
{
	if (_Index >= SpriteDatas.size())
	{
		MsgBoxAssert("�ε����� �����ؼ� ��������Ʈ �����͸� ���������� �߽��ϴ�.");
		return SpriteData();
	}

	return SpriteDatas[_Index];
}