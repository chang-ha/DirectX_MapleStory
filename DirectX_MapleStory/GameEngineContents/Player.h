#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
// Ό³Έν :
class Player : public GameEngineActor
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

	void TestInit(std::string_view _SpriteName, UINT _Start, UINT _End);

protected:
	void Start();
	void Update(float _Delta);
private:
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;
};

