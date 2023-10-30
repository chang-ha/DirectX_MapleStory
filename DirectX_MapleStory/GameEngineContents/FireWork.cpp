#include "PreCompile.h"
#include "FireWork.h"

FireWork::FireWork()
{

}

FireWork::~FireWork()
{

}

void FireWork::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void FireWork::Start()
{
	FireWorkRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BACKGROUNDOBJECT);
	FireWorkRenderer->Transform.SetLocalPosition({0, 0, RenderDepth::backgroundobject});
	FireWorkRenderer->AutoSpriteSizeOn();
	FireWorkRenderer->SetPivotType(PivotType::Top);
}

void FireWork::Update(float _Delta)
{
	
}

void FireWork::Release()
{

}

void FireWork::Init(int _Type)
{
	if (nullptr == GameEngineSprite::Find("FireWork" + std::to_string(_Type)))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentResources");
		Dir.MoveChild("ContentResources\\Textures\\MapObject\\Lachlen\\FireWork" + std::to_string(_Type));
		GameEngineSprite::CreateFolder("FireWork" + std::to_string(_Type), Dir.GetStringPath());
	}

	std::shared_ptr<GameEngineFrameAnimation> _Animation = nullptr;
	switch (_Type)
	{
	case 1:
		FireWorkRenderer->CreateAnimation("FireWork", "FireWork" + std::to_string(_Type), 0.12f);
		_Animation = FireWorkRenderer->FindAnimation("FireWork");
		_Animation->Inter[15] = 3.0f;
		break;
	case 2:
		FireWorkRenderer->CreateAnimation("FireWork", "FireWork" + std::to_string(_Type), 0.1f);
		_Animation = FireWorkRenderer->FindAnimation("FireWork");
		_Animation->Inter[15] = 3.0f;
		break;
	case 3:
		FireWorkRenderer->CreateAnimation("FireWork", "FireWork" + std::to_string(_Type), 0.18f);
		_Animation = FireWorkRenderer->FindAnimation("FireWork");
		_Animation->Inter[16] = 3.0f;
		break;
	case 4:
		FireWorkRenderer->CreateAnimation("FireWork", "FireWork" + std::to_string(_Type), 0.18f);
		_Animation = FireWorkRenderer->FindAnimation("FireWork");
		_Animation->Inter[16] = 2.6f;
		break;
	case 5:
		FireWorkRenderer->CreateAnimation("FireWork", "FireWork" + std::to_string(_Type));
		_Animation = FireWorkRenderer->FindAnimation("FireWork");
		_Animation->Inter[11] = 1.5f;
		break;
	default:
		break;
	}
	FireWorkRenderer->ChangeAnimation("FireWork");
}
