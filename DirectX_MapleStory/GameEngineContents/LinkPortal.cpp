#include "PreCompile.h"
#include "LinkPortal.h"
#include "Player.h"

float LinkPortal::LinkPortalDelayTime = 0.0f;

LinkPortal::LinkPortal()
{

}

LinkPortal::~LinkPortal()
{

}

void LinkPortal::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void LinkPortal::Start()
{
	GameEngineInput::AddInputObject(this);

	if (nullptr == GameEngineSprite::Find("LinkPortal"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Portal\\Link");
		GameEngineSprite::CreateFolder("LinkPortal", Dir.GetStringPath());
	}

	if (nullptr == PortalRenderer)
	{
		PortalRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::PORTAL);
	}
	PortalRenderer->CreateAnimation("Idle", "LinkPortal");
	PortalRenderer->ChangeAnimation("Idle");
	PortalRenderer->SetPivotType(PivotType::Bottom);
	PortalRenderer->AutoSpriteSizeOn();
	PortalRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::portal });

	if (nullptr == PortalCollision)
	{
		PortalCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Portal);
		PortalCollision->Transform.SetLocalScale({ 4, 4 });
		PortalCollision->Transform.SetLocalPosition({ 0, 8 });
	}
}

void LinkPortal::Update(float _Delta)
{
	LinkPortalDelayTime -= _Delta;
	if (0.0f < LinkPortalDelayTime)
	{
		return;
	}

	if (nullptr == LinkedPortal)
	{
		return;
	}

	if (true == PortalCollision->Collision(CollisionOrder::Player) && true == GameEngineInput::IsPress(VK_UP, this))
	{
		Player::MainPlayer->MoveVectorForceReset();
		Player::MainPlayer->Transform.SetWorldPosition(LinkedPortal->Transform.GetWorldPosition() + float4(0, 7));
		LinkPortalDelayTime = LINK_DELAY_TIME;
	}
}

void LinkPortal::Release()
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

void LinkPortal::DoubleLinkPortal(LinkPortal* _LinkPortal)
{
	Link(_LinkPortal);
	_LinkPortal->Link(this);
}

void LinkPortal::Link(LinkPortal* _LinkPortal)
{
	LinkedPortal = _LinkPortal;
}