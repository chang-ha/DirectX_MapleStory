#include "PreCompile.h"
#include "GameEngineTileMap.h"
#include "GameEngineTransform.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineCamera.h"

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
	ResSetting();

	float4 CameraPos = _Camera->Transform.GetWorldPosition();
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	float4 ScreenLeftTop;

	ScreenLeftTop.X = CameraPos.X - WindowScale.hX();
	ScreenLeftTop.Y = CameraPos.Y + WindowScale.hY();

	int StartX = static_cast<size_t>(ScreenLeftTop.X / TileData.TileScale.X) - 1;
	int StartY = static_cast<size_t>(ScreenLeftTop.Y / TileData.TileScale.Y) - 1;
	int EndX = static_cast<size_t>(StartX + (WindowScale.X / TileData.TileScale.X) + 1);
	int EndY = static_cast<size_t>(StartY + (WindowScale.Y / TileData.TileScale.Y) + 1);

	if (0 >= StartX)
	{
		StartX = 0;
	}

	if (0 >= EndX)
	{
		EndX = 0;
	}

	if (TileData.TileCountX < StartX)
	{
		StartX = static_cast<int>(TileData.TileCountX - 1);
	}

	if (TileData.TileCountX < EndX)
	{
		EndX = static_cast<int>(TileData.TileCountX - 1);
	}

	if (0 >= StartY)
	{
		StartY = 0;
	}

	if (0 >= EndY)
	{
		EndY = 0;
	}

	if (TileData.TileCountX < StartY)
	{
		StartX = static_cast<int>(TileData.TileCountX - 1);
	}

	if (TileData.TileCountY < EndY)
	{
		EndX = static_cast<int>(TileData.TileCountX - 1);
	}


	TransformData Data;
	for (size_t y = StartY; y < EndY; y++)
	{
		for (size_t x = StartX; x < EndX; x++)
		{
			//if (카메라에 나오지 않는다면)
			//{
			//	continue;
			//}


			std::shared_ptr<GameEngineConstantBuffer> TransBuffer = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData", ShaderType::Vertex);

			if (nullptr != TransBuffer)
			{
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
				// 내 행렬을 전부다 계산하고 넘긴다.

				TransBuffer->ChangeData(Data);
				TransBuffer->Setting(0);
			}

			SpriteData& TileSprite = Tiles[y][x].Data; 

			std::shared_ptr<GameEngineConstantBuffer> SpriteBuffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData", ShaderType::Vertex);
			if (nullptr != SpriteBuffer)
			{
				SpriteBuffer->ChangeData(TileSprite.SpritePivot);
				SpriteBuffer->Setting(1);
			}

			Tiles[y][x].Data.Texture->PSSetting(0);

			Draw();
		}
	}
}