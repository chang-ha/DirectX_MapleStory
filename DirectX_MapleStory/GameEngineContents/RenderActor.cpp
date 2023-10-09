#include "PreCompile.h"
#include "RenderActor.h"

RenderActor::RenderActor()
{

}

RenderActor::~RenderActor()
{

}

void RenderActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void RenderActor::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::RenderActor);
}

void RenderActor::Update(float _Delta)
{

}

void RenderActor::Load(std::string_view _Path)
{
	//if (nullptr == GameEngineTexture::Find(_MapName))
	//{
	//	GameEnginePath Path;
	//	Path.SetCurrentPath();
	//	Path.MoveParentToExistsChild("ContentResources");
	//	Path.MoveChild("ContentResources\\Textures\\Map\\");
	//	GameEngineTexture::Load(Path.GetStringPath() + std::string(_MapName.data()));
	//	GameEngineTexture::Load(Path.GetStringPath() + "Collision_" + std::string(_MapName.data()));
	//	GameEngineSprite::CreateSingle(_MapName);
	//	GameEngineSprite::CreateSingle("Collision_" + std::string(_MapName.data()));
	//}
}