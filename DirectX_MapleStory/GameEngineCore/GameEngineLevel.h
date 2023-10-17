#pragma once
#include "GameEngineObject.h"
// ���� :
// class GameEngineActor; �̷����ǰ�
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
		NewChild->SetName(_Name);

		ActorInit(NewChild, _Order);

		// GameEngineObject������ ����ϰ� �ִٸ�
		// ���� �߸�����ȯ�ϸ� Monster ���µ�? Player <= ��ģ���� �޸� ũ���ø� ����ŵ�ϴ�.
		// �̳༮�� ������ ������ �˼� ���� ������??????
		// �������Ͱ� ��Ӱ����� �ְ� �����Լ� ���̺��� ������ �ִٸ�
		// dynamic_cast�� ���ؼ� �����ϰ� ����ȯ�� �����ϴ�.
		// std::shared_ptr ��¥ �����ʹ� �ƴϱ� ������ dynamic_cast �ؾ��� ��Ȳ����
		// �Ʒ��� ���� �Լ��� ����ϸ� �ȴ�.
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
	// LevelChange�� ��������
	// ���� ���� �����̸� LevelStart
	// ���� �׷� End
	virtual void LevelStart(GameEngineLevel* _PrevLevel) {}
	virtual void LevelEnd(GameEngineLevel* _NextLevel) {}

	// ���Ͱ��� ��ɵ�
	void AllUpdate(float _Delta) override;

	void ActorInit(std::shared_ptr<class GameEngineActor> _Actor, int _Order);

	void Render(float _Delta);

	void AllReleaseCheck() override;
	void Release() override;

	void PushCollision(std::shared_ptr<class GameEngineCollision> _Collision);

	// �̹� ���Ͱ� child�� �����ϰ� ������
	// ���� ī�޶� ��� ���� �̴ϴ�.
	std::map<int, std::shared_ptr<class GameEngineCamera>> Cameras;
	std::map<int, std::shared_ptr<class GameEngineCollisionGroup>> CollisionGroups;
};

