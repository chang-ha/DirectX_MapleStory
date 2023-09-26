#pragma once
#include "GameEngineTransform.h"
#include <memory>
// 우리엔진의 가장 기본적인
// Start 이녀석이 시작될때
// Update 이녀석이 업데이트될때
// Release 이녀석이 지워질때

class GameEngineObjectBase
{
public:
	int GetOrder()
	{
		return Order;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}


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
		return true == IsUpdateValue && false == IsDeathValue;
	}

	virtual bool IsDeath()
	{
		return IsDeathValue;
	}

protected:
	int Order = 0;
	bool IsUpdateValue = true; // 이걸 false로 만들면 됩니다.
	bool IsDeathValue = false; // 아예 메모리에서 날려버리고 싶어.
};

// 설명 :
class GameEngineObject : public GameEngineObjectBase, public std::enable_shared_from_this<GameEngineObject>
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
	virtual void LevelStart(class GameEngineLevel* _PrevLevel) {}
	virtual void LevelEnd(class GameEngineLevel* _NextLevel) {}

	bool IsUpdate() override
	{
		return Parent == nullptr ? true == IsUpdateValue && false == IsDeathValue : Parent->IsUpdate() && true == IsUpdateValue && false == IsDeath();
	}

	bool IsDeath() override
	{
		return Parent == nullptr ? IsDeathValue : Parent->IsDeath() || IsDeathValue;
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
	virtual void AllReleaseCheck();
	void AllLevelStart(class GameEngineLevel* _PrevLevel);
	void AllLevelEnd(class GameEngineLevel* _NextLevel);

	template<typename ChildType>
	std::shared_ptr<GameEngineObject> CreateChild(int _Order)
	{
		std::shared_ptr<GameEngineObject> NewChild = std::make_shared<ChildType>();
		NewChild->SetOrder(_Order);
		NewChild->SetParent(this, _Order);
		NewChild->Start();
		return NewChild;
	}

	void SetParent(GameEngineObject* _Parent, int _Order)
	{
		Parent = _Parent;
		Parent->Childs[_Order].push_back(shared_from_this());
		Transform.SetParent(_Parent->Transform);
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
		std::shared_ptr<ConvertType> ConvertPtr = std::dynamic_pointer_cast<ConvertType>(ObjectPtr);

		if (nullptr == ConvertPtr)
		{
			// MsgBoxAssert("다이나믹 캐스트에 실패했습니다. 가상함수 테이블 부모가 누구인지 확인해보세요. 혹은 부모 생성자에서는 사용이 불가능한 함수입니다.");
			return nullptr;
		}

		return ConvertPtr;
	}

	// 값형이라 어마무시한 복사가 일어나서 자주 안쓰는걸 추천 -> Const &붙여서 리턴하면 음... 정말 참조밖에 못함(해당 객체들을 전혀 사용 못함;;)
	template<typename EnumType>
	std::list<std::shared_ptr<GameEngineObject>> GetObjectGroup(EnumType _GroupIndex)
	{
		return GetObjectGroup(static_cast<int>(_GroupIndex));
	}

	std::list<std::shared_ptr<GameEngineObject>> GetObjectGroup(int _GroupIndex)
	{
		std::list<std::shared_ptr<GameEngineObject>>& Group = Childs[_GroupIndex];
		return Group;
	}

	template<typename ObjectType, typename EnumType>
	std::list<std::shared_ptr<ObjectType>> GetObjectGroupConvert(EnumType _GroupIndex)
	{
		return GetObjectGroupConvert<ObjectType>(static_cast<int>(_GroupIndex));
	}

	// 특정그룹에 있는 특정 클래스만 골라서 다이나믹캐스팅 후 리턴해주는 함수
	template<typename ObjectType>
	std::list<std::shared_ptr<ObjectType>> GetObjectGroupConvert(int _GroupIndex)
	{
		std::list<std::shared_ptr<ObjectType>> Result;
		std::list<std::shared_ptr<class GameEngineObject>>& Group = Childs[_GroupIndex];

		for (std::shared_ptr<class GameEngineObject> Obejct : Group)
		{
			// 컴파일타임어써션을 통해서 애초에 이게 가능한 일인지 알수 있는데
			// 빠르게 만들어야 하니까.
			std::shared_ptr<ObjectType> Ptr = Obejct->GetDynamic_Cast_This<ObjectType>();

			if (nullptr == Ptr)
			{
				continue;
			}

			Result.push_back(Ptr);
		}

		return Result;
	}

protected:
	GameEngineObject* Parent = nullptr;
	// 오더링을 위해서
	std::map<int, std::list<std::shared_ptr<class GameEngineObject>>> Childs;

private:

	std::string Name;
	float LiveTime = 0.0f;

	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}

	void AllRelease();
};

