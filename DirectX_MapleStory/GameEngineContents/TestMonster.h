#pragma once
#include "ContentActor.h"

class TestMonster : public ContentBaseActor
{
public:
	// constructer destructer
	TestMonster();
	~TestMonster();

	// delete function
	TestMonster(const TestMonster& _Ohter) = delete;
	TestMonster(TestMonster&& _Ohter) noexcept = delete;
	TestMonster& operator=(const TestMonster& _Other) = delete;
	TestMonster& operator=(TestMonster&& _Other) noexcept = delete;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineCollision> Collision = nullptr;
};

