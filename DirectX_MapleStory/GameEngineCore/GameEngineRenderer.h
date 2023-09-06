#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"

// ���� : GameEngineRenderer���� Order�� ������ �Ǵ� ������ �ǹ��մϴ�.
class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// �̰� ���� ���ٸ�
	// ī�޶��� ��쿡�� 
	// �̰� ������ ȣ��Ǿ� �մϴ�.
	// �ϳ��� �������� �������� �������� ī�޶� �ٶ󺼼� �ִ�.
	// ���� �Ȱܴٴϴ� ������ �ƴϴ�.
	void SetViewCameraSelect(int _Order);

	// ��� ī�޶󿡼� ���� ����

	// ���� ���ִ� ī�޶� �ٲٰڴٴ� 

	// ���ٶ󺸴� ��� ī�޶󿡼� ���� �����ϰ�
	// _Order ī�޶�� �̵��ϴ°�.
	// void SetChangeViewCameraAllClear(int _Order);

	template <typename EnumType>
	void SetRenderOrder(EnumType _Order)
	{
		SetRenderOrder(static_cast<int>(_Order));
	}

	void SetRenderOrder(int _Order);

	void SetCameraOrder(int _Order);

protected:
	void Start();
	virtual void Render(class GameEngineCamera* _Camera, float _Delta);

	void ResSetting();
	void Draw();

private:
	class GameEngineCamera* Camera = nullptr;
	std::shared_ptr<class GameEngineInputLayOut> LayOut = nullptr;

	// int CameraOrder = 0;
};

