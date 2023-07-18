#pragma once

// 우리엔진의 가장 기본적인
// Start 이녀석이 시작될때
// Update 이녀석이 업데이트될때
// Release 이녀석이 지워질때

// 설명 :
class GameEngineObject
{
public:
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

protected:

private:

};

