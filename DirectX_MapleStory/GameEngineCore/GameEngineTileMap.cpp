#include "PreCompile.h"
#include "GameEngineTileMap.h"
#include "GameEngineTransform.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineCamera.h"
#include "GameEngineSampler.h"

GameEngineTileMap::GameEngineTileMap()
{
}

GameEngineTileMap::~GameEngineTileMap()
{
}

void GameEngineTileMap::CreateTileMap(const CreateTileParameter& _Parameter)
{
	Tiles.resize(_Parameter.TileCountY);

	for (size_t i = 0; i < _Parameter.TileCountY; i++)
	{
		Tiles[i].resize(_Parameter.TileCountX);
	}

	DefaultSprite = GameEngineSprite::Find(_Parameter.SpriteName);

	TileData = _Parameter;
	TileData.TileScale.Z = 1.0f;
}

void GameEngineTileMap::Start()
{
	GameEngineSpriteRenderer::Start();
}

void GameEngineTileMap::SetTilePos(const SetTileParameterPos& _Parameter)
{

	SetTileParameterIndex Parameter;
	Parameter.X = static_cast<size_t>(_Parameter.Pos.X / TileData.TileScale.X);
	Parameter.Y = static_cast<size_t>(_Parameter.Pos.Y / TileData.TileScale.Y);
	Parameter.Index = _Parameter.Index;
	Parameter.SpriteName = _Parameter.SpriteName;

	SetTileIndex(Parameter);
}

void GameEngineTileMap::SetTileIndex(const SetTileParameterIndex& _Parameter)
{
	if (Tiles.size() <= _Parameter.Y)
	{
		MsgBoxAssert("타일 인덱스를 Y 오버했습니다.");
	}

	if (Tiles[_Parameter.Y].size() <= _Parameter.X)
	{
		MsgBoxAssert("타일 인덱스를 X 오버했습니다.");
	}

	Tile& CurTile = Tiles[_Parameter.Y][_Parameter.X];

	if (_Parameter.SpriteName.empty())
	{
		CurTile.Data = DefaultSprite->GetSpriteData(_Parameter.Index);
	}
	else
	{
		std::shared_ptr<GameEngineSprite> FindSprite = GameEngineSprite::Find(_Parameter.SpriteName);
		CurTile.Data = FindSprite->GetSpriteData(_Parameter.Index);
	}

	CurTile.Index = _Parameter.Index;
}

void GameEngineTileMap::Render(GameEngineCamera* _Camera, float _Delta)
{

	float4 CameraPos = _Camera->Transform.GetWorldPosition();
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 ScreenLeftTop;

	ScreenLeftTop.X = CameraPos.X - WindowScale.hX();
	ScreenLeftTop.Y = CameraPos.Y + WindowScale.hY();

	int StartX = static_cast<int>(ScreenLeftTop.X / TileData.TileScale.X);
	int StartY = static_cast<int>(-ScreenLeftTop.Y / TileData.TileScale.Y);
	int EndX = StartX + static_cast<int>(WindowScale.X / TileData.TileScale.X) + TileMapExpansionSize;
	int EndY = StartY + static_cast<int>(WindowScale.Y / TileData.TileScale.Y) + TileMapExpansionSize;
	StartX -= TileMapExpansionSize;
	StartY -= TileMapExpansionSize;

	if (0 > StartX)
	{
		StartX = 0;
	}

	if (0 > StartY)
	{
		StartY = 0;
	}

	if (TileData.TileCountX < StartX)
	{
		StartX = static_cast<int>(TileData.TileCountX);
	}

	if (TileData.TileCountY < StartY)
	{
		StartY = static_cast<int>(TileData.TileCountY);
	}

	if (0 > EndX)
	{
		EndX = 0;
	}

	if (0 > EndY)
	{
		EndY = 0;
	}

	if (TileData.TileCountX < EndX)
	{
		EndX = static_cast<int>(TileData.TileCountX);
	}

	if (TileData.TileCountY < EndY)
	{
		EndY = static_cast<int>(TileData.TileCountY);
	}

	TransformData Data;
	GetShaderResHelper().SetConstantBufferLink("TransformData", Data);

	for (size_t y = StartY; y < EndY; y++)
	{
		for (size_t x = StartX; x < EndX; x++)
		{

			if (0 > Tiles[y][x].Index)
			{
				continue;
			}

			float4 Pos;
			Pos = Transform.GetWorldPosition();
			Pos.X += TileData.TileScale.X * x + TileData.TileScale.hX();
			Pos.Y -= TileData.TileScale.Y * y + TileData.TileScale.hY();

			Data = Transform.GetConstTransformDataRef();
			Data.Position = Pos;
			Data.Scale = TileData.TileScale;
			Data.LocalCalculation(); // 로컬 월드 생성

			Data.ParentMatrix = Transform.GetConstTransformDataRef().WorldMatrix;
			Data.WorldMatrix = Data.LocalWorldMatrix * Data.ParentMatrix;
			Data.WorldViewProjectionCalculation();

			GetShaderResHelper().SetConstantBufferLink("SpriteData", Tiles[y][x].Data.SpritePivot);
			SpriteData TileSprite = DefaultSprite->GetSpriteData(static_cast<unsigned int>(Tiles[y][x].Index));
			GetShaderResHelper().SetTexture("DiffuseTex", TileSprite.Texture);

			GameEngineRenderer::Render(_Camera, _Delta);
		}
	}
}