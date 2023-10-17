#include "PreCompile.h"
#include "ContentLevel.h"
#include "ContentMap.h"

void LevelDebug::Start()
{
	
}

void LevelDebug::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Checkbox("MapCollision", &ContentMap::IsCollisionDebug);
	ImGui::Checkbox("Collision", &GameEngineLevel::IsDebug);
}

ContentLevel::ContentLevel()
{

}

ContentLevel::~ContentLevel()
{

}

ContentLevel* ContentLevel::CurContentLevel = nullptr;

void ContentLevel::Start()
{
	GameEngineInput::AddInputObject(this);
	GameEngineGUI::CreateGUIWindow<LevelDebug>("LevelDebug");

	{
		std::shared_ptr<GameEngineCamera> BackGroundCamera = CreateCamera(INT_MIN, ECAMERAORDER::MainPrev);
	}
}

void ContentLevel::Update(float _Delta)
{
}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CurContentLevel = this;
}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}