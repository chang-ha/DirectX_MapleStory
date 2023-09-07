#include "PreCompile.h"
#include "TitleLevel.h"
#include "Player.h"
#include "ContentBackGround.h"
#include "SkillManager.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}


void TitleLevel::Start()
{
	ContentLevel::Start();
	float4 WinScale = GlobalValue::WinScale;
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	std::shared_ptr<ContentBackGround> Back = CreateActor<ContentBackGround>();
	Back->Init("Title.png", WinScale);
	WinScale.Y *= -1.0f;
	GetMainCamera()->Transform.SetLocalPosition(WinScale.Half());
	CreateActor<SkillManager>();
}

void TitleLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
}