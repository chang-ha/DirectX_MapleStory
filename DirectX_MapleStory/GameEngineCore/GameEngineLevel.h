#pragma once
#include "GameEngineObject.h"

// ���� :
// class GameEngineActor; �̷����ǰ�
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;
	friend class GameEngineCamera;

public:
	// constrcuter destructer
	GameEngineLevel();
	~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineCamera> CreateCamera(int _Order, int _CameraOrder);

	template<typename ObjectType>
	std::shared_ptr<ObjectType> CreateActor(int _Order = 0)
	{
		std::shared_ptr<class GameEngineActor> NewChild = std::make_shared<ObjectType>();

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
		return Cameras[0];
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

	//void Render(float _Delta);

	void ActorRelease();

	void ActorInit(std::shared_ptr<class GameEngineActor> _Actor, int _Order);

	void Render(float _Delta);

	// �̹� ���Ͱ� child�� �����ϰ� ������
	// ���� ī�޶� ��� ���� �̴ϴ�.
	std::map<int, std::shared_ptr<class GameEngineCamera>> Cameras;
};

