#pragma once

class BarFrame
{
	friend class PlayerUIManager;
	std::shared_ptr<GameEngineUIRenderer> Bar = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Slash = nullptr;
	std::shared_ptr<GameEngineUIRenderer> CurStatus_Hund = nullptr;
	std::shared_ptr<GameEngineUIRenderer> CurStatus_Ten = nullptr;
	std::shared_ptr<GameEngineUIRenderer> CurStatus_One = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MaxStatus_Hund = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MaxStatus_Ten = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MaxStatus_One = nullptr;
};

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
	void Update(float _Delta) override;
	void Release() override;

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
	BarFrame HP;
	BarFrame MP;
	std::shared_ptr<GameEngineUIRenderer> Bar_Name = nullptr;

	void PlayerStatusUpdate(float _Delta);
	void HPUpdate(float _Delta);
	void MPUpdate(float _Delta);
};

