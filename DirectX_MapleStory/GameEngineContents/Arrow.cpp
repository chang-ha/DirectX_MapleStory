#include "PreCompile.h"
#include "Arrow.h"
#include "Player.h"
#include "ContentMonster.h"
#include "HitRenderManager.h"

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
		ArrowRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::SKILL);
		ArrowRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::skill});
	}

	if (nullptr == ArrowCollision)
	{
		ArrowCollision = CreateComponent<GameEngineCollision>(CollisionOrder::PlayerAttack);
	}

	if (nullptr == GameEngineSprite::Find("SongOfHeaven_Actor_Arrow"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Skill\\SongOfHeaven_Actor");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& ChildDir = Directorys[i];
			GameEngineSprite::CreateFolder("SongOfHeaven_Actor_" + ChildDir.GetFileName(), ChildDir.GetStringPath());
		}
	}

	ArrowRenderer->CreateAnimation("Arrow", "SongOfHeaven_Actor_Arrow", 0.1f, -1, -1, true);
	ArrowRenderer->CreateAnimation("Arrow_Hit", "SongOfHeaven_Actor_Arrow_Hit", 0.1f, -1, -1, true);
	ArrowRenderer->ChangeAnimation("Arrow");
	ArrowRenderer->AutoSpriteSizeOn();
	ArrowRenderer->SetPivotType(PivotType::Bottom);
	float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();

	ArrowRenderer->SetEndEvent("Arrow_Hit", [&](GameEngineRenderer* _Renderer)
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

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("SongOfHeaven_Actor_Arrow");
	ArrowScale = Sprite->GetSpriteData(0).GetScale();

	ArrowCollision->Transform.SetLocalScale(ArrowScale);
	ArrowCollision->Transform.SetLocalPosition({0, ArrowScale.hY()});

	ArrowEvent.Enter = std::bind(&Arrow::CollisionEnter, this, std::placeholders::_1, std::placeholders::_2);
}

void Arrow::Update(float _Delta)
{
	ArrowRenderer->GetColorData().MulColor.A = GlobalValue::SkillEffectAlpha;

	if (4 <= CollisionCount)
	{
		Death();
		return;
	}

	if (true == ArrowRenderer->IsCurAnimation("Arrow_Hit"))
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

	if (0.0f >= LiveTime && true == ArrowRenderer->IsCurAnimation("Arrow"))
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
	HitRenderManager::MainHitRenderManager->HitPrint("SongOfHeaven_Actor_Arrow_Hit", 1, _Other->GetParentObject(), 1, false);
}