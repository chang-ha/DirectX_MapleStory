#pragma once
#include "ContentLevel.h"
#include "RenderActor.h"

class FallingObject : public RenderActor
{
	friend class Lucid_Phase2;
private:
	template <typename RenderEnum, typename DepthEnum>
	void Init(int _ObjectNumber, float _Speed, float _StartPos, RenderEnum _RenderOrder = RenderOrder::BACKGROUNDOBJECT, DepthEnum _RenderDepth = RenderDepth::backgroundobject)
	{
		Init(_ObjectNumber, _Speed, _StartPos, static_cast<int>(_RenderOrder), static_cast<float>(_RenderDepth));
	}

	void Init(int _ObjectNumber, float _Speed, float _StartPos, int _RenderOrder = static_cast<int>(RenderOrder::BACKGROUNDOBJECT), float _RenderDepth = static_cast<float>(RenderDepth::backgroundobject));
	void Update(float _Delta) override;

	float ObjectSpeed = 0.0f;
	float StartPos = 0.0f;
};

class FootHold : public RenderActor
{
	friend class Lucid_Phase2;
public:
	enum class FootHoldState
	{
		Idle,
		Break,
	};

	void ChangeState(FootHoldState _State);
	void StateUpdate(float _Delta);
private:
	int FootHoldNumber = -1;
	float FootHoldYPos = 0.0f;
	float BreakTime = 0.0f;
	FootHoldState State = FootHoldState::Idle;

	void Init(int _FootHoldNumber);

	void IdleStart();
	void BreakStart();
	void IdleUpdate(float _Delta);
	void BreakUpdate(float _Delta);
};

#define Lase_Cooldown 0.7f
#define Golem_Cooldown 10.0f 

class Lucid_Phase2 : public ContentLevel
{
	friend FallingObject;
public:
	// constructer destructer
	Lucid_Phase2();
	~Lucid_Phase2();

	// delete function
	Lucid_Phase2(const Lucid_Phase2& _Ohter) = delete;
	Lucid_Phase2(Lucid_Phase2&& _Ohter) noexcept = delete;
	Lucid_Phase2& operator=(const Lucid_Phase2& _Other) = delete;
	Lucid_Phase2& operator=(Lucid_Phase2&& _Other) noexcept = delete;

	void CallDragon();
	void SummonGolem();
	void BreakFootHold(int _FootHoldNumber);
	void LucidLaserOn();
	void LucidLaserOff()
	{
		LaserPatternValue = false;
	}

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;

private:
	bool LaserPatternValue = false;
	bool OnceFadeAlphaSetting = true;
	float LaserCooldown = Lase_Cooldown;
	float GolemCooldown = Golem_Cooldown;
	int PrevFootHold = -1;
	float4 CurMapScale = float4::ZERO;
	std::shared_ptr<class Dragon> LeftDragon = nullptr;
	std::shared_ptr<class Dragon> RightDragon = nullptr;
	std::shared_ptr<class ContentBackGround> Back = nullptr;
	std::shared_ptr<class Boss_Lucid_Phase2> Boss = nullptr;
	std::shared_ptr<class Player> CurPlayer = nullptr;
	std::shared_ptr<class SkillManager> SkillManagerActor = nullptr;

	// Map Detail
	void ObjectUpdate(float _Delta);
	std::vector<int> FootHoldsNumber;
	std::shared_ptr<RenderActor> BG_LucidLaser = nullptr;
	std::vector<std::shared_ptr<FootHold>> AllFootHolds;
	std::vector<std::shared_ptr<FallingObject>> MapObjects;
};

