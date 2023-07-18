#pragma once

// �츮������ ���� �⺻����
// Start �̳༮�� ���۵ɶ�
// Update �̳༮�� ������Ʈ�ɶ�
// Release �̳༮�� ��������

// ���� :
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

