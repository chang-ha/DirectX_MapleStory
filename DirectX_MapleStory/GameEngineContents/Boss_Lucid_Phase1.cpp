#include "PreCompile.h"
#include "Boss_Lucid_Phase1.h"

Boss_Lucid_Phase1::Boss_Lucid_Phase1()
{

}

Boss_Lucid_Phase1::~Boss_Lucid_Phase1()
{

}

void Boss_Lucid_Phase1::LevelStart(GameEngineLevel* _PrevLevel)
{
	BaseBossActor::LevelStart(_PrevLevel);
}

void Boss_Lucid_Phase1::LevelEnd(GameEngineLevel* _NextLevel)
{
	BaseBossActor::LevelEnd(_NextLevel);
}

void Boss_Lucid_Phase1::Start()
{
	FlowerRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::Monster);
	BaseBossActor::Start();
	FlowerRenderer->AutoSpriteSizeOn();

	if (nullptr == GameEngineSprite::Find("Lucid_Phase1_Death"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\Boss\\Lucid\\Phase1");
		std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

		for (size_t i = 0; i < Directorys.size(); i++)
		{
			GameEngineDirectory& Childs = Directorys[i];
			GameEngineSprite::CreateFolder("Lucid_Phase1_" + Childs.GetFileName(), Childs.GetStringPath());
		}
	}


	BossRenderer->CreateAnimation("Idle", "Lucid_Phase1_Idle");
	BossRenderer->CreateAnimation("Death", "Lucid_Phase1_Death", 0.11f);
	BossRenderer->ChangeAnimation("Idle");

	BossRenderer->SetStartEvent("Idle", [&](GameEngineRenderer* _Renderer)
		{
			BossRenderer->SetPivotType(PivotType::Center);
			BossRenderer->Transform.SetLocalPosition({37, 321});
			FlowerRenderer->On();
		}
	);

	BossRenderer->SetStartEvent("Death", [&](GameEngineRenderer* _Renderer)
		{
			BossRenderer->SetPivotType(PivotType::Bottom);
			BossRenderer->Transform.SetLocalPosition({});
			FlowerRenderer->Off();
		}
	);

	FlowerRenderer->CreateAnimation("Flower", "Lucid_Phase1_Flower", 0.15f);
	FlowerRenderer->SetPivotType(PivotType::Bottom);
	FlowerRenderer->ChangeAnimation("Flower");
	FlowerRenderer->Transform.SetLocalPosition({ -5, 3 });
}

void Boss_Lucid_Phase1::Update(float _Delta)
{
	BaseBossActor::Update(_Delta);

	// TestCode
	if (true == GameEngineInput::IsDown('9'))
	{
		BossRenderer->ChangeAnimation("Idle");
	}

	if (true == GameEngineInput::IsDown('0'))
	{
		BossRenderer->ChangeAnimation("Death");
	}
}
