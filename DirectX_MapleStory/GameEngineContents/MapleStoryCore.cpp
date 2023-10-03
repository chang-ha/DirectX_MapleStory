﻿#include "PreCompile.h"
#include "MapleStoryCore.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "Lucid_Enter.h"
#include "Lucid_Phase1.h"

MapleStoryCore::MapleStoryCore()
{

}

MapleStoryCore::~MapleStoryCore()
{

}

void MapleStoryCore::Start()
{
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	// GameEngineCore::CreateLevel<Lucid_Enter>("Lucid_Enter");
	GameEngineCore::CreateLevel<Lucid_Phase1>("Lucid_Phase1");
	GameEngineCore::ChangeLevel("Lucid_Phase1");
}

void MapleStoryCore::Update(float _Delta)
{

}

void MapleStoryCore::Release()
{

}