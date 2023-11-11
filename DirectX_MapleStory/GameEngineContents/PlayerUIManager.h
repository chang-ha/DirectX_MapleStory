#pragma once

#define DELAY 0.02f

class PlayerUIManager : public GameEngineActor
{
public:
	// constructer destructer
	PlayerUIManager();
	~PlayerUIManager();

	// delete function
	PlayerUIManager(const PlayerUIManager& _Ohter) = delete;
	PlayerUIManager(PlayerUIManager&& _Ohter) noexcept = delete;
	PlayerUIManager& operator=(const PlayerUIManager& _Other) = delete;
	PlayerUIManager& operator=(PlayerUIManager&& _Other) noexcept = delete;

protected:
	void LevelStart(class GameEngineLevel* _PrevLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

private:
	float Delay = DELAY;
	int CurHPScale = 0;
	int CurMPScale = 0;

	std::shared_ptr<GameEngineUIRenderer> EXP_Bar = nullptr;
	std::shared_ptr<GameEngineUIRenderer> HP_Bar = nullptr;
	std::shared_ptr<GameEngineUIRenderer> HP_Bar_BG = nullptr;
	std::shared_ptr<GameEngineUIRenderer> HP = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MP = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Bar_Name = nullptr;

	void PlayerStatusUpdate(float _Delta);
};

