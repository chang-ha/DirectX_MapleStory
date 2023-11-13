#include "PreCompile.h"
#include "Portal.h"
#include "ContentLevel.h"
#include "FadeObject.h"
#include "Player.h"

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

	if (nullptr == PortalRenderer)
	{
		PortalRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PORTAL);
	}
	PortalRenderer->CreateAnimation("Idle", "NormalPortal");
	PortalRenderer->ChangeAnimation("Idle");
	PortalRenderer->SetPivotType(PivotType::Bottom);
	PortalRenderer->AutoSpriteSizeOn();

	PortalRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::portal});

	if (nullptr == PortalCollision)
	{
		PortalCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Portal);
		PortalCollision->Transform.SetLocalScale({ 4, 4 });
		PortalCollision->Transform.SetLocalPosition({ 0, 10 });
	}
}

void Portal::Update(float _Delta)
{
	if (true == PortalCollision->Collision(CollisionOrder::Player) && true == GameEngineInput::IsPress(VK_UP, this))
	{
		std::shared_ptr<FadeObject> _FadeObject = ContentLevel::CurContentLevel->FadeOutObject;
		_FadeObject->SetChangeLevel(MoveMap);
		_FadeObject->FadeStart();

		Player::MainPlayer->PopInput();
	}
}

void Portal::Release()
{
	if (nullptr != PortalRenderer)
	{
		PortalRenderer->Death();
		PortalRenderer = nullptr;
	}

	if (nullptr != PortalCollision)
	{
		PortalCollision->Death();
		PortalCollision = nullptr;
	}
}