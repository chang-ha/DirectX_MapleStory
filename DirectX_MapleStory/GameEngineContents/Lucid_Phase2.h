#pragma once
#include "ContentLevel.h"
#include "RenderActor.h"

class FallingObject : public RenderActor
{
	friend class Lucid_Phase2;
private:
	void Init(int _ObjectNumber, float _Speed, float _StartPos);
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
	std::shared_ptr<class ContentBackGround> Back = nullptr;
	std::shared_ptr<class Boss_Lucid_Phase1> Boss = nullptr;
	std::shared_ptr<class Player> CurPlayer = nullptr;
	std::shared_ptr<class SkillManager> SkillManagerActor = nullptr;

	// Map Detail
	void ObjectUpdate(float _Delta);
	std::vector<std::shared_ptr<FallingObject>> MapObjects;
};

