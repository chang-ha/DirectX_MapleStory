#include "PreCompile.h"
#include "CutsceneActor.h"
#include "ContentLevel.h"
#include "FadeObject.h"
#include "ReleaseFunction.h"

CutsceneActor::CutsceneActor()
{

}

CutsceneActor::~CutsceneActor()
{

}

void CutsceneActor::Init(std::string_view _BossName)
{
	BossName = _BossName;

	if (nullptr == CutRenderer)
	{
		CutRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		CutRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::ui});
	}

	if (nullptr == GameEngineSprite::Find(std::string(_BossName) + "_Cutscene"))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\Boss\\" + std::string(_BossName) + "\\Cutscene");
		GameEngineSprite::CreateFolder(std::string(_BossName.data()) + "_Cutscene", Path.GetStringPath());
	}

	CutRenderer->CreateAnimation("Cutscene", std::string(_BossName.data()) + "_Cutscene", 0.03f, -1, -1, false);
	CutRenderer->ChangeAnimation("Cutscene");
	CutRenderer->SetImageScale(GlobalValue::WinScale);

	CutRenderer->SetEndEvent("Cutscene", [&](GameEngineSpriteRenderer* _Renderer)
		{
			ContentLevel::CurContentLevel->FadeOutObject->FadeStart();
		}
	);

	std::shared_ptr<GameEngineFrameAnimation> _Animation = CutRenderer->FindAnimation("Cutscene");
	_Animation->Inter[0] = 1.0f;
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
		ReleaseFunction::FolderRelease(std::string(BossName) + "_Cutscene", "Cutscene_");
	}
}