#pragma once

class Arrow : public GameEngineActor
{
public:
	Arrow();
	~Arrow();
	
	Arrow(const Arrow& _Other) = delete;
	Arrow(Arrow&& _Other) noexcept = delete;
	Arrow& operator=(const Arrow& _Other) = delete;
	Arrow& operator=(Arrow&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

	void CollisionEnter(GameEngineCollision* _this, GameEngineCollision* _Other);

private:
	float ArrowSpeed = 400.0f;
	float4 ArrowScale = float4::ZERO;
	ActorDir Dir = ActorDir::Null;
	std::shared_ptr<GameEngineSpriteRenderer> ArrowRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> ArrowCollision= nullptr;
	//TestCode
	float LiveTime = 1.0f;
	EventParameter ArrowEvent;
};

