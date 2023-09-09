#include "PreCompile.h"
#include "ContentBackGround.h"

ContentBackGround::ContentBackGround()
{
	
}

ContentBackGround::~ContentBackGround()
{

}

void ContentBackGround::Start()
{
	BackGroundRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BackGround);
}

void ContentBackGround::Update(float _Delta)
{

}

void ContentBackGround::Init(std::string_view _BackGroundName, const float4& _BackGroundScale)
{
	if (nullptr == GameEngineTexture::Find(_BackGroundName))
	{
		GameEnginePath Path;
		Path.SetCurrentPath();
		Path.MoveParentToExistsChild("ContentResources");
		Path.MoveChild("ContentResources\\Textures\\BackGround\\");
		GameEngineTexture::Load(Path.GetStringPath() + std::string(_BackGroundName.data()));
		GameEngineSprite::CreateSingle(_BackGroundName);
	}
	std::shared_ptr<GameEngineTexture> BackGroundTexture = GameEngineTexture::Find(std::string(_BackGroundName.data()));
	BackGroundRenderer->SetSprite(_BackGroundName);
	
	if (float4::ZERO != _BackGroundScale)
	{
		BackScale = _BackGroundScale;
		BackGroundRenderer->SetImageScale(_BackGroundScale);
	}
	else
	{
		BackScale = BackGroundTexture->GetScale();
	}

	float4 HalfBackScale = BackScale.Half();
	HalfBackScale.Y *= -1.0f;
	this->Transform.SetLocalPosition(HalfBackScale);
}