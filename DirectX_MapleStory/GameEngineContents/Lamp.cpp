#include "PreCompile.h"
#include "Lamp.h"

Lamp::Lamp()
{

}

Lamp::~Lamp()
{

}

void Lamp::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Lamp::Start()
{
	LampRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MAPOBJECT);
	LampRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::mapobject});
	LampRenderer->AutoSpriteSizeOn();
	LampRenderer->SetPivotType(PivotType::Top);
}

void Lamp::Update(float _Delta)
{

}

void Lamp::Release()
{
	if (nullptr != LampRenderer)
	{
		LampRenderer->Death();
		LampRenderer = nullptr;
	}
}

void Lamp::Init(int _Type)
{
	if (nullptr == GameEngineSprite::Find("Lamp" + std::to_string(_Type)))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Lachlen\\Lamp" + std::to_string(_Type));
		GameEngineSprite::CreateFolder("Lamp" + std::to_string(_Type), Dir.GetStringPath());
	}

	std::shared_ptr<GameEngineFrameAnimation> _Animation = nullptr;
	LampRenderer->CreateAnimation("Lamp", "Lamp" + std::to_string(_Type));
	LampRenderer->ChangeAnimation("Lamp");

	if (9 == _Type)
	{
		LampRenderer->SetPivotType(PivotType::Bottom);
	}
}