#pragma once
#include <GameEngineCore/GameEngineActor.h>

#define MAX_GRAVITY 1500.0f

enum class ActorDir
{
	Null,
	Right,
	Left
};

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

	inline void PlusMoveVectorForce(float4 _Force)
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

	void Gravity(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

	ActorDir Dir = ActorDir::Null;
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;

private:
	bool IsGravity = true;
	float GravitySpeed = 15000.0f;
	float GravityForce = 0.0f;
	float4 MoveVectorForce = float4::ZERO;
};

