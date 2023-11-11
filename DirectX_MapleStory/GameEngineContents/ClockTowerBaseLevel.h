#pragma once
#include "ContentLevel.h"

#define RESPAWN_TIME 6.0f

class FieldMonsterInfo
{
public:
	float4 RespawnPos = float4::ZERO;
	std::shared_ptr<class FieldMonster> Monster;
};

class ClockTowerBaseLevel : public ContentLevel
{
public:
	// constructer destructer
	ClockTowerBaseLevel();
	~ClockTowerBaseLevel();

	// delete function
	ClockTowerBaseLevel(const ClockTowerBaseLevel& _Ohter) = delete;
	ClockTowerBaseLevel(ClockTowerBaseLevel&& _Ohter) noexcept = delete;
	ClockTowerBaseLevel& operator=(const ClockTowerBaseLevel& _Other) = delete;
	ClockTowerBaseLevel& operator=(ClockTowerBaseLevel&& _Other) noexcept = delete;

	template <typename MonsterType>
	void CreateMonster(float4 _RespawnPos)
	{
		FieldMonsterInfo Info;

		std::shared_ptr<class FieldMonster> _Monster = CreateActor<MonsterType>(UpdateOrder::Monster);
		PlaceMonster(_Monster, _RespawnPos);

		Info.Monster = _Monster;
		Info.RespawnPos = _RespawnPos;

		AllMonster.push_back(Info);
	}

protected:
	float RespawnTime = RESPAWN_TIME;
	float4 CurMapScale = float4::ZERO;
	float4 StartPos = float4::ZERO;

	std::vector<FieldMonsterInfo> AllMonster;
	std::shared_ptr<class ContentBackGround> Back = nullptr;
	std::shared_ptr<class Player> CurPlayer = nullptr;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

private:
	void RespawnMonster(float _Delta);
	void PlaceMonster(std::shared_ptr<class FieldMonster> _Monster, float4 _RespawnPos);
};

