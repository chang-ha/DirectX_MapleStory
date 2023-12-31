﻿#include "PreCompile.h"
#include "RenderActor.h"

RenderActor::RenderActor()
{

}

RenderActor::~RenderActor()
{

}

void RenderActor::Init(int _Order, float _Depth)
{
	if (nullptr == Renderer)
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(_Order);
		Renderer->Transform.SetLocalPosition({ 0, 0, _Depth });
		Renderer->AutoSpriteSizeOn();
	}
}

void RenderActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void RenderActor::Start()
{

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