#pragma once

class DeathCountFrame
{
	friend class DeathCount;
	std::shared_ptr<GameEngineUIRenderer> CounterFrame;
	std::shared_ptr<GameEngineUIRenderer> CounterNum1;
	std::shared_ptr<GameEngineUIRenderer> CounterNum2;
};

class DeathCount : public GameEngineActor
{
public:
	// constructer destructer
	DeathCount();
	~DeathCount();

	// delete function
	DeathCount(const DeathCount& _Ohter) = delete;
	DeathCount(DeathCount&& _Ohter) noexcept = delete;
	DeathCount& operator=(const DeathCount& _Other) = delete;
	DeathCount& operator=(DeathCount&& _Other) noexcept = delete;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	DeathCountFrame Frame;
};

