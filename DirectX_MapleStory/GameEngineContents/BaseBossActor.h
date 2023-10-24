#pragma once

#define PhantasmalWind_Colldown 5.0f
#define Summon_Dragon_Cooldown 13.0f

class BaseBossActor : public GameEngineActor
{
public:
	// constructer destructer
	BaseBossActor();
	~BaseBossActor();

	// delete function
	BaseBossActor(const BaseBossActor& _Ohter) = delete;
	BaseBossActor(BaseBossActor&& _Ohter) noexcept = delete;
	BaseBossActor& operator=(const BaseBossActor& _Other) = delete;
	BaseBossActor& operator=(BaseBossActor&& _Other) noexcept = delete;

protected:
	std::shared_ptr<GameEngineSpriteRenderer> BossRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BossCollision = nullptr;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
};

