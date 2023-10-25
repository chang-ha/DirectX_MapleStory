#pragma once

enum class Phase
{
	Phase1 = 1,
	Phase2 = 2,
};

class ButterFly_Ball : public GameEngineActor
{
	// friend class ButterFly;
public:
	// constructer destructer
	ButterFly_Ball();
	~ButterFly_Ball();

	// delete function
	ButterFly_Ball(const ButterFly_Ball& _Ohter) = delete;
	ButterFly_Ball(ButterFly_Ball&& _Ohter) noexcept = delete;
	ButterFly_Ball& operator=(const ButterFly_Ball& _Other) = delete;
	ButterFly_Ball& operator=(ButterFly_Ball&& _Other) noexcept = delete;
	
	void Init(Phase _Phase)
	{
		Init(static_cast<int>(_Phase));
	}

	void SetDirVector(const float4& _Vector)
	{
		DirVector = _Vector;
	}

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	float Speed = 150.0f;
	float4 DirVector = float4::ZERO;
	std::shared_ptr<GameEngineSpriteRenderer> BallRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BallCollision = nullptr;

	void Init(int _Phase);

};

