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
	BossHpBarFrame.HpBack = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpFront = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.DeathCountBG = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.DeathCountNum = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);


	BossHpBarFrame.BossFace->SetPivotType(PivotType::RightUp);
	BossHpBarFrame.HpStart->SetPivotType(PivotType::Top);
	BossHpBarFrame.HpMiddle->SetPivotType(PivotType::Top);
	BossHpBarFrame.HpEnd->SetPivotType(PivotType::Top);
	BossHpBarFrame.HpBack->SetPivotType(PivotType::Left);
	BossHpBarFrame.HpFront->SetPivotType(PivotType::Left);
	BossHpBarFrame.DeathCountBG->SetPivotType(PivotType::LeftTop);
	BossHpBarFrame.DeathCountNum->SetPivotType(PivotType::Top);

	BossHpBarFrame.BossFace->AutoSpriteSizeOn();
	BossHpBarFrame.HpStart->AutoSpriteSizeOn();
	BossHpBarFrame.HpEnd->AutoSpriteSizeOn();
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
	BossHpBarFrame.DeathCountBG->SetSprite("Boss_DeathCount.png");
	BossHpBarFrame.HpBack->SetSprite("Boss_BackHp.png");
	BossHpBarFrame.HpFront->SetSprite("Boss_FrontHp.png");

	BossHpBarFrame.BossFace->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 325, 0, RenderDepth::ui });
	BossHpBarFrame.HpStart->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 325, 0, RenderDepth::ui });
	BossHpBarFrame.HpMiddle->Transform.SetLocalPosition({ GlobalValue::WinScale.hX(), 0, RenderDepth::ui});
	BossHpBarFrame.HpEnd->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() + 325, 0, RenderDepth::ui });
	BossHpBarFrame.DeathCountBG->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 329, -20, RenderDepth::ui });
	BossHpBarFrame.DeathCountNum->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 310, -22, RenderDepth::ui});

	BossHpBarFrame.HpMiddle->SetImageScale({ 650 , 20 });
	BossHpBarFrame.HpMiddle->RenderBaseInfoValue.VertexUVMul.X = 650;

	BossHpBarFrame.HpBack->SetImageScale({ 650 , 12 });
	BossHpBarFrame.HpFront->SetImageScale({ 650 , 12 });
	BossHpBarFrame.HpBack->RenderBaseInfoValue.VertexUVMul.X = 650;
	BossHpBarFrame.HpFront->RenderBaseInfoValue.VertexUVMul.X = 650;
	BossHpBarFrame.HpBack->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 325, -10, RenderDepth::ui });
	BossHpBarFrame.HpFront->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 325, -10, RenderDepth::ui });

	// Percent Number
	BossHpBarFrame.HpRatioBG = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpPercent = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpDot = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpNum1 = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpNum2 = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpNum3 = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);

	BossHpBarFrame.HpRatioBG->SetPivotType(PivotType::RightUp);

	BossHpBarFrame.HpRatioBG->SetSprite("Boss_HpRatio_BG.png");
	BossHpBarFrame.HpDot->SetSprite("Boss_HpRatioNum_dot.png");
	BossHpBarFrame.HpPercent->SetSprite("Boss_HpRatioNum_percent.png");
	BossHpBarFrame.HpNum1->SetSprite("Boss_HpRatioNum_1.png");
	BossHpBarFrame.HpNum2->SetSprite("Boss_HpRatioNum_0.png");
	BossHpBarFrame.HpNum3->SetSprite("Boss_HpRatioNum_0.png");

	BossHpBarFrame.HpRatioBG->AutoSpriteSizeOn();
	BossHpBarFrame.HpNum1->SetImageScale({ 6, 8 });
	BossHpBarFrame.HpNum2->SetImageScale({ 6, 8 });
	BossHpBarFrame.HpDot->SetImageScale({ 1,1 });
	BossHpBarFrame.HpNum3->SetImageScale({ 6, 8 });
	BossHpBarFrame.HpPercent->SetImageScale({8, 8});

	BossHpBarFrame.HpRatioBG->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 325, -37, RenderDepth::ui });
	BossHpBarFrame.HpNum1->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 356, -46, RenderDepth::ui });
	BossHpBarFrame.HpNum2->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 349, -46, RenderDepth::ui });
	BossHpBarFrame.HpDot->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 345, -51, RenderDepth::ui });
	BossHpBarFrame.HpNum3->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 341, -46, RenderDepth::ui });
	BossHpBarFrame.HpPercent->Transform.SetLocalPosition({ GlobalValue::WinScale.hX() - 334, -46, RenderDepth::ui });

	BossHpBarFrame.HpDot->Off();
}

void BossHpBar::Update(float _Delta)
{
	CalcuLifeCount();
	CalueLifePercent();
}

void BossHpBar::Release()
{

}

void BossHpBar::CalcuLifeCount()
{
	LifeCount = (*BossHP - 1) / OneLifeValue;
	if (PrevLifeCount != LifeCount)
	{
		PrevLifeCount = LifeCount;
		BossHpBarFrame.DeathCountNum->SetSprite("Boss_DeathCountNum_" + std::to_string(PrevLifeCount) + ".png");
	}
}

void BossHpBar::CalueLifePercent()
{
	if (MaxBossHP == *BossHP)
	{
		return;
	}

	float CurPercent = static_cast<float>(*BossHP) / MaxBossHP * 100.0f;

	if (false == BossHpBarFrame.HpDot->IsUpdate() && MaxBossHP != *BossHP)
	{
		BossHpBarFrame.HpDot->On();
	}

	int TenDigit = static_cast<int>(CurPercent / 10);
	BossHpBarFrame.HpNum1->SetSprite("Boss_HpRatioNum_" + std::to_string(TenDigit) + ".png");
	BossHpBarFrame.HpNum1->SetImageScale({ 6, 8 });

	int OneDigit = static_cast<int>(CurPercent) % 10;
	BossHpBarFrame.HpNum2->SetSprite("Boss_HpRatioNum_" + std::to_string(OneDigit) + ".png");
	BossHpBarFrame.HpNum2->SetImageScale({ 6, 8 });

	int DotDigit = static_cast<int>(CurPercent * 10.0f) % 10;
	BossHpBarFrame.HpNum3->SetSprite("Boss_HpRatioNum_" + std::to_string(DotDigit) + ".png");
	BossHpBarFrame.HpNum3->SetImageScale({ 6, 8 });

	if (true == BossHpBarFrame.HpFront->IsUpdate() && 0 == TenDigit)
	{
		BossHpBarFrame.HpFront->Off();
	}

	if (0 != TenDigit)
	{
		BossHpBarFrame.HpFront->SetImageScale({ 65.0f * (OneDigit + DotDigit * 0.1f), 12 });
	}
	else if (0 == TenDigit)
	{
		BossHpBarFrame.HpBack->SetImageScale({ 65.0f * (OneDigit + DotDigit * 0.1f), 12 });
	}
}

