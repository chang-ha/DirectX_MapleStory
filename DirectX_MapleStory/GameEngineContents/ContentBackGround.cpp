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
		BackGroundRenderer = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BACKGROUND);
		BackGroundRenderer->Transform.SetLocalPosition({ 0, 0, RenderDepth::background });
	}
}

void ContentBackGround::Update(float _Delta)
{
	if (true == GetLevel()->GetMainCamera()->IsFreeCamera())
	{
		BackGroundRenderer->Off();
	}
	else
	{
		BackGroundRenderer->On();
	}
	Transform.SetLocalPosition(GetLevel()->GetMainCamera()->Transform.GetWorldPosition());
}

void ContentBackGround::Release()
{
	if (nullptr != BackGroundRenderer)
	{
		BackGroundRenderer->Death();
		BackGroundRenderer = nullptr;
	}

	if (nullptr != GameEngineSprite::Find(BackGroundName))
	{
		GameEngineTexture::Release(BackGroundName);
		GameEngineSprite::Release(BackGroundName);
	}
}

void ContentBackGround::Init(std::string_view _BackGroundName, const float4& _BackGroundScale)
{
	BackGroundName = _BackGroundName;
	if (nullptr == GameEngineTexture::Find(BackGroundName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResources");
		FilePath.MoveChild("ContentResources\\Textures\\BackGround\\");
		GameEngineTexture::Load(FilePath.GetStringPath() + std::string(BackGroundName.data()));
		GameEngineSprite::CreateSingle(BackGroundName);
	}
	std::shared_ptr<GameEngineTexture> BackGroundTexture = GameEngineTexture::Find(std::string(BackGroundName.data()));
	BackGroundRenderer->SetSprite(BackGroundName);
	
	if (float4::ZERO != _BackGroundScale)
	{
		BackScale = _BackGroundScale;
	}
	else
	{
		BackScale = BackGroundTexture->GetScale();
	}
	BackGroundRenderer->SetImageScale(BackScale);
}