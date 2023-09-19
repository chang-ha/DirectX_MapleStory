#include "PreCompile.h"
#include "Arrow.h"
#include "Player.h"
#include "ContentMonster.h"
#include "SkillManager.h"

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

	ArrowRenderer->SetEndEvent("TestArrow_Hit", [&](GameEngineRenderer* _Renderer)
		{
			Death();
		}
	);
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

void Arrow::CollisionEnter(GameEngineCollision* _this, GameEngineCollision* _Other)
{
	++CollisionCount;
	ContentMonster* CurMonster = dynamic_cast<ContentMonster*>(_Other->GetParentObject());
	if (nullptr == CurMonster)
	{
		MsgBoxAssert("충돌대상이 잘못되었습니다.");
		return;
	}

	if (MonsterState::Death == CurMonster->GetState())
	{
		return;
	}

	SkillManager::PlayerSkillManager->HitPrint("TestArrow_Hit", 1, _Other->GetParentObject(), false);
	// ArrowRenderer->ChangeAnimation("TestArrow_Hit");
	// ArrowRenderer->SetPivotType(PivotType::Center);
	// float4 OtherPos = CurMonster->Transform.GetWorldPosition();
	// Transform.SetLocalPosition(OtherPos);
	// CurMonster->ChangeState(MonsterState::Hit);
}