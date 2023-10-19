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
private:
	void Init(int _FootHoldNumber);
};

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

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;

private:
	float4 CurMapScale = float4::ZERO;
	std::shared_ptr<class Dragon> LeftDragon = nullptr;
	std::shared_ptr<class ContentBackGround> Back = nullptr;
	std::shared_ptr<class Boss_Lucid_Phase2> Boss = nullptr;
	std::shared_ptr<class Player> CurPlayer = nullptr;
	std::shared_ptr<class SkillManager> SkillManagerActor = nullptr;

	// Map Detail
	void ObjectUpdate(float _Delta);
	std::vector<std::shared_ptr<FallingObject>> MapObjects;
};

