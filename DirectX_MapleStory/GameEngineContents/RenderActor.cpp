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