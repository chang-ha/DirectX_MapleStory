#include "PreCompile.h"

#include "ContentLevel.h"
#include "ContentMap.h"
#include "FadeObject.h"
#include "ContentMouse.h"
#include "ContentButton.h"
#include "RenderActor.h"
#include "Player.h"
#include "SkillManager.h"

void FlowObject::Init(std::string_view _SpriteName, float _ObjectSpeed, const float4& _StartPos, const float4& _EndPos)
{
	SpriteName = _SpriteName;

	if (nullptr == GameEngineSprite::Find(SpriteName))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\MapObject\\FlowObject\\" + SpriteName);
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	RenderActor::Init(RenderOrder::MAPOBJECT, RenderDepth::mapobject);
	Renderer->SetSprite(SpriteName);
	ObjectSpeed = _ObjectSpeed;
	StartPos = _StartPos;
	EndPos = _EndPos;
}

void FlowObject::Update(float _Delta)
{
	Transform.AddLocalPosition(float4::RIGHT * ObjectSpeed * _Delta);

	if (EndPos.X <= Transform.GetWorldPosition().X)
	{
		Transform.SetLocalPosition(StartPos);
	}
}

void FlowObject::Release()
{
	if (nullptr != GameEngineSprite::Find(SpriteName))
	{
		GameEngineTexture::Release(SpriteName);
		GameEngineSprite::Release(SpriteName);
	}
}

void LevelDebug::Start()
{
	
}

void LevelDebug::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::Checkbox("MapCollision", &ContentMap::IsCollisionDebug);
	ImGui::Checkbox("Collision", &GameEngineLevel::IsDebug);
	ImGui::SliderFloat("SkillEffectAlpha", &GlobalValue::SkillEffectAlpha, 0.2f, 1.0f);
	ImGui::SliderFloat("BGVolume", &GlobalValue::BGVolume, 0.0f, 1.0f);
	ImGui::SliderFloat("SkillVolume", &GlobalValue::SkillVolume, 0.0f, 1.0f);
	ImGui::SliderFloat("HitVolume", &GlobalValue::HitVolume, 0.0f, 1.0f);
	ImGui::SliderFloat("FieldMonsterVolume", &GlobalValue::FieldMonsterVolume, 0.0f, 1.0f);

	if (nullptr == Player::MainPlayer)
	{
		return;
	}

	if (true == ImGui::Button("SkillCoolDowmReset", { 150, 20 }))
	{
		Player::MainPlayer->GetSkillManager()->ResetAllSkillCoolDown();
	}
}

ContentLevel::ContentLevel()
{

}

ContentLevel::~ContentLevel()
{

}

ContentLevel* ContentLevel::CurContentLevel = nullptr;
GameEngineSoundPlayer ContentLevel::BGMPlayer;

void ContentLevel::Start()
{
	GameEngineInput::AddInputObject(this);
	GameEngineGUI::CreateGUIWindow<LevelDebug>("Option");

	std::shared_ptr<GameEngineCamera> UICamera = GetCamera(static_cast<int>(ECAMERAORDER::UI));
	UICamera->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());
}

void ContentLevel::Update(float _Delta)
{
	if ("" != PrevLevel && true == GameEngineInput::IsDown(VK_F5, this))
	{
		FadeOutObject->SetChangeLevel(PrevLevel);
		FadeOutObject->FadeStart();
	}

	if ("" != NextLevel && true == GameEngineInput::IsDown(VK_F6, this))
	{
		FadeOutObject->SetChangeLevel(NextLevel);
		FadeOutObject->FadeStart();
	}

	BGMPlayer.SetVolume(GlobalValue::BGVolume);
}

void ContentLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	CurContentLevel = this;

	if (nullptr == FadeInObject)
	{
		FadeInObject = GetLevelRenderTarget()->CreateEffect<FadeObject>();
		FadeInObject->SetFadeIn();
	}

	if (nullptr == FadeOutObject)
	{
		FadeOutObject = GetLevelRenderTarget()->CreateEffect<FadeObject>();
	}

	FadeInObject->FadeStart();
	CreateActor<ContentMouse>(UpdateOrder::UI);
}

void ContentLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	// sFadeOutObject->FadeStart();
	AllButton.clear();

	if (nullptr != FadeInObject)
	{
		FadeInObject->Death();
		FadeInObject = nullptr;
	}

	if (nullptr != FadeOutObject)
	{
		FadeOutObject->Death();
		FadeOutObject = nullptr;
	}
}

void ContentLevel::AllButtonOn()
{
	for (size_t i = 0; i < AllButton.size(); i++)
	{
		AllButton[i]->CollisionOn();
	}
}

void ContentLevel::AllButtonOff()
{
	for (size_t i = 0; i < AllButton.size(); i++)
	{
		AllButton[i]->CollisionOff();
	}
}