#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineConstantBuffer.h"

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}

void GameEngineSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	GameEngineRenderer::ResSetting();

	std::shared_ptr<GameEngineConstantBuffer> ConstantBuffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData", ShaderType::Vertex, 1);
	if (nullptr != ConstantBuffer)
	{
		ConstantBuffer->ChangeData(CurSprite.SpritePivot);
		ConstantBuffer->Setting(1);
	}

	CurSprite.Texture->PSSetting(0);

	std::shared_ptr<GameEngineSampler> Sampler = GameEngineSampler::Find("EngineBaseSampler");
	if (nullptr == Sampler)
	{
		MsgBoxAssert("존재하지 않는 텍스처를 사용하려고 했습니다.");
	}
	Sampler->PSSetting(0);
	GameEngineRenderer::Draw();
}

void GameEngineSpriteRenderer::SetSprite(std::string_view _Name, unsigned int Index /*= 0*/)
{
	Sprite = GameEngineSprite::Find(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
	}

	CurSprite = Sprite->GetSpriteData(Index);
	Transform.SetLocalScale(CurSprite.GetScale());
}