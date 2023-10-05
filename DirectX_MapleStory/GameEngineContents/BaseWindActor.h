#pragma once

class BaseWindActor : public GameEngineActor
{
public:
	// constructer destructer
	BaseWindActor();
	~BaseWindActor();

	// delete function
	BaseWindActor(const BaseWindActor& _Ohter) = delete;
	BaseWindActor(BaseWindActor&& _Ohter) noexcept = delete;
	BaseWindActor& operator=(const BaseWindActor& _Other) = delete;
	BaseWindActor& operator=(BaseWindActor&& _Other) noexcept = delete;

	static std::shared_ptr<BaseWindActor> CreateMercilessWind();
	static void CreateTriflingWind();


protected:
	float LiveTime = 5.0f;
	float DirAngle = 0.0f;
	float Speed = 600.0f;
	float RotationSpeed = 0.0f;
	float4 MoveVector = float4::ZERO;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<GameEngineCollision> DetectCollision;
	std::shared_ptr<GameEngineCollision> HitCollision;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Init(std::string_view _WindName);

private:
};

