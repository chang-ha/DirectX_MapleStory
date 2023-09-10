#include "PreCompile.h"
#include "Arrow.h"
#include "Player.h"

Arrow::Arrow()
{

}

Arrow::~Arrow()
{

}

void Arrow::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void Arrow::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Arrow::Start()
{
	if (nullptr == GameEngineSprite::Find("TestArrow"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Arrow");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& ChildDir = Directorys[i];
			GameEngineSprite::CreateFolder(ChildDir.GetStringPath());
		}
	}
	ArrowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Arrow);
	ArrowRenderer->AutoSpriteSizeOn();
	ArrowRenderer->SetPivotType(PivotType::Bottom);
	ArrowRenderer->CreateAnimation("TestArrow", "TestArrow", 0.1f, 0, 2, true);
	ArrowRenderer->CreateAnimation("TestArrow_Hit", "TestArrow_Hit", 0.1f, 0, 2, true);
	ArrowRenderer->ChangeAnimation("TestArrow");
	float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();

	Dir = Player::MainPlayer->GetDir();
	switch (Dir)
	{
	case ActorDir::Right:
		Transform.SetLocalScale(float4(-1.0f, 1.0f));
		Transform.SetLocalPosition(float4(PlayerPos.X + Player::MainPlayer->GetPlayerScale().X, PlayerPos.Y));
		break;
	case ActorDir::Left:
		Transform.SetLocalScale(float4(1.0f, 1.0f));
		Transform.SetLocalPosition(float4(PlayerPos.X - Player::MainPlayer->GetPlayerScale().X, PlayerPos.Y));
		break;
	case ActorDir::Null:
	default:
		break;
	}

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TestArrow");
	ArrowScale = Sprite->GetSpriteData(0).GetScale();
	Sprite = nullptr;

	ArrowCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
	ArrowCollision->Transform.SetLocalScale(ArrowScale);

	ArrowEvent.Enter = [=](GameEngineCollision* _OtherCollision)
	{
		ArrowRenderer->ChangeAnimation("TestArrow_Hit");
		ArrowRenderer->SetPivotType(PivotType::Center);
		float4 OtherPos = _OtherCollision->GetParentObject()->Transform.GetWorldPosition();
		Transform.SetLocalPosition(OtherPos);
	};
}

void Arrow::Update(float _Delta)
{
	static std::vector<std::shared_ptr<GameEngineCollision>> _CollisionResult;
	if (true == ArrowRenderer->IsCurAnimation("TestArrow_Hit") && true == ArrowRenderer->IsCurAnimationEnd())
	{
		Death();
	}

	if (true == ArrowRenderer->IsCurAnimation("TestArrow_Hit"))
	{
		return;
	}

	LiveTime -= _Delta;
	switch (Dir)
	{
	case ActorDir::Right:
		Transform.AddLocalPosition(float4(ArrowSpeed * _Delta));
		break;
	case ActorDir::Left:
		Transform.AddLocalPosition(float4(-ArrowSpeed * _Delta));
		break;
	default:
		break;
	}

	if (0.0f >= LiveTime && true == ArrowRenderer->IsCurAnimation("TestArrow"))
	{
		Death();
	}


	ArrowCollision->CollisionEvent(CollisionOrder::Monster, ArrowEvent);
}