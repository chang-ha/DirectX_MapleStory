#pragma once

class BossHpBarStruct
{
	friend class BossHpBar;
	std::shared_ptr<GameEngineSpriteRenderer> BossFace = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpStart = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpMiddle = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HpEnd = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> DeathCountBG = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> DeathCountNum = nullptr;
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

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	BossHpBarStruct BossHpBarFrame;
};

