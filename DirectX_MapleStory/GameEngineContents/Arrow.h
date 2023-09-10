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

private:
	float ArrowSpeed = 300.0f;
	ActorDir Dir = ActorDir::Null;
	std::shared_ptr<GameEngineSpriteRenderer> ArrowRenderer = nullptr;
	//TestCode
	float LiveTime = 3.0f;
};

