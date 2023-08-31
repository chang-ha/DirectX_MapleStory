#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

	inline void PlusGravity(float4 _Force)
	{
		GravityForce += _Force;
	}

	inline const float4 GetGravityForce()
	{
		return GravityForce;
	}

	inline void GravityReset()
	{
		GravityForce = float4::ZERO;
	}

	void Gravity(float _Delta);
	void AirResistence(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer = nullptr;
	std::shared_ptr<ContentLevel> CurContentLevel = nullptr;

private:
	bool IsGravity = true;
	float GravitySpeed = 500.0f;
	float4 GravityForce = float4::ZERO;
};

