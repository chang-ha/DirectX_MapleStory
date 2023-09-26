#pragma once
#include "GameEngineShaderResHelper.h"

// final로 더이상 상속받을수 없게 만듦
class GameEngineRenderUnit final : public GameEngineObjectBase, std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
	// constructer destructer
	GameEngineRenderUnit();
	~GameEngineRenderUnit();

	// delete function
	GameEngineRenderUnit(const GameEngineRenderUnit& _Ohter) = delete;
	GameEngineRenderUnit(GameEngineRenderUnit&& _Ohter) noexcept = delete;
	GameEngineRenderUnit& operator=(const GameEngineRenderUnit& _Other) = delete;
	GameEngineRenderUnit& operator=(GameEngineRenderUnit&& _Other) noexcept = delete;

	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);

	void ResSetting();
	void Draw();

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

	// 추후 최적화 대상이 될수 있다.
	std::shared_ptr<class GameEngineInputLayOut> LayOut = nullptr;

	std::shared_ptr<class GameEngineMesh> Mesh = nullptr;
	std::shared_ptr<class GameEngineMaterial> Material = nullptr;
};

