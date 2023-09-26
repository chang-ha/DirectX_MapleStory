#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"
#include "GameEngineMesh.h"
#include "GameEngineMaterial.h"
#include "GameEngineRenderUnit.h"

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

	void SetCameraOrder(ECAMERAORDER _Order)
	{
		SetCameraOrder(static_cast<int>(_Order));
	}
	void SetCameraOrder(int _Order);

	// Create PushBack������ �ƴմϴ�.
	// 0�� ���� ����Ʈ�� ����ٰ� ġ�� 0��°�� ���� ����Ʈ�� ����� ���ϴ�.
	// 8���� �ϸ� vector�� Ȯ��ǰ� 8��°�� ���� ����Ʈ�� ����� �˴ϴ�.
	std::shared_ptr<GameEngineRenderUnit> CreateAndFindRenderUnit(int _Index = 0);

	void SetMesh(std::string_view _Name, int _Index = 0);
	void SetMaterial(std::string_view _Name, int _Index = 0);

	GameEngineShaderResHelper& GetShaderResHelper(int _Index = 0);

protected:
	std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;

	void Start();
	virtual void Render(class GameEngineCamera* _Camera, float _Delta);

private:
	class GameEngineCamera* Camera = nullptr;
};

