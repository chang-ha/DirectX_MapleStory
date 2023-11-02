﻿#include "PreCompile.h"
#include "Portal.h"
#include "ContentLevel.h"
#include "FadeObject.h"

Portal::Portal()
{

}

Portal::~Portal()
{

}

void Portal::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Portal::Start()
{
	GameEngineInput::AddInputObject(this);

	if (nullptr == GameEngineSprite::Find("NormalPortal"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Portal\\Normal");
		GameEngineSprite::CreateFolder("NormalPortal", Dir.GetStringPath());
	}

	PortalRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PORTAL);
	PortalRenderer->CreateAnimation("Idle", "NormalPortal");
	PortalRenderer->ChangeAnimation("Idle");
	PortalRenderer->AutoSpriteSizeOn();

	PortalRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::portal});

	PortalCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Portal);
	PortalCollision->Transform.SetLocalScale({28, 80});
	PortalCollision->Transform.SetLocalPosition({0, -25});
}

void Portal::Update(float _Delta)
{
	if (true == PortalCollision->Collision(CollisionOrder::Player) && true == GameEngineInput::IsPress(VK_UP, this))
	{
		std::shared_ptr<FadeObject> _FadeObject = ContentLevel::CurContentLevel->FadeOutObject;
		_FadeObject->SetChangeLevel(MoveMap);
		_FadeObject->FadeStart();
	}
}

void Portal::Release()
{

}