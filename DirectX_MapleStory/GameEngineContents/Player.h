#pragma once
#define IDLE_ANI_SPEED 0.5f
#define WALK_ANI_SPEED 0.15f
#define SHOOT1_ANI_SPEED 0.2f
#define ROPE_ANI_SPEED 0.2f
#define ATT_ANI_SPEED 0.3f
#define DOWN_ATT_ANI_SPEED 0.5f

#include "ContentActor.h"

class Player : public ContentActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
};

