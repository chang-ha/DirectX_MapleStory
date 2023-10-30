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
	BossHpBarFrame.BossFace = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpStart = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpMiddle = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.HpEnd = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.DeathCountBG = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BossHpBarFrame.DeathCountNum = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);

	BossHpBarFrame.BossFace->AutoSpriteSizeOn();
	BossHpBarFrame.HpStart->AutoSpriteSizeOn();
	BossHpBarFrame.HpEnd->AutoSpriteSizeOn();
	BossHpBarFrame.DeathCountBG->AutoSpriteSizeOn();
	BossHpBarFrame.DeathCountNum->AutoSpriteSizeOn();
}

void BossHpBar::Update(float _Delta)
{
	
}

void BossHpBar::Release()
{

}