#pragma once
#include "ContentActor.h"

enum class HowlingGaleState
{
	Ready,
	Attack,
	Death
};

class HowlingGale_Actor : public ContentActor
{
	friend class HowlingGale;
public:
	static HowlingGale_Actor* MainHowlingGale;

public:
	// constructer destructer
	HowlingGale_Actor();
	~HowlingGale_Actor();

	// delete function
	HowlingGale_Actor(const HowlingGale_Actor& _Ohter) = delete;
	HowlingGale_Actor(HowlingGale_Actor&& _Ohter) noexcept = delete;
	HowlingGale_Actor& operator=(const HowlingGale_Actor& _Other) = delete;
	HowlingGale_Actor& operator=(HowlingGale_Actor&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void BlockOutMap();
	void MoveUpdate(float _Delta);

private:
	bool IsUpdate = true;
	float Speed = 200.0f;
	float LiveTime = 10.0f;
	float4 Scale = float4::ZERO;
	float4 CurMapScale = float4::ZERO;
	HowlingGaleState State = HowlingGaleState::Ready;
	std::shared_ptr<GameEngineCollision> SkillCollision = nullptr;
	std::map<std::shared_ptr<GameEngineCollision>, float> CollisionTime;

	void SetDir(ActorDir _Dir)
	{
		Dir = _Dir;
	}
};

