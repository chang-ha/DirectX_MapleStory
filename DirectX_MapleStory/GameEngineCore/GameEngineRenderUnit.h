#pragma once
#include "GameEngineShaderResHelper.h"
#include "GameEngineFont.h"

// final�� ���̻� ��ӹ����� ���� ����
class GameEngineRenderUnit final : public GameEngineObjectBase, std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
	// constructer destructer
	GameEngineRenderUnit();
	~GameEngineRenderUnit();

	void SetText(const std::string& _Font, const std::string& _Text, float _Scale = 20.0f, const float4& Color = float4::RED, FW1_TEXT_FLAG Flag = FW1_LEFT);

	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);

	void ResSetting();
	void Draw();
	void Render();

	void SetParentRenderer(class GameEngineRenderer* _Renderer)
	{
		ParentRenderer = _Renderer;
	}

	class GameEngineRenderer* GetParentRenderer()
	{
		return ParentRenderer;
	}

	GameEngineShaderResHelper ShaderResHelper;

protected:

private:
	class GameEngineRenderer* ParentRenderer = nullptr;

	std::shared_ptr<GameEngineFont> Font = nullptr;
	std::string FontText = "";
	float FontScale = 20.0f;
	float4 FontColor = float4::RED;
	FW1_TEXT_FLAG FontFlag;

	// ���� ����ȭ ����� �ɼ� �ִ�.
	std::shared_ptr<class GameEngineInputLayOut> LayOut = nullptr;

	std::shared_ptr<class GameEngineMesh> Mesh = nullptr;
	std::shared_ptr<class GameEngineMaterial> Material = nullptr;
};

