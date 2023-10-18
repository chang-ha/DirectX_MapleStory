#include "PreCompile.h"
#include "CutsceneActor.h"

CutsceneActor::CutsceneActor()
{

}

CutsceneActor::~CutsceneActor()
{

}

void CutsceneActor::Init(std::string_view _BossName, std::string_view _NextLevelName)
{
	BossName = _BossName;
	NextLevelName = _NextLevelName;

	if (nullptr == CutRenderer)
	{
		CutRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	}

	if (nullptr == GameEngineSprite::Find(std::string(_BossName) + "_Cutscene"))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\Boss\\" + std::string(_BossName) + "\\Cutscene");
		GameEngineSprite::CreateFolder(std::string(_BossName.data()) + "_Cutscene", Path.GetStringPath());
	}

	CutRenderer->CreateAnimation("Cutscene", std::string(_BossName.data()) + "_Cutscene", 0.03f);
	CutRenderer->ChangeAnimation("Cutscene");
	CutRenderer->SetImageScale(GlobalValue::WinScale);

	CutRenderer->SetEndEvent("Cutscene", [&](GameEngineSpriteRenderer* _Renderer)
		{
			GameEngineCore::ChangeLevel(NextLevelName);
		}
	);
}

void CutsceneActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void CutsceneActor::Release()
{
	if (nullptr != CutRenderer)
	{
		CutRenderer->Death();
		CutRenderer = nullptr;
	}

	if (nullptr != GameEngineSprite::Find(std::string(BossName) + "_Cutscene"))
	{
		GameEngineSprite::Release(std::string(BossName) + "_Cutscene");
	}
}