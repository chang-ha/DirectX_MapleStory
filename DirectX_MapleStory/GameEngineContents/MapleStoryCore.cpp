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
#include "ServerLevel.h"
#include "Boss_WaitingRoom.h"
#include "FadeObject.h"
#include "ClockTowerOfNightMare_1th.h"
#include "CharacterSelect.h"

void LevelChangeGUI::Start()
{

}

void LevelChangeGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	std::map<std::string, std::shared_ptr<GameEngineLevel>>& AllLevels = GameEngineCore::GetAllLevel();

	for (std::pair<const std::string, std::shared_ptr<GameEngineLevel>> Pair : AllLevels)
	{
		if (ImGui::Button(Pair.first.c_str(), {120, 20}))
		{
			ContentLevel::CurContentLevel->FadeOutObject->SetChangeLevel(Pair.first);
			ContentLevel::CurContentLevel->FadeOutObject->FadeStart();
			// GameEngineCore::ChangeLevel(Pair.first);
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
	GameEngineFont::Load("메이플스토리");

	ContentResources::ContentResourcesInit();

	GameEngineGUI::CreateGUIWindow<LevelChangeGUI>("LevelChange");

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({1.0f, 1.0f, 1.0f, 1.0f});

	std::shared_ptr<GameEngineMaterial> _Mat = GameEngineResources<GameEngineMaterial>::Find("2DTexture");
	_Mat->SetDepthState("LessEqualDepth");

	GameEngineCore::CreateLevel<TitleLevel>("1.TitleLevel");
	// GameEngineCore::CreateLevel<PlayLevel>("2.PlayLevel");
	GameEngineCore::CreateLevel<ServerLevel>("2.ServerLevel");
	GameEngineCore::CreateLevel<Boss_WaitingRoom>("Boss_WaitingRoom");
	GameEngineCore::CreateLevel<Lucid_Enter>("3.Lucid_Enter");
	GameEngineCore::CreateLevel<Lucid_Phase1>("4.Lucid_Phase1");
	GameEngineCore::CreateLevel<Lucid_Next>("5.Lucid_Next");
	GameEngineCore::CreateLevel<Lucid_Phase2>("6.Lucid_Phase2");
	GameEngineCore::CreateLevel<ClockTowerOfNightMare_1th>("ClockTowerOfNightMare_1th");
	GameEngineCore::CreateLevel<CharacterSelect>("CharacterSelect");
	GameEngineCore::ChangeLevel("CharacterSelect");
}

void MapleStoryCore::Update(float _Delta)
{

}

void MapleStoryCore::Release()
{

}