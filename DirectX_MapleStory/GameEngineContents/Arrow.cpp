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
	ArrowRenderer->ChangeAnimation("TestArrow");
	Transform.SetLocalPosition(Player::MainPlayer->Transform.GetWorldPosition());

	Dir = Player::MainPlayer->GetDir();
	switch (Dir)
	{
	case ActorDir::Right:
		Transform.SetLocalScale(float4(-1.0f, 1.0f));
		break;
	case ActorDir::Left:
		Transform.SetLocalScale(float4(1.0f, 1.0f));
		break;
	case ActorDir::Null:
	default:
		break;
	}
}

void Arrow::Update(float _Delta)
{
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

	if (0.0f >= LiveTime)
	{
		Death();
	}
}