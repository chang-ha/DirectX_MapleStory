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
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;
};

