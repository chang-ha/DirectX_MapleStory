#pragma once

class TowerWall : public GameEngineActor
{
	friend class ClockTowerBaseLevel;
public:
	// constructer destructer
	TowerWall();
	~TowerWall();

	// delete function
	TowerWall(const TowerWall& _Ohter) = delete;
	TowerWall(TowerWall&& _Ohter) noexcept = delete;
	TowerWall& operator=(const TowerWall& _Other) = delete;
	TowerWall& operator=(TowerWall&& _Other) noexcept = delete;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Release() override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> WallRenderer = nullptr;
};

