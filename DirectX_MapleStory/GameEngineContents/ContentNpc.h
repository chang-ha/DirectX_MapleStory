#pragma once

class ContentNpc : public GameEngineActor
{
public:
	// constructer destructer
	ContentNpc();
	~ContentNpc();

	// delete function
	ContentNpc(const ContentNpc& _Ohter) = delete;
	ContentNpc(ContentNpc&& _Ohter) noexcept = delete;
	ContentNpc& operator=(const ContentNpc& _Other) = delete;
	ContentNpc& operator=(ContentNpc&& _Other) noexcept = delete;

	void Init(std::string_view _NpcName, ActorDir _Dir);

protected:
	std::shared_ptr<GameEngineSpriteRenderer> NpcRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> NpcCollision = nullptr;
	EventParameter NpcEvent;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void CollisionEnter(GameEngineCollision* _this, GameEngineCollision* _Other);
	void CollisionStay(GameEngineCollision* _this, GameEngineCollision* _Other);
	void CollisionExit(GameEngineCollision* _this, GameEngineCollision* _Other);

private:


};

