﻿#include "PreCompile.h"

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
	std::map<std::string, std::shared_ptr<GameEngineLevel>>& AllLevels = GameEngineCore::GetAllLevel();

	for (std::pair<const std::string, std::shared_ptr<GameEngineLevel>> Pair : AllLevels)
	{
		if (ImGui::Button(Pair.first.c_str()))
		{
			GameEngineCore::ChangeLevel(Pair.first);
		}
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
	GameEngineCore::CreateLevel<TitleLevel>("1.TitleLevel");
	GameEngineCore::CreateLevel<PlayLevel>("2.PlayLevel");
	GameEngineCore::CreateLevel<Lucid_Enter>("3.Lucid_Enter");
	GameEngineCore::CreateLevel<Lucid_Phase1>("4.Lucid_Phase1");
	GameEngineCore::CreateLevel<Lucid_Next>("5.Lucid_Next");
	GameEngineCore::CreateLevel<Lucid_Phase2>("6.Lucid_Phase2");
	GameEngineCore::ChangeLevel("6.Lucid_Phase2");
}

void MapleStoryCore::Update(float _Delta)
{

}

void MapleStoryCore::Release()
{

}