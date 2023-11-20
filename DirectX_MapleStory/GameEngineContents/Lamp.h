#pragma once

enum class LampType
{
	Lamp1 = 1,
	Lamp2,
	Lamp3,
	Lamp4,
	Lamp5,
	Lamp6,
	Lamp7,
	Lamp8,
	Lamp9,
	Lamp10
};

class Lamp : public GameEngineActor
{
public:
	// constructer destructer
	Lamp();
	~Lamp();

	// delete function
	Lamp(const Lamp& _Ohter) = delete;
	Lamp(Lamp&& _Ohter) noexcept = delete;
	Lamp& operator=(const Lamp& _Other) = delete;
	Lamp& operator=(Lamp&& _Other) noexcept = delete;

	void Init(LampType _Type)
	{
		Init(static_cast<int>(_Type));
	}

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Release() override;

private:
	int Type = -1;
	std::shared_ptr<GameEngineSpriteRenderer> LampRenderer = nullptr;

	void Init(int _Type);
};

