#pragma once

class BossTimerFrame
{
	friend class BossTimer;
	std::shared_ptr<GameEngineUIRenderer> TimerFrame;
	std::shared_ptr<GameEngineUIRenderer> TimerNum1;
	std::shared_ptr<GameEngineUIRenderer> TimerNum2;
	std::shared_ptr<GameEngineUIRenderer> TimerNum3;
	std::shared_ptr<GameEngineUIRenderer> TimerNum4;
};

class BossTimer : public GameEngineActor
{
public:
	static float TimeValue;

	// constructer destructer
	BossTimer();
	~BossTimer();

	// delete function
	BossTimer(const BossTimer& _Ohter) = delete;
	BossTimer(BossTimer&& _Ohter) noexcept = delete;
	BossTimer& operator=(const BossTimer& _Other) = delete;
	BossTimer& operator=(BossTimer&& _Other) noexcept = delete;

	static void SetTimeValue(float _Value)
	{
		TimeValue = _Value;
	}

	void CalcuRemainTime();

protected:
	int PrevTenMinute = 0;
	int PrevOneMinute = 0;
	int PrevTenSecond = 0;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	BossTimerFrame Frame;
};

