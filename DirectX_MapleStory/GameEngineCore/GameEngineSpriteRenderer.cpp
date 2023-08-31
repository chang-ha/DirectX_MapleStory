#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineConstantBuffer.h"

void GameEngineFrameAnimation::Reset()
{
	CurTime = 0.0f;
	CurIndex = 0;
}

SpriteData GameEngineFrameAnimation::Update(float _Delta)
{
	CurTime += _Delta;
	if (Inter <= CurTime)
	{
		++CurIndex;
		CurTime -= Inter;
		if (CurIndex > End - Start)
		{
			if (true == Loop)
			{
				CurIndex = 0;
			}
			else
			{
				--CurIndex;
			}
		}
	}

	return Sprite->GetSpriteData(Index[CurIndex]);
}

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}

void GameEngineSpriteRenderer::Update(float _Delta)
{
	if (nullptr != CurFrameAnimations)
	{
		CurSprite = CurFrameAnimations->Update(_Delta);
	}

	// Set TransformData's LocalScale at ImageSize
	if (true == IsImageSize)
	{
		float4 Scale = float4(CurSprite.GetScale());
		Scale.Z = 1.0f;
		Scale.W = 0.0f;
		Transform.SetLocalScale(Scale * AutoScaleRatio);
	}
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

void GameEngineSpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, float _Inter /*= 0.1f*/, unsigned int _Start /*= -1*/, unsigned int _End /*= -1*/, bool _Loop /*= true*/)
{
	std::string SpriteName = GameEngineString::ToUpperReturn(_SpriteName);
	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find(SpriteName);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트로 애니메이션을 만들려고 했습니다.");
		return;
	}

	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);
	if (true == FrameAnimations.contains(UpperName))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만들려고 했습니다.");
		return;
	}

	std::shared_ptr<GameEngineFrameAnimation> NewAnimation = std::make_shared<GameEngineFrameAnimation>();
	FrameAnimations[UpperName] = NewAnimation;
	NewAnimation->AnimationName = _AnimationName;
	NewAnimation->SpriteName = _SpriteName;
	NewAnimation->Sprite = Sprite;
	NewAnimation->Loop = _Loop;
	NewAnimation->Inter = _Inter;
	NewAnimation->CurIndex = 0;

	// if (Start || End is -1) == Use All Sprite Image
	if (_Start != -1)
	{
		NewAnimation->Start = _Start;
	}
	else
	{
		NewAnimation->Start = 0;
	}

	if (_End != -1)
	{
		NewAnimation->End = _End;
	}
	else
	{
		NewAnimation->End = Sprite->GetSpriteCount() - 1;
	}
	
	// Save Animation Index to Vector
	// if use Sprite Image 3 to 5 = save 3 4 5 to vector
	for (unsigned int i = NewAnimation->Start; i <= NewAnimation->End; i++)
	{
		NewAnimation->Index.push_back(i);
	}
}

void GameEngineSpriteRenderer::ChangeAnimation(std::string_view _AnimationName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
		return;
	}
	
	CurFrameAnimations = FrameAnimations[UpperName];
}

void GameEngineSpriteRenderer::AutoSpriteSizeOn()
{
	IsImageSize = true;
}

void GameEngineSpriteRenderer::AutoSpriteSizeOff()
{
	IsImageSize = false;
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
