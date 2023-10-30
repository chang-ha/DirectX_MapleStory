#include "PreCompile.h"
#include "BossHpBar.h"

BossHpBar::BossHpBar()
{

}

BossHpBar::~BossHpBar()
{

}

void BossHpBar::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BossHpBar::Start()
{
	// Frame
	BossHpBarFrame.BossFace = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpStart = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpMiddle = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpEnd = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpRatioBG = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.DeathCountBG = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.DeathCountNum = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);

	BossHpBarFrame.BossFace->SetPivotType(PivotType::RightUp);
	BossHpBarFrame.HpStart->SetPivotType(PivotType::Top);
	BossHpBarFrame.HpMiddle->SetPivotType(PivotType::Top);
	BossHpBarFrame.HpEnd->SetPivotType(PivotType::Top);
	BossHpBarFrame.HpRatioBG->SetPivotType(PivotType::RightUp);
	BossHpBarFrame.DeathCountBG->SetPivotType(PivotType::LeftTop);
	BossHpBarFrame.DeathCountNum->SetPivotType(PivotType::Top);

	BossHpBarFrame.BossFace->AutoSpriteSizeOn();
	BossHpBarFrame.HpStart->AutoSpriteSizeOn();
	BossHpBarFrame.HpEnd->AutoSpriteSizeOn();
	BossHpBarFrame.HpRatioBG->AutoSpriteSizeOn();
	BossHpBarFrame.DeathCountBG->AutoSpriteSizeOn();
	BossHpBarFrame.DeathCountNum->AutoSpriteSizeOn();

	if (nullptr == GameEngineSprite::Find("Boss_Face.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\UI\\BossHpBar");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& Childs = Files[i];
			GameEngineTexture::Load(Childs.GetStringPath());
			GameEngineSprite::CreateSingle(Childs.GetFileName());
		}
	}

	BossHpBarFrame.BossFace->SetSprite("Boss_Face.png");
	BossHpBarFrame.HpStart->SetSprite("Boss_HpStart.png");
	BossHpBarFrame.HpMiddle->SetSprite("Boss_HpMiddle.png");
	BossHpBarFrame.HpEnd->SetSprite("Boss_HpEnd.png");
	BossHpBarFrame.HpRatioBG->SetSprite("Boss_HpRatio_BG.png");
	BossHpBarFrame.DeathCountBG->SetSprite("Boss_DeathCount.png");

	BossHpBarFrame.BossFace->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 325, 0, RenderDepth::ui });
	BossHpBarFrame.HpStart->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 325, 0, RenderDepth::ui });
	BossHpBarFrame.HpMiddle->Transform.SetLocalPosition({ GlobalValue::WinScale.hX(), 0, RenderDepth::ui});
	BossHpBarFrame.HpEnd->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 325, 0, RenderDepth::ui });
	BossHpBarFrame.HpRatioBG->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 325, -37, RenderDepth::ui });
	BossHpBarFrame.DeathCountBG->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 329, -20, RenderDepth::ui });
	BossHpBarFrame.DeathCountNum->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 310, -22, RenderDepth::ui});

	BossHpBarFrame.HpMiddle->SetImageScale({ 650 , 20 });
	BossHpBarFrame.HpMiddle->RenderBaseInfoValue.VertexUVMul.X = 650;
}

void BossHpBar::Update(float _Delta)
{
	LifeCount = (*BossHP - 1) / OneLifeValue;
	if (PrevLifeCount != LifeCount)
	{
		PrevLifeCount = LifeCount;
		BossHpBarFrame.DeathCountNum->SetSprite("Boss_DeathCountNum_" + std::to_string(PrevLifeCount) + ".png");
	}
}

void BossHpBar::Release()
{

}