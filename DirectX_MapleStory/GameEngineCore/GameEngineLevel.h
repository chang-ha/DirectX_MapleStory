#pragma once
#include "GameEngineObject.h"
// 설명 :
// class GameEngineActor; 이래도되고
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;
	friend class GameEngineCamera;
	friend class GameEngineCollision;

public:
	static bool IsDebug;

	static void OnDebug() { IsDebug = true; }
	static void OffDebug() { IsDebug = false; }

	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineCamera> CreateCamera(int _Order, ECAMERAORDER _CameraOrder)
	{
		return CreateCamera(_Order, static_cast<int>(_CameraOrder));
	}
	std::shared_ptr<class GameEngineCamera> CreateCamera(int _Order, int _CameraOrder);

	template<typename ObjectType, typename EnumType>
	std::shared_ptr<ObjectType> CreateActor(EnumType _Order)
	{
		return CreateActor<ObjectType>(static_cast<int>(_Order));
	}

	template<typename ObjectType>
	std::shared_ptr<ObjectType> CreateActor(int _Order = 0, std::string_view _Name = "")
	{
		std::shared_ptr<class GameEngineActor> NewChild = std::make_shared<ObjectType>();
		ActorInit(NewChild, _Order, _Name);

		// GameEngineObject형으로 사용하고 있다면
		// 내가 잘못형변환하면 Monster 였는데? Player <= 미친듯한 메모리 크러시를 일으킵니다.
		// 이녀석은 문제가 이유를 알수 없게 터진다??????
		// 이포인터가 상속관계이 있고 가상함수 테이블을 가지고 있다면
		// dynamic_cast를 통해서 안전하게 형변환이 가능하다.
		// std::shared_ptr 진짜 포인터는 아니기 때문에 dynamic_cast 해야할 상황에서
		// 아래와 같은 함수를 사용하면 된다.
		return std::dynamic_pointer_cast<ObjectType>(NewChild);
	}

	std::shared_ptr<GameEngineCamera> GetMainCamera()
	{
		return Cameras[static_cast<int>(ECAMERAORDER::Main)];
	}

	std::shared_ptr<GameEngineCamera> GetCamera(int _Select)
	{
		return Cameras[_Select];
	}

protected:

private:
	// LevelChange가 벌어질때
	// 내가 다음 레벨이면 LevelStart
	// 내가 그럼 End
	virtual void LevelStart(GameEngineLevel* _PrevLevel) {}
	virtual void LevelEnd(GameEngineLevel* _NextLevel) {}

	// 액터관련 기능들
	void AllUpdate(float _Delta) override;

	void ActorInit(std::shared_ptr<class GameEngineActor> _Actor, int _Order, std::string_view _Name = "");

	void Render(float _Delta);

	void AllReleaseCheck() override;
	void Release() override;

	void PushCollision(std::shared_ptr<class GameEngineCollision> _Collision);

	// 이미 액터가 child로 관리하고 있지만
	// 따로 카메라도 들고 있을 겁니다.
	std::map<int, std::shared_ptr<class GameEngineCamera>> Cameras;
	std::map<int, std::shared_ptr<class GameEngineCollisionGroup>> CollisionGroups;
};

