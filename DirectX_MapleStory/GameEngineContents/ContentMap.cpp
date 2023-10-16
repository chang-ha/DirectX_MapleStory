﻿#include "PreCompile.h"
#include "ContentMap.h"

ContentMap::ContentMap()
{

}

ContentMap::~ContentMap()
{

}

void ContentMap::Start()
{
	GameEngineInput::AddInputObject(this);
}

void ContentMap::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_F1, this))
	{
		if (true == MapRenderer->IsUpdate())
		{
			MapRenderer->Off();
		}
		else
		{
			MapRenderer->On();
		}
	}
	else if (GameEngineInput::IsDown(VK_F2, this))
	{
		if (true == MapCollisionRenderer->IsUpdate())
		{
			MapCollisionRenderer->Off();
		}
		else
		{
			MapCollisionRenderer->On();
		}
	}
}


void ContentMap::InitMap(std::string_view _MapName)
{
	if (nullptr == GameEngineTexture::Find(_MapName))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\Map\\");
		GameEngineTexture::Load(Path.GetStringPath() + std::string(_MapName.data()));
		GameEngineSprite::CreateSingle(_MapName);
	}

	if (nullptr == MapRenderer)
	{
		MapRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MAP);
		MapRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::map });
	}

	// MapName = _MapName;
	MapRenderer->SetSprite(_MapName);
	
	//float4 HalfMapScale = GameEngineTexture::Find(_MapName)->GetScale().Half();
	//HalfMapScale.Y *= -1.0f;
	//this->Transform.SetLocalPosition(HalfMapScale);
}

void ContentMap::InitMapCollision(std::string_view _MapName)
{
	if (nullptr == GameEngineTexture::Find(_MapName))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\Map\\");
		GameEngineTexture::Load(Path.GetStringPath() + std::string(_MapName.data()));
		GameEngineSprite::CreateSingle(_MapName);
	}

	if (nullptr == MapCollisionRenderer)
	{
		MapCollisionRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MAP);
		MapCollisionRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::map });
	}

	MapCollisionRenderer->SetSprite(_MapName);
	MapCollisionRenderer->Off();

	MapCollisionTexture = GameEngineTexture::Find(_MapName);
	float4 HalfMapScale = MapCollisionTexture->GetScale().Half();
	HalfMapScale.Y *= -1.0f;
	this->Transform.SetLocalPosition(HalfMapScale);
}

GameEngineColor ContentMap::GetColor(float4 _Pos, GameEngineColor _DefaultColor /*= GROUND_COLOR*/)
{
	// 플레이어의 위치를 이미지의 좌표계에 맞게 변형한다.
	// 이미지는 위에서부터 아래로 내려갈수록 +가 되기 때문이다. (DirectX의 Y좌표계는 아래로 내려갈수록 -)
	_Pos.Y *= -1.0f;
	return MapCollisionTexture->GetColor(_Pos, _DefaultColor);
}

void ContentMap::Release()
{
	if (nullptr != MapRenderer)
	{
		MapRenderer->Death();
		MapRenderer = nullptr;
	}

	if (nullptr != MapCollisionRenderer)
	{
		MapCollisionRenderer->Death();
		MapCollisionRenderer = nullptr;
	}
}