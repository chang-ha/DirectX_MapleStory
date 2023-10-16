#pragma once
#include <GameEngineCore/GameEngineActor.h>

#define MAX_GRAVITY_FORCE 1400.0f

#define UP_PIXEL_LIMIT 4
#define DOWN_PIXEL_LIMIT 4

class GameEngineSpriteRenderer;
class ContentLevel;
class ContentActor : public GameEngineActor
{
public:
	// constructer destructer
	ContentActor();
	~ContentActor();

	// delete function
	ContentActor(const ContentActor& _Ohter) = delete;
	ContentActor(ContentActor&& _Ohter) noexcept = delete;
	ContentActor& operator=(const ContentActor& _Other) = delete;
	ContentActor& operator=(ContentActor&& _Other) noexcept = delete;

	inline void GravityOn()
	{
		IsGravity = true;
	}

	inline void GravityOff()
	{
		IsGravity = false;
	}

	void AirResisOn(ActorDir _Dir = ActorDir::Null, const float _ResistanceForce = 0.0f)
	{
		IsAirResis = true;
		AirResisDir = _Dir;
		ResistanceForce = _ResistanceForce;
	}

	void AirResisOff()
	{
		IsAirResis = false;
		AirResisDir = ActorDir::Null;
		ResistanceForce = 0.0f;
	}

	void PlusMoveVectorForce(const float4& _Force)
	{
		MoveVectorForce += _Force;
	}

	inline const float4 GetMoveVectorForce()
	{
		return MoveVectorForce;
	}

	inline void GravityReset()
	{
		GravityForce = 0.0f;
	}

	void MoveVectorForceReset()
	{
		MoveVectorForce = float4::ZERO;
	}

	inline void MoveVectorForceXReset()
	{
		MoveVectorForce.X = 0.0f;
	}

	inline void MoveVectorForceYReset()
	{
		MoveVectorForce.Y = 0.0f;
	}

	inline const ActorDir GetDir()
	{
		return Dir;
	}

	inline void SetDir(ActorDir _Dir)
	{
		Dir = _Dir;
	}

	void Gravity(float _Delta);
	void AirResistance(float _Delta);

protected:
	bool IsGround = true;
	ActorDir Dir = ActorDir::Null;
	float GravityForce = 0.0f;
	float MaxGraviry = 10.0f;
	float4 MoveVectorForce = float4::ZERO;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	bool CheckGround(float4 PlusCheckPos = float4::ZERO);
	GameEngineColor CheckGroundColor(float4 PlusCheckPos = float4::ZERO);

private:
	bool IsGravity = true;
	bool IsAirResis = false;
	float GravitySpeed = 15000.0f;
	ActorDir AirResisDir = ActorDir::Null;
	float ResistanceForce = 0.0f;
};

