#include "PreCompile.h"
#include "NightmareMusicBox.h"
#include "ReleaseFunction.h"

NightmareMusicBox::NightmareMusicBox()
{

}

NightmareMusicBox::~NightmareMusicBox()
{

}

void NightmareMusicBox::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void NightmareMusicBox::Start()
{
	HP = 100;

	if (nullptr == GameEngineSprite::Find("NightmareMusicBox_Death"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Monster\\NightmareMusicBox");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("NightmareMusicBox_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}

	if (nullptr == BoxRenderer)
	{
		BoxRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MONSTER);
		BoxRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::monster});
		BoxRenderer->AutoSpriteSizeOn();
	}

	if (nullptr == BoxCollision)
	{
		BoxCollision = CreateComponent<GameEngineCollision>(CollisionOrder::Monster);
	}

	BoxRenderer->CreateAnimation("Idle", "NightmareMusicBox_Idle", 0.18f);
	BoxRenderer->CreateAnimation("Death", "NightmareMusicBox_Death", 0.12f);
	BoxRenderer->ChangeAnimation("Idle");
	BoxRenderer->SetPivotType(PivotType::Bottom);

	BoxRenderer->SetStartEvent("Death", [&](GameEngineSpriteRenderer* _Renderer)
		{
			BoxRenderer->SetPivotValue({0.517f, 0.74f});
			BoxCollision->Off();
		});

	BoxRenderer->SetEndEvent("Death", [&](GameEngineSpriteRenderer* _Renderer)
		{
			Death();
		});

	BoxCollision->Transform.SetLocalScale({80, 150, 1});
	BoxCollision->Transform.SetLocalPosition({20, 75});
}

void NightmareMusicBox::Update(float _Delta)
{
	if (0 >= HP && true == BoxRenderer->IsCurAnimation("Idle"))
	{
		BoxRenderer->ChangeAnimation("Death");
	}
}

void NightmareMusicBox::Release()
{
	if (nullptr != BoxRenderer)
	{
		BoxRenderer->Death();
		BoxRenderer = nullptr;
	}

	if (nullptr != BoxCollision)
	{
		BoxCollision->Death();
		BoxCollision = nullptr;
	}

	if (nullptr != GameEngineSprite::Find("NightmareMusicBox_Death"))
	{
		ReleaseFunction::FolderRelease("NightmareMusicBox_Idle", "NightmareMusicBox_Idle_");
		ReleaseFunction::FolderRelease("NightmareMusicBox_Death", "NightmareMusicBox_Death_");
	}
}