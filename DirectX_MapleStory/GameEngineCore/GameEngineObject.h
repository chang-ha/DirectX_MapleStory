#pragma once
#include "GameEngineTransform.h"

// �츮������ ���� �⺻����
// Start �̳༮�� ���۵ɶ�
// Update �̳༮�� ������Ʈ�ɶ�
// Release �̳༮�� ��������

// ���� :
class GameEngineObject : public std::enable_shared_from_this<GameEngineObject>
{
	friend class GameEngineLevel;
	friend class GameEngineCore;

public:
	GameEngineTransform Transform;

	// constrcuter destructer
	GameEngineObject();
	virtual ~GameEngineObject();

	// delete Function
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	virtual void Start() {}
	virtual void Update(float _Delta) {}
	virtual void Release() {}


	virtual void On()
	{
		IsUpdateValue = true;
	}

	virtual void Off()
	{
		IsUpdateValue = false;
	}

	void Death()
	{
		this->IsDeathValue = true;
	}

	virtual bool IsUpdate()
	{
		return Parent == nullptr ? true == IsUpdateValue && false == IsDeathValue : Parent->IsUpdate() && true == IsUpdateValue && false == IsDeathValue;
	}

	virtual bool IsDeath()
	{
		return Parent == nullptr ? IsDeathValue : Parent->IsDeathValue && IsDeathValue;
	}

	int GetUpdateOrder()
	{
		return UpdateOrder;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetUpdateOrder(static_cast<int>(_Order));
	}

	virtual void SetUpdateOrder(int _Order)
	{
		UpdateOrder = _Order;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

	void SetName(const std::string& _Name)
	{
		Name = _Name;
	}

	std::string GetName()
	{
		return Name;
	}

	virtual void AllUpdate(float _Delta);

	void SetParent(GameEngineObject* _Parent)
	{
		Parent = _Parent;
		// Parent->Transform.SetParent(_Parent->Transform);
	}

	template<typename ParentType>
	void SetParent(std::shared_ptr<ParentType> _Parent)
	{
		Parent = _Parent.get();
		Transform.SetParent(_Parent->Transform);
		// Parent->Transform.SetParent(_Parent->Transform);
	}

	GameEngineObject* GetParentObject()
	{
		return Parent;
	}


	template<typename ParentType>
	ParentType* GetParent()
	{
		return dynamic_cast<ParentType*>(Parent);
	}

	template<typename ConvertType>
	std::shared_ptr<ConvertType> GetDynamic_Cast_This()
	{
		std::shared_ptr<GameEngineObject> ObjectPtr = shared_from_this();
		std::shared_ptr<ConvertType> CameraPtr = std::dynamic_pointer_cast<ConvertType>(ObjectPtr);

		if (nullptr == CameraPtr)
		{
			MsgBoxAssert("���̳��� ĳ��Ʈ�� �����߽��ϴ�. �����Լ� ���̺� �θ� �������� Ȯ���غ�����. Ȥ�� �θ� �����ڿ����� ����� �Ұ����� �Լ��Դϴ�.");
		}

		return CameraPtr;
	}

protected:
	GameEngineObject* Parent = nullptr;
	// �������� ���ؼ�
	std::map<int, std::list<std::shared_ptr<class GameEngineObject>>> Childs;

private:

	std::string Name;
	float LiveTime = 0.0f;
	int UpdateOrder = 0;
	bool IsUpdateValue = true; // �̰� false�� ����� �˴ϴ�.
	bool IsDeathValue = false; // �ƿ� �޸𸮿��� ���������� �;�.

	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}

};

