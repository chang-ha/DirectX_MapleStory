#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineConstantBuffer.h"

std::shared_ptr<GameEngineSampler> GameEngineSpriteRenderer::DefaultSampler;

void GameEngineFrameAnimation::Reset()
{
	CurTime = 0.0f;
	CurIndex = 0;
	IsEnd = false;
	EventCheck = true;
}

void GameEngineFrameAnimation::EventCall(int _Frame)
{
	if (true == FrameEventFunction.contains(Index[_Frame]))
	{
		FrameEventFunction[Index[_Frame]](Parent);
	}
}

SpriteData GameEngineFrameAnimation::Update(float _Delta)
{
	if (true == Parent->IsPause)
	{
		return Sprite->GetSpriteData(Index[CurIndex]);
	}

	if (true == Loop)
	{
		IsEnd = false;
	}

	if (true == EventCheck && false == IsEnd)
	{
		EventCall(CurIndex);
		EventCheck = false;
	}

	CurTime += _Delta;
	if (Inter <= CurTime)
	{
		++CurIndex;
		EventCheck = true;
		CurTime -= Inter;
		if (CurIndex > End - Start)
		{
			if (nullptr != EndEvent && false == IsEnd)
			{
				EndEvent(Parent);
			}

			IsEnd = true;

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
	if (nullptr == DefaultSampler)
	{
		MsgBoxAssert("SpriteRenderer�� ������ �⺻ ���÷��� �����ϴ�.");
	}

	Sampler = DefaultSampler;
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}

void GameEngineSpriteRenderer::SetPivotType(PivotType _Type)
{
	switch (_Type)
	{
	case PivotType::Center:
		Pivot = { 0.5f, 0.5f };
		break;
	case PivotType::Bottom:
		Pivot = { 0.5f, 1.0f };
		break;
	case PivotType::Left:
		Pivot = { 1.0f, 0.5f };
		break;
	default:
		break;
	}
}

void GameEngineSpriteRenderer::SetImageScale(const float4& _Scale)
{
	ImageTransform.SetLocalScale(_Scale);
}

void GameEngineSpriteRenderer::AddImageScale(const float4& _Scale)
{
	ImageTransform.AddLocalScale(_Scale);
}

void GameEngineSpriteRenderer::SetDefaultSampler(std::string_view _SamplerName)
{
	DefaultSampler = GameEngineSampler::Find(_SamplerName);
}

void GameEngineSpriteRenderer::Start()
{
	GameEngineRenderer::Start();
	// DataTransform�� ImageTransform�� �־���
	DataTransform = &ImageTransform;
	// �θ�δ� ��(����)�� Transform�� �־������μ� ������ Transform�� Renderer�� Transform�� �и���
	ImageTransform.SetParent(Transform);
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
		SetImageScale(Scale * AutoScaleRatio);
	}
}

void GameEngineSpriteRenderer::SetSprite(std::string_view _Name, unsigned int Index /*= 0*/)
{
	Sprite = GameEngineSprite::Find(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("�������� �ʴ� ��������Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}

	CurSprite = Sprite->GetSpriteData(Index);
	SetImageScale(CurSprite.GetScale());
}

void GameEngineSpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, float _Inter /*= 0.1f*/, unsigned int _Start /*= -1*/, unsigned int _End /*= -1*/, bool _Loop /*= true*/)
{
	std::string SpriteName = GameEngineString::ToUpperReturn(_SpriteName);
	std::shared_ptr<GameEngineSprite> Sprite = GameEngineSprite::Find(SpriteName);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("�������� �ʴ� ��������Ʈ�� �ִϸ��̼��� ������� �߽��ϴ�.");
		return;
	}

	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);
	if (true == FrameAnimations.contains(UpperName))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� �� ������� �߽��ϴ�.");
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
	NewAnimation->Parent = this;

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

void GameEngineSpriteRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/, unsigned int _FrameIndex /*= 0*/)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);
	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	if (FrameAnimations.end() == FindIter)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� ü�����Ϸ��� �߽��ϴ�.");
		return;
	}
	
	if (false == _Force && FindIter->second == CurFrameAnimations)
	{
		return;
	}

	CurFrameAnimations = FrameAnimations[UpperName];
	CurFrameAnimations->Reset();
	CurFrameAnimations->CurIndex = _FrameIndex;
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
	float4 ParentScale = Transform.GetLocalScale();
	float4 ImageScale = ImageTransform.GetLocalScale();
	float4 CalPivot = Pivot;
	CalPivot.X -= 0.5f;
	CalPivot.Y -= 0.5f;

	float4 PivotPos;
	PivotPos.X = ImageScale.X * CalPivot.X;
	PivotPos.Y = ImageScale.Y * CalPivot.Y;

	ImageTransform.SetLocalPosition(PivotPos);
	ImageTransform.TransformUpdate();
	ImageTransform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());

	GameEngineRenderer::ResSetting();

	std::shared_ptr<GameEngineConstantBuffer> ConstantBuffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData", ShaderType::Vertex, 1);
	if (nullptr != ConstantBuffer)
	{
		ConstantBuffer->ChangeData(CurSprite.SpritePivot);
		ConstantBuffer->Setting(1);
	}

	CurSprite.Texture->PSSetting(0);

	if (nullptr == Sampler)
	{
		MsgBoxAssert("�������� �ʴ� �ؽ�ó�� ����Ϸ��� �߽��ϴ�.");
	}
	Sampler->PSSetting(0);
	GameEngineRenderer::Draw();
}

void GameEngineSpriteRenderer::SetSamplerState(SamplerOption _Option)
{
	switch (_Option)
	{
	case SamplerOption::LINEAR:
		Sampler = GameEngineSampler::Find("LINEAR");
		break;
	case SamplerOption::POINT:
		Sampler = GameEngineSampler::Find("POINT");
		break;
	default:
		break;
	}
}

void GameEngineSpriteRenderer::SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameEngineSpriteRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	std::shared_ptr<GameEngineFrameAnimation> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->FrameEventFunction[_Frame] = _Function;
}

void GameEngineSpriteRenderer::SetStartEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	std::shared_ptr<GameEngineFrameAnimation> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->FrameEventFunction[0] = _Function;
}

void GameEngineSpriteRenderer::SetEndEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_AnimationName);

	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>>::iterator FindIter = FrameAnimations.find(UpperName);

	std::shared_ptr<GameEngineFrameAnimation> Animation = FindIter->second;

	if (nullptr == Animation)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼ǿ� �̺�Ʈ�� ������� �߽��ϴ�.");
	}

	Animation->EndEvent = _Function;
}

void GameEngineSpriteRenderer::AnimationPauseSwitch()
{
	IsPause = !IsPause;
}

void GameEngineSpriteRenderer::AnimationPauseOn()
{
	IsPause = true;
}

void GameEngineSpriteRenderer::AnimationPauseOff()
{
	IsPause = false;
}