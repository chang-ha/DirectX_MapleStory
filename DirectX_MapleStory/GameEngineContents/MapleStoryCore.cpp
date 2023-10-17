#include "PreCompile.h"

#include <GameEngineCore\GameEngineRenderTarget.h>
#include <GameEngineCore\GameEngineResources.h>

#include "MapleStoryCore.h"
#include "ContentResources.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "Lucid_Enter.h"
#include "Lucid_Phase1.h"
#include "Lucid_Next.h"
#include "Lucid_Phase2.h"

void LevelChangeGUI::Start()
{

}

void LevelChangeGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (ImGui::Button("TitleLevel", {100, 20}))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (ImGui::Button("PlayLevel", { 100, 20 }))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}

	if (ImGui::Button("Lucid_Enter", { 100, 20 }))
	{
		GameEngineCore::ChangeLevel("Lucid_Enter");
	}

	if (ImGui::Button("Lucid_Phase1", { 100, 20 }))
	{
		GameEngineCore::ChangeLevel("Lucid_Phase1");
	}

	if (ImGui::Button("Lucid_Next", { 100, 20 }))
	{
		GameEngineCore::ChangeLevel("Lucid_Next");
	}

	if (ImGui::Button("Lucid_Phase2", { 100, 20 }))
	{
		GameEngineCore::ChangeLevel("Lucid_Phase2");
	}
}

MapleStoryCore::MapleStoryCore()
{

}

MapleStoryCore::~MapleStoryCore()
{

}

void MapleStoryCore::Start()
{
	GameEngineGUI::CreateGUIWindow<LevelChangeGUI>("LevelChange");

	ContentResources::ContentResourcesInit();
	std::shared_ptr<GameEngineMaterial> _Mat = GameEngineResources<GameEngineMaterial>::Find("2DTexture");
	_Mat->SetDepthState("LessEqualDepth");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<Lucid_Enter>("Lucid_Enter");
	GameEngineCore::CreateLevel<Lucid_Phase1>("Lucid_Phase1");
	GameEngineCore::CreateLevel<Lucid_Next>("Lucid_Next");
	GameEngineCore::CreateLevel<Lucid_Phase2>("Lucid_Phase2");
	GameEngineCore::ChangeLevel("Lucid_Phase2");
}

void MapleStoryCore::Update(float _Delta)
{

}

void MapleStoryCore::Release()
{

}