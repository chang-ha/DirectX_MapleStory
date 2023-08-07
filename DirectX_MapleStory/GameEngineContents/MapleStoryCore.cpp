#include "PreCompile.h"
#include "MapleStoryCore.h"
#include "TitleLevel.h"

MapleStoryCore::MapleStoryCore()
{

}

MapleStoryCore::~MapleStoryCore()
{

}

void MapleStoryCore::Start()
{
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::ChangeLevel("TitleLevel");
}

void MapleStoryCore::Update(float _Delta)
{
	GameEngineCore::MainWindow.DoubleBuffering();
}

void MapleStoryCore::Release()
{

}