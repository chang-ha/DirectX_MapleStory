#pragma once

class PhantasmalWind : public GameEngineActor
{
public:
	// constructer destructer
	PhantasmalWind();
	~PhantasmalWind();

	// delete function
	PhantasmalWind(const PhantasmalWind& _Ohter) = delete;
	PhantasmalWind(PhantasmalWind&& _Ohter) noexcept = delete;
	PhantasmalWind& operator=(const PhantasmalWind& _Other) = delete;
	PhantasmalWind& operator=(PhantasmalWind&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

private:
	float LiveTime = 30.0f;
	float DirAngle = 0.0f;
	float Speed = 50.0f;
	float4 MoveVector = float4::ZERO;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> PhantasmaCollision = nullptr;
};

