#include "PreCompile.h"

#include "ContentLevel.h"
#include "ContentMap.h"
#include "FadeObject.h"
#include "ContentMouse.h"
#include "ContentButton.h"
#include "RenderActor.h"

void FlowObject::Init(std::string_view _SpriteName, float _ObjectSpeed, const float4& _StartPos, const float4& _EndPos)
{
	if (nullptr == GameEngineSprite::Find(_SpriteName))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\MapObject\\FlowObject\\" + std::string(_SpriteName));
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	RenderActor::Init(RenderOrder::MAPOBJECT, RenderDepth::mapobject);
	Renderer->SetSprite(_SpriteName);
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

	std::shared_ptr<GameEngineCamera> UICamera = GetCamera(static_cast<int>(ECAMERAORDER::UI));
	UICamera->Transform.SetLocalPosition(GlobalValue::GetDirectXWinScale().Half());
}

void ContentLevel::Update(float _Delta)
{
}

void ContentLevel::ResourcesRelease()
{

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
	ResourcesRelease();
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