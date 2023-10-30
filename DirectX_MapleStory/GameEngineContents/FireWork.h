#pragma once

enum class FireWorkType
{
	FireWork1 = 1,
	FireWork2,
	FireWork3,
	FireWork4,
	FireWork5,
};

class FireWork : public GameEngineActor
{
public:
	// constructer destructer
	FireWork();
	~FireWork();

	// delete function
	FireWork(const FireWork& _Ohter) = delete;
	FireWork(FireWork&& _Ohter) noexcept = delete;
	FireWork& operator=(const FireWork& _Other) = delete;
	FireWork& operator=(FireWork&& _Other) noexcept = delete;

	void Init(FireWorkType _Type)
	{
		Init(static_cast<int>(_Type));
	}

protected:
	// void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> FireWorkRenderer = nullptr;

	void Init(int _Type);
};

