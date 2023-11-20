#include "PreCompile.h"
#include "FireWork.h"
#include "ReleaseFunction.h"

FireWork::FireWork()
{

}

FireWork::~FireWork()
{

}

void FireWork::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void FireWork::Start()
{
	FireWorkRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BACKGROUNDOBJECT);
	FireWorkRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::backgroundobject});
	FireWorkRenderer->AutoSpriteSizeOn();
	FireWorkRenderer->SetPivotType(PivotType::Top);
}

void FireWork::Release()
{
	if (nullptr != FireWorkRenderer)
	{
		FireWorkRenderer->Death();
		FireWorkRenderer = nullptr;
	}

	if (nullptr != GameEngineSprite::Find("FireWork" + std::to_string(Type)))
	{
		ReleaseFunction::FolderRelease("FireWork" + std::to_string(Type), "FireWork" + std::to_string(Type) + "_");
	}
}

void FireWork::Init(int _Type)
{
	Type = _Type;

	if (nullptr == GameEngineSprite::Find("FireWork" + std::to_string(Type)))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Lachlen\\FireWork" + std::to_string(Type));
		GameEngineSprite::CreateFolder("FireWork" + std::to_string(Type), Dir.GetStringPath());
	}

	std::shared_ptr<GameEngineFrameAnimation> _Animation = nullptr;
	switch (Type)
	{
	case 1:
		FireWorkRenderer->CreateAnimation("FireWork", "FireWork" + std::to_string(Type), 0.12f);
		_Animation = FireWorkRenderer->FindAnimation("FireWork");
		_Animation->Inter[15] = 3.0f;
		break;
	case 2:
		FireWorkRenderer->CreateAnimation("FireWork", "FireWork" + std::to_string(Type), 0.1f);
		_Animation = FireWorkRenderer->FindAnimation("FireWork");
		_Animation->Inter[15] = 3.0f;
		break;
	case 3:
		FireWorkRenderer->CreateAnimation("FireWork", "FireWork" + std::to_string(Type), 0.18f);
		_Animation = FireWorkRenderer->FindAnimation("FireWork");
		_Animation->Inter[16] = 3.0f;
		break;
	case 4:
		FireWorkRenderer->CreateAnimation("FireWork", "FireWork" + std::to_string(Type), 0.18f);
		_Animation = FireWorkRenderer->FindAnimation("FireWork");
		_Animation->Inter[16] = 2.6f;
		break;
	case 5:
		FireWorkRenderer->CreateAnimation("FireWork", "FireWork" + std::to_string(Type));
		_Animation = FireWorkRenderer->FindAnimation("FireWork");
		_Animation->Inter[11] = 1.5f;
		break;
	default:
		break;
	}
	FireWorkRenderer->ChangeAnimation("FireWork");
}
