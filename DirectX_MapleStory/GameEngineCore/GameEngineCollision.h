#pragma once
#include "GameEngineComponent.h"
#include "GameEngineObject.h"

class EventParameter
{
public:
	std::function<void(GameEngineCollision* ,GameEngineCollision* _Collisions)> Enter = nullptr;
	std::function<void(GameEngineCollision* ,GameEngineCollision* _Collisions)> Stay = nullptr;
	std::function<void(GameEngineCollision* ,GameEngineCollision* _Collisions)> Exit = nullptr;
};

class GameEngineCollision : public GameEngineComponent
{
	friend class GameEngineCollisionGroup;
public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	template<typename EnumType>
	bool Collision(EnumType _Order)
	{
		return Collision(static_cast<int>(_Order));
	}

	bool Collision(int _Order);
	 
	template<typename EnumType>
	bool Collision(EnumType _Order, const float4& _NextPos)
	{
		return Collision(static_cast<int>(_Order), _NextPos);
	}

	bool Collision(int _Order, const float4& _NextPos);

	template<typename EnumType>
	bool Collision(EnumType _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
	{
		return Collision(static_cast<int>(_Order), _Function);
	}

	bool Collision(int _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function);

	template<typename EnumType>
	bool Collision(EnumType _Order, const float4& _NextPos, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function)
	{
		return Collision(static_cast<int>(_Order), _NextPos, _Function);
	}
	bool Collision(int _Order, const float4& _NextPos, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collisions)> _Function);

	template<typename EnumType>
	bool CollisionEvent(EnumType _Order, const EventParameter& _Event)
	{
		return CollisionEvent(static_cast<int>(_Order), _Event);
	}

	bool CollisionEvent(int _Order, const EventParameter& _Event);

	ColType GetCollisionType()
	{
		return CollisionType;
	}

protected:
	void Start() override;
	void Release() override;

private:
	ColType CollisionType = ColType::SPHERE2D;
	std::set<std::shared_ptr<GameEngineCollision>> Others;
};

