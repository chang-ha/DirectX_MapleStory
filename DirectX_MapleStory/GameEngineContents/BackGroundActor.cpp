#include "PreCompile.h"
#include "BackGroundActor.h"

BackGroundActor::BackGroundActor()
{

}

BackGroundActor::~BackGroundActor()
{

}

void BackGroundActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void BackGroundActor::Start()
{
	//BackGroundRenderer->SetMaterial("BackGroundActor");
	//BackGroundRenderer->SetSampler("EngineBaseWRAPSampler");

	//BackGroundRenderer->GetShaderResHelper().SetConstantBufferLink("BackGroundInfo", InfoValue);
}

void BackGroundActor::Update(float _Delta)
{
	
}

void BackGroundActor::Release()
{
	for (size_t i = 0; i < BackGroundRenderers.size(); i++)
	{
		if (nullptr != BackGroundRenderers[i])
		{
			BackGroundRenderers[i]->Death();
			BackGroundRenderers[i] = nullptr;
		}
	}
}

void BackGroundActor::Init(std::string_view _BackGroundName, int LoopNumber_X, float BackGroundScale_X, float OverLapRatio_X)
{
	BackGroundName = _BackGroundName;
	BackGroundRenderers.resize(LoopNumber_X);
	if (nullptr == GameEngineSprite::Find(BackGroundName))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\BackGround\\" + BackGroundName);
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(BackGroundName);
	}

	std::shared_ptr<GameEngineTexture> _Texture = GameEngineTexture::Find(BackGroundName);
	float4 TextureScale = _Texture->GetScale();

	for (size_t i = 0; i < BackGroundRenderers.size(); i++)
	{
		if (nullptr == BackGroundRenderers[i])
		{
			BackGroundRenderers[i] = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::BACKGROUND);
			BackGroundRenderers[i]->Transform.SetLocalPosition({ TextureScale.X * OverLapRatio_X * i, 0, RenderDepth::background });
		}
		BackGroundRenderers[i]->AutoSpriteSizeOn();
		BackGroundRenderers[i]->SetPivotType(PivotType::Left);
		BackGroundRenderers[i]->SetSprite(BackGroundName);
	}
}
