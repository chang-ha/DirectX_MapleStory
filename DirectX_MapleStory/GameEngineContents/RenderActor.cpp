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
	Release();
	Death();
}

void RenderActor::Start()
{
	if (nullptr == Renderer)
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::RenderActor);
	}
}

void RenderActor::Update(float _Delta)
{

}

void RenderActor::Release()
{
	if (nullptr != Renderer)
	{
		Renderer->Death();
		Renderer = nullptr;
	}
}