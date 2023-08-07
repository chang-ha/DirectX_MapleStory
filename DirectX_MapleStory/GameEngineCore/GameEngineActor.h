#pragma once
#include "GameEngineCoreObject.h"
#include <list>

// 설명 :
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


	template<typename ObjectType>
	std::shared_ptr<ObjectType> CreateComponent(int _Order = 0)
	{
		std::shared_ptr<class GameEngineComponent> NewChild = std::make_shared<ObjectType>();
		NewChild->SetParent(this);
		NewChild->Start();
		Childs[_Order].push_back(NewChild);

		// GameEngineObject형으로 사용하고 있다면
		// 내가 잘못형변환하면 Monster 였는데? Player <= 미친듯한 메모리 크러시를 일으킵니다.
		// 이녀석은 문제가 이유를 알수 없게 터진다??????
		// 이포인터가 상속관계이 있고 가상함수 테이블을 가지고 있다면
		// dynamic_cast를 통해서 안전하게 형변환이 가능하다.
		// std::shared_ptr 진짜 포인터는 아니기 때문에 dynamic_cast 해야할 상황에서
		// 아래와 같은 함수를 사용하면 된다.
		return std::dynamic_pointer_cast<ObjectType>(NewChild);
	}

	class GameEngineLevel* GetLevel();

protected:

private:
	// 다형성은 무조건 위쪽을 가질수록 범용성이 높아집니다.
	// 그리고 + 이런 기능은 
	// Renderer와 Collision : GameEngineComponent

};

