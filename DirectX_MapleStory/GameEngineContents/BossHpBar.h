#pragma once

class BossHpBarStruct
{
	friend class BossHpBar;
	// Frame
	std::shared_ptr<GameEngineSpriteRenderer> BossFace = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpStart = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpMiddle = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpEnd = nullptr;
	// HpBar
	std::shared_ptr<GameEngineSpriteRenderer> HpBack = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpFront = nullptr;
	// DeathCount
	std::shared_ptr<GameEngineSpriteRenderer> DeathCountBG = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> DeathCountNum = nullptr;
	// HpRatio
	std::shared_ptr<GameEngineSpriteRenderer> HpRatioBG = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpNum1 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpNum2 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpDot = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpNum3 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpPercent = nullptr;
};

class BossHpBar : public GameEngineActor
{
public:
	// constructer destructer
	BossHpBar();
	~BossHpBar();

	// delete function
	BossHpBar(const BossHpBar& _Ohter) = delete;
	BossHpBar(BossHpBar&& _Ohter) noexcept = delete;
	BossHpBar& operator=(const BossHpBar& _Other) = delete;
	BossHpBar& operator=(BossHpBar&& _Other) noexcept = delete;

	inline void LinkBossHP(int* _BossHP)
	{
		BossHP = _BossHP;
		MaxBossHP = *_BossHP;
		OneLifeValue = *_BossHP / 10;
	}

	void CalcuLifeCount();
	void CalueLifePercent();

protected:
	int MaxBossHP = 0;
	int OneLifeValue = 0;
	int PrevLifeCount = 0;
	int LifeCount = 0;
	int* BossHP = nullptr;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	BossHpBarStruct BossHpBarFrame;
};

