#pragma once
#include <GameEngineCore/GameEngineActor.h>

#define MAX_GRAVITY_FORCE 1500.0f
#define MAX_GRAVITY 10.0f

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

	inline void AirResisOn(ActorDir _Dir = ActorDir::Null, const float _ResistanceForce = 0.0f)
	{
		IsAirResis = true;
		AirResisDir = _Dir;
		ResistanceForce = _ResistanceForce;
	}

	inline void AirResisOff()
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

	inline void MoveVectorForceReset()
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

	void Gravity(float _Delta);
	void AirResistance(float _Delta);

protected:
	bool IsGround = true;
	ActorDir Dir = ActorDir::Null;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;

	bool CheckGround(float4 PlusCheckPos = float4::ZERO);
	GameEngineColor CheckGroundColor(float4 PlusCheckPos = float4::ZERO);

private:
	bool IsGravity = true;
	bool IsAirResis = false;
	float GravitySpeed = 15000.0f;
	float GravityForce = 0.0f;
	float4 MoveVectorForce = float4::ZERO;
	ActorDir AirResisDir = ActorDir::Null;
	float ResistanceForce = 0.0f;
};

