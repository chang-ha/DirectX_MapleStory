#pragma once

class ContentMonster : public GameEngineActor
{
public:
	ContentMonster();
	~ContentMonster();

	ContentMonster(const ContentMonster& _Other) = delete;
	ContentMonster(ContentMonster&& _Other) noexcept = delete;
	ContentMonster& operator=(const ContentMonster& _Other) = delete;
	ContentMonster& operator=(ContentMonster&& _Other) noexcept = delete;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	int HP = 0;
	std::shared_ptr<GameEngineSpriteRenderer> MonsterRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> MonsterCollision = nullptr;
};

