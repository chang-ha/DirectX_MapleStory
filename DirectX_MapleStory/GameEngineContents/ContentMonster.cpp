#include "PreCompile.h"
#include "ContentMonster.h"


ContentMonster::ContentMonster()
{

}

ContentMonster::~ContentMonster()
{

}

void ContentMonster::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void ContentMonster::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void ContentMonster::Start()
{
	if (nullptr == GameEngineSprite::Find("Monster_Idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Monster");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& ChildDir = Directorys[i];
			GameEngineSprite::CreateFolder(ChildDir.GetStringPath());
		}

	}
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	MainSpriteRenderer->CreateAnimation("Monster_Idle", "Monster_Idle");
	MainSpriteRenderer->CreateAnimation("Monster_Hit", "Monster_Hit");
	MainSpriteRenderer->CreateAnimation("Monster_Die", "Monster_Die");
	MainSpriteRenderer->ChangeAnimation("Monster_Idle");
	MainSpriteRenderer->AutoSpriteSizeOn();

	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find("Monster_Idle");
	MonsterScale = Sprite->GetSpriteData(0).GetScale();
	Sprite = nullptr;

	// Collision
	MainCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	MainCollision->Transform.SetLocalScale(MonsterScale);

	MonsterEvent.Enter = [](GameEngineCollision* _OtherCollision)
	{

	};

	MonsterEvent.Stay = [](GameEngineCollision* _OtherCollision)
	{

	};

	MonsterEvent.Exit = [](GameEngineCollision* _OtherCollision)
	{

	};
}

void ContentMonster::Update(float _Delta)
{

}