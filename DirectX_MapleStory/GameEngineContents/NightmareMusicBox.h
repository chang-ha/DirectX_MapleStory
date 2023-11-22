#pragma once
#include "ContentActor.h"

class NightmareMusicBox : public ContentBaseActor
{
public:
	// constructer destructer
	NightmareMusicBox();
	~NightmareMusicBox();

	// delete function
	NightmareMusicBox(const NightmareMusicBox& _Ohter) = delete;
	NightmareMusicBox(NightmareMusicBox&& _Ohter) noexcept = delete;
	NightmareMusicBox& operator=(const NightmareMusicBox& _Other) = delete;
	NightmareMusicBox& operator=(NightmareMusicBox&& _Other) noexcept = delete;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> BoxRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> BoxCollision = nullptr;
};

