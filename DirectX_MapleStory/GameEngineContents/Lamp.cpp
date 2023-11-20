#include "PreCompile.h"
#include "Lamp.h"
#include "ReleaseFunction.h"

Lamp::Lamp()
{

}

Lamp::~Lamp()
{

}

void Lamp::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Lamp::Start()
{
	LampRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MAPOBJECT);
	LampRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::mapobject});
	LampRenderer->AutoSpriteSizeOn();
	LampRenderer->SetPivotType(PivotType::Top);
}

void Lamp::Release()
{
	if (nullptr != LampRenderer)
	{
		LampRenderer->Death();
		LampRenderer = nullptr;
	}

	if (nullptr != GameEngineSprite::Find("Lamp" + std::to_string(Type)))
	{
		ReleaseFunction::FolderRelease("Lamp" + std::to_string(Type), "Lamp" + std::to_string(Type) + "_");
	}
}

void Lamp::Init(int _Type)
{
	Type = _Type;
	if (nullptr == GameEngineSprite::Find("Lamp" + std::to_string(Type)))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Lachlen\\Lamp" + std::to_string(Type));
		GameEngineSprite::CreateFolder("Lamp" + std::to_string(Type), Dir.GetStringPath());
	}

	std::shared_ptr<GameEngineFrameAnimation> _Animation = nullptr;
	LampRenderer->CreateAnimation("Lamp", "Lamp" + std::to_string(Type));
	LampRenderer->ChangeAnimation("Lamp");

	if (9 == Type)
	{
		LampRenderer->SetPivotType(PivotType::Bottom);
	}
}