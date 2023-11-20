#include "PreCompile.h"

#include <GameEngineCore\GameEngineRenderTarget.h>
#include <GameEngineCore\GameEngineResources.h>

#include "MapleStoryCore.h"
#include "ContentResources.h"
#include "TitleLevel.h"
#include "Lucid_Enter.h"
#include "Lucid_Phase1.h"
#include "Lucid_Next.h"
#include "Lucid_Phase2.h"
#include "ServerLevel.h"
#include "Boss_WaitingRoom.h"
#include "FadeObject.h"
#include "CharacterSelect.h"
#include "Lachlen.h"
#include "ClockTowerOfNightMare_1th.h"
#include "ClockTowerOfNightMare_2th.h"
#include "ClockTowerOfNightMare_3th.h"
#include "ClockTowerOfNightMare_4th.h"
#include "ClockTowerOfNightMare_5th.h"

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
	GameEngineCore::CreateLevel<ServerLevel>("2.ServerLevel");
	GameEngineCore::CreateLevel<CharacterSelect>("3.CharacterSelect");
	GameEngineCore::CreateLevel<Lachlen>("4.Lachlen");
	GameEngineCore::CreateLevel<ClockTowerOfNightMare_1th>("5.ClockTowerOfNightMare_1th");
	GameEngineCore::CreateLevel<ClockTowerOfNightMare_2th>("6.ClockTowerOfNightMare_2th");
	GameEngineCore::CreateLevel<ClockTowerOfNightMare_3th>("7.ClockTowerOfNightMare_3th");
	GameEngineCore::CreateLevel<ClockTowerOfNightMare_4th>("8.ClockTowerOfNightMare_4th");
	GameEngineCore::CreateLevel<ClockTowerOfNightMare_5th>("9.ClockTowerOfNightMare_5th");
	GameEngineCore::CreateLevel<Boss_WaitingRoom>("10.Boss_WaitingRoom");
	GameEngineCore::CreateLevel<Lucid_Enter>("11.Lucid_Enter");
	GameEngineCore::CreateLevel<Lucid_Phase1>("12.Lucid_Phase1");
	GameEngineCore::CreateLevel<Lucid_Next>("13.Lucid_Next");
	GameEngineCore::CreateLevel<Lucid_Phase2>("14.Lucid_Phase2");

	GameEngineCore::ChangeLevel("3.CharacterSelect");
}


void MapleStoryCore::Update(float _Delta)
{

}

void MapleStoryCore::Release()
{

}