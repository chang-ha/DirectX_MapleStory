#pragma once
#include "GameEngineCoreObject.h"
#include <list>
// ���� :
class GameEngineActor : public GameEngineCoreObject
{
public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	template<typename ObjectType, typename EnumType>
	std::shared_ptr<ObjectType> CreateComponent(EnumType _Enum)
	{
		return CreateComponent<ObjectType>(static_cast<int>(_Enum));
	}

	template<typename ObjectType>
	std::shared_ptr<ObjectType> CreateComponent(int _Order = 0)
	{
		// std::shared_ptr<class GameEngineComponent> NewChild = std::make_shared<ObjectType>();
		// ComponentInit(NewChild, _Order);


		// GameEngineObject������ ����ϰ� �ִٸ�
		// ���� �߸�����ȯ�ϸ� Monster ���µ�? Player <= ��ģ���� �޸� ũ���ø� ����ŵ�ϴ�.
		// �̳༮�� ������ ������ �˼� ���� ������??????
		// �������Ͱ� ��Ӱ����� �ְ� �����Լ� ���̺��� ������ �ִٸ�
		// dynamic_cast�� ���ؼ� �����ϰ� ����ȯ�� �����ϴ�.
		// std::shared_ptr ��¥ �����ʹ� �ƴϱ� ������ dynamic_cast �ؾ��� ��Ȳ����
		// �Ʒ��� ���� �Լ��� ����ϸ� �ȴ�.
		return std::dynamic_pointer_cast<ObjectType>(CreateChild<ObjectType>(_Order)); //std::dynamic_pointer_cast<ObjectType>(NewChild);
	}

	class GameEngineLevel* GetLevel();

protected:

private:
	void ComponentInit(std::shared_ptr<class GameEngineComponent> _Component, int _Order);
	// �������� ������ ������ �������� ���뼺�� �������ϴ�.
	// �׸��� + �̷� ����� 
	// Renderer�� Collision : GameEngineComponent

};

