#pragma once

class Laser : public GameEngineActor
{
public:
	// constructer destructer
	Laser();
	~Laser();

	// delete function
	Laser(const Laser& _Ohter) = delete;
	Laser(Laser&& _Ohter) noexcept = delete;
	Laser& operator=(const Laser& _Other) = delete;
	Laser& operator=(Laser&& _Other) noexcept = delete;

	void Init(std::string_view _LaserName);
	void SetAngle(float _Angle);

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> LaserRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> LaserCollision = nullptr;

};

