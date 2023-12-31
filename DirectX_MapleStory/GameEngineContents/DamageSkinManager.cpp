﻿#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "DamageSkinManager.h"
#include "ContentLevel.h"
#include "DamageSkinRenderer.h"
#include "Player.h"

DamageSkinManager* DamageSkinManager::MainDamageSkinManager = nullptr;


DamageSkinManager::DamageSkinManager()
{

}

DamageSkinManager::~DamageSkinManager()
{

}

void DamageSkinManager::LevelStart(class GameEngineLevel* _PrevLevel)
{
	MainDamageSkinManager = this;
}

void DamageSkinManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	MainDamageSkinManager = nullptr;
	Death();
}

void DamageSkinManager::Start()
{
	if (nullptr == GameEngineSprite::Find("Character_Empty.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\DamageSkin\\DamageSkin_Num_Merge.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}
}

std::shared_ptr<DamageSkinRenderer> DamageSkinManager::CreateDamageSkin(ContentBaseActor* _Actor, int _Damage)
{
	std::shared_ptr<DamageSkinRenderer> _Renderer = CreateComponent<DamageSkinRenderer>(RenderOrder::UI);
	_Renderer->SetDamage(_Damage);
	float4 RenderPos = _Actor->Transform.GetWorldPosition() + _Actor->GetDamageSkinPivot();
	RenderPos.Z = 0.0f;
	_Renderer->Transform.SetLocalPosition(RenderPos + float4(0, 0, RenderDepth::ui));

	return _Renderer;
}

std::shared_ptr<class DamageSkinRenderer> DamageSkinManager::CreateDamageSkin(const float4& _RenderPos, int _Damage)
{
	std::shared_ptr<DamageSkinRenderer> _Renderer = CreateComponent<DamageSkinRenderer>(RenderOrder::UI);
	_Renderer->SetDamage(_Damage);
	float4 RenderPos = _RenderPos;
	RenderPos.Z = 0.0f;
	_Renderer->Transform.SetLocalPosition(RenderPos + float4(0, 0, RenderDepth::ui));
	return _Renderer;
}
