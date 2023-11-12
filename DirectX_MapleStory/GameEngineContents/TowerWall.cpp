#include "PreCompile.h"
#include "TowerWall.h"

TowerWall::TowerWall()
{

}

TowerWall::~TowerWall()
{

}

void TowerWall::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void TowerWall::Start()
{
	if (nullptr == GameEngineSprite::Find("Tower_Wall.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\Map\\Tower_Wall.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	WallRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::UI);
	WallRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::ui});
	WallRenderer->SetSprite("Tower_Wall.png");
	WallRenderer->SetSampler("EngineBaseWRAPSampler");
	WallRenderer->AutoSpriteSizeOff();
	WallRenderer->SetImageScale({201, 3100, 1});
	WallRenderer->RenderBaseInfoValue.VertexUVMul.Y = 5;
	WallRenderer->SetPivotType(PivotType::Top);
}

void TowerWall::Release()
{

}