#include "PreCompile.h"
#include "Arrow.h"
#include "Player.h"
#include "ContentMonster.h"
#include "SkillManager.h"
//Test Code
#include "BaseWindActor.h"

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
	Death();
}

void Arrow::Start()
{
	if (nullptr == ArrowRenderer)
	{
		ArrowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::ARROW);
		ArrowRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::arrow});
	}

	if (nullptr == ArrowCollision)
	{
		ArrowCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
	}

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

	ArrowRenderer->AutoSpriteSizeOn();
	ArrowRenderer->SetPivotType(PivotType::Bottom);
	ArrowRenderer->CreateAnimation("TestArrow", "TestArrow", 0.1f, 0, 2, true);
	ArrowRenderer->CreateAnimation("TestArrow_Hit", "TestArrow_Hit", 0.1f, 0, 2, true);
	ArrowRenderer->ChangeAnimation("TestArrow");
	float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();

	ArrowRenderer->SetEndEvent("TestArrow_Hit", [&](GameEngineRenderer* _Renderer)
		{
			Death();
		}
	);
	Dir = Player::MainPlayer->GetDir();
	switch (Dir)
	{
	case ActorDir::Right:
		ArrowRenderer->LeftFlip();
		Transform.SetLocalPosition(float4(PlayerPos.X + Player::MainPlayer->GetPlayerScale().X, PlayerPos.Y));
		break;
	case ActorDir::Left:
		ArrowRenderer->RightFlip();
		Transform.SetLocalPosition(float4(PlayerPos.X - Player::MainPlayer->GetPlayerScale().X, PlayerPos.Y));
		break;
	case ActorDir::Null:
	default:
		break;
	}

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("TestArrow");
	ArrowScale = Sprite->GetSpriteData(0).GetScale();

	ArrowCollision->Transform.SetLocalScale(ArrowScale);
	ArrowCollision->Transform.SetLocalPosition({0, ArrowScale.hY()});

	ArrowEvent.Enter = std::bind(&Arrow::CollisionEnter, this, std::placeholders::_1, std::placeholders::_2);
}

void Arrow::Update(float _Delta)
{
	if (4 <= CollisionCount)
	{
		Death();
		return;
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

void Arrow::Release()
{
	if (nullptr != ArrowRenderer)
	{
		ArrowRenderer->Death();
		ArrowRenderer = nullptr;
	}

	if (nullptr != ArrowCollision)
	{
		ArrowCollision->Death();
		ArrowCollision = nullptr;
	}
}

void Arrow::CollisionEnter(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	++CollisionCount;
	SkillManager::PlayerSkillManager->HitPrint("TestArrow_Hit", 1, _Other->GetParentObject(), false);
}