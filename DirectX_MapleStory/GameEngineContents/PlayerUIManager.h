#pragma once

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
	float ReflectUpSpeed = 100.0f;
	float ReflectDownSpeed = 30.0f;
	int PrevHP = 0;
	int PrevMP = 0;
	float CurHPScale = 0;
	float CurMPScale = 0;

	std::shared_ptr<GameEngineUIRenderer> EXP_Bar = nullptr;
	std::shared_ptr<GameEngineUIRenderer> HP_Bar = nullptr;
	std::shared_ptr<GameEngineUIRenderer> HP_Bar_BG = nullptr;
	std::shared_ptr<GameEngineUIRenderer> HP = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MP = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Bar_Name = nullptr;

	void PlayerStatusUpdate(float _Delta);
	void HPUpdate(float _Delta);
	void MPUpdate(float _Delta);
};

