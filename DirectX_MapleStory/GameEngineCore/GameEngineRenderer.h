#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"
#include "GameEngineMesh.h"
#include "GameEngineMaterial.h"
#include "GameEngineShaderResHelper.h"

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

	// Renderer�� �Ž��� ��Ƽ������ ������ �����
	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);

protected:
	std::shared_ptr<class GameEngineInputLayOut> LayOut = nullptr;
	std::shared_ptr<class GameEngineMesh> Mesh = nullptr;
	std::shared_ptr<class GameEngineMaterial> Material = nullptr;
	GameEngineShaderResHelper ShaderResHelper;

	void Start();
	virtual void Render(class GameEngineCamera* _Camera, float _Delta);

	void ResSetting();
	void Draw();

private:
	class GameEngineCamera* Camera = nullptr;
};

