#pragma once

enum class MonsterState
{
	Idle,
	Hit,
	Death,
};
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
	float4 MonsterScale = float4::ZERO;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> MainCollision = nullptr;

	//TestCode
	EventParameter MonsterEvent;
};

