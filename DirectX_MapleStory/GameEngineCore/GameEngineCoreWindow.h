#pragma once
#include "GameEngineGUI.h"
#include "GAMEENGINERENDERTARGET.H"

class GameEngineImageShotWindow : public GameEngineGUIWindow
{
public:
	ImTextureID RenderTexture;
	ImVec2 Size;

public:
	void RenderTextureSetting(ImTextureID RenderTexture, ImVec2 Size);

public:
	void Start() {};
	void Initialize(class GameEngineLevel* _Level) {}
	void OnGUI(class GameEngineLevel* _Level, float _DeltaTime) override;
};


struct NameRenderTarget
{
public:
	std::string Name;
	std::shared_ptr<GameEngineRenderTarget> RenderTarget;
};

// 랜더 타겟을 만들거나.
// 설명 :
class GameEngineCoreWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	GameEngineCoreWindow();
	~GameEngineCoreWindow();

	// delete Function
	GameEngineCoreWindow(const GameEngineCoreWindow& _Other) = delete;
	GameEngineCoreWindow(GameEngineCoreWindow&& _Other) noexcept = delete;
	GameEngineCoreWindow& operator=(const GameEngineCoreWindow& _Other) = delete;
	GameEngineCoreWindow& operator=(GameEngineCoreWindow&& _Other) noexcept = delete;

	static void AddDebugRenderTarget(int _Order, const std::string_view& _Name, std::shared_ptr<GameEngineRenderTarget> _Target);

protected:
	void Start() override;
	void OnGUI(class GameEngineLevel* _Level, float _DeltaTime) override;

private:
	static std::map<int, NameRenderTarget> DebugRenderTarget;
};

