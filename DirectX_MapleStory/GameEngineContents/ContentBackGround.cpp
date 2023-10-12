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
	if (nullptr == BackGroundRenderer)
	{
		BackGroundRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BackGround);
	}
}

void ContentBackGround::Update(float _Delta)
{

}

void ContentBackGround::Release()
{
	if (nullptr != BackGroundRenderer)
	{
		BackGroundRenderer->Death();
		BackGroundRenderer = nullptr;
	}
}

void ContentBackGround::Init(std::string_view _BackGroundName, const float4& _BackGroundScale)
{
	if (nullptr == GameEngineTexture::Find(_BackGroundName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Textures\\BackGround\\");
		GameEngineTexture::Load(FilePath.GetStringPath() + std::string(_BackGroundName.data()));
		GameEngineSprite::CreateSingle(_BackGroundName);
	}
	std::shared_ptr<GameEngineTexture> BackGroundTexture = GameEngineTexture::Find(std::string(_BackGroundName.data()));
	BackGroundRenderer->SetSprite(_BackGroundName);
	
	if (float4::ZERO != _BackGroundScale)
	{
		BackScale = _BackGroundScale;
	}
	else
	{
		BackScale = BackGroundTexture->GetScale();
	}
	BackGroundRenderer->SetImageScale(BackScale);

	float4 HalfBackScale = BackScale.Half();
	HalfBackScale.Y *= -1.0f;
	Transform.SetLocalPosition(HalfBackScale);
}