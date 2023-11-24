#include "PreCompile.h"
#include "DamageSkinRenderer.h"

DamageSkinRenderer::DamageSkinRenderer()
{
}

DamageSkinRenderer::~DamageSkinRenderer()
{
}

void DamageSkinRenderer::SetImageScale(const float4& _Scale)
{
	ImageTransform.SetLocalScale(_Scale);
}

void DamageSkinRenderer::AddImageScale(const float4& _Scale)
{
	ImageTransform.AddLocalScale(_Scale);
}

void DamageSkinRenderer::Start()
{
	GameEngineRenderer::Start();
	// DataTransform�� ImageTransform�� �־���
	// DataTransform = &ImageTransform;
	// �θ�δ� ��(����)�� Transform�� �־������μ� ������ Transform�� Renderer�� Transform�� �и���

	ImageTransform.SetParent(Transform);
	GameEngineRenderer::SetMesh("Rect");
	GameEngineRenderer::SetMaterial("DamageSkinTexture");
}

void DamageSkinRenderer::Update(float _Delta)
{
	// Set TransformData's LocalScale at ImageSize
	//if (true == IsImageSize)
	//{
	//	float4 Scale = float4(CurSprite.GetScale());
	//	Scale.Z = 1.0f;
	//	Scale.W = 0.0f;
	//	SetImageScale(Scale * AutoScaleRatio);
	//}

	//RenderBaseInfoValue.RenderScreenScale = CurSprite.GetScale();

	Transform.AddLocalPosition({0, UpSpeed * _Delta});
	if (0.0 < AlphaDelay)
	{
		AlphaDelay -= _Delta;
		return;
	}
	
	ColorDataValue.MulColor.A -= _Delta;

	if (0.0f >= ColorDataValue.MulColor.A)
	{
		Death();
	}
}

void DamageSkinRenderer::SetSprite(std::string_view _Name, unsigned int Index /*= 0*/)
{
	Sprite = GameEngineSprite::Find(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("�������� �ʴ� ��������Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}

	CurSprite = Sprite->GetSpriteData(Index);
	// SetImageScale(CurSprite.GetScale());
}

void DamageSkinRenderer::Render(GameEngineCamera* _Camera, float _Delta)
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

	GetShaderResHelper().SetTexture("DamageSkinTex", CurSprite.Texture, true);
	GameEngineRenderer::Render(_Camera, _Delta);
}

void DamageSkinRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
{
	// ���� ImageTransform�� ConstantBuufer�� ��������
	const TransformData& Data = ImageTransform.GetConstTransformDataRef();
	GetShaderResHelper().SetConstantBufferLink("TransformData", Data);
	GetShaderResHelper().SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	// GetShaderResHelper().SetConstantBufferLink("SpriteData", CurSprite.SpritePivot);
	GetShaderResHelper().SetConstantBufferLink("ColorData", ColorDataValue);
	GetShaderResHelper().SetConstantBufferLink("UVInfo", UVValues);
	SetSprite("DamageSkin_Num_Merge.png");
}

void DamageSkinRenderer::SetDamage(int _Damage)
{
	std::string _DamageString = std::to_string(_Damage);
	if (9 <= _DamageString.length())
	{
		MsgBoxAssert("������ �ִ��ڸ����� �ʰ��߽��ϴ�.");
	}

	std::shared_ptr<GameEngineTexture> _Texture = GameEngineTexture::Find("DamageSkin_Num_Merge.png");
	float4 _TextureScale = _Texture->GetScale();

	std::vector<float> Skin;
	Skin.reserve(10);
	Skin = {51.0f, 43.0f, 43.0f, 53.0f, 47.0f, 32.0f, 40.0f, 44.0f, 53.0f, 58.0f};
	float4 DamageSkinScale = {0.0f, _TextureScale.Y, 0.0f, 0.0f};

	for (size_t i = 0; i < _DamageString.length(); i++)
	{
		int _Index = int(_DamageString[i]) - 48;
		DamageSkinScale.X += Skin[_Index];
	}

	SetImageScale(DamageSkinScale);
	UVValues.Ratio = DamageSkinScale.X / _TextureScale.X;
	float StartUv = 0.0f;
	for (size_t i = 0; i < _DamageString.length(); i++)
	{
		int _Index = int(_DamageString[i]) - 48;
		UVValues.RendererUV[i] = StartUv + Skin[_Index] / DamageSkinScale.X;
		UVValues.TextureUV[i] = CalcuTextureUV(Skin, _Index, _TextureScale.X);
		StartUv = UVValues.RendererUV[i];
	}
}

float DamageSkinRenderer::CalcuTextureUV(std::vector<float> _SkinSizeVector, int _Index, float _SkinWholeSize /*= 0.0f*/)
{
	if (_Index >= _SkinSizeVector.size())
	{
		MsgBoxAssert("Index���� �߸��Ǿ����ϴ�.");
	}

	float WholeSkinSize = _SkinWholeSize;
	if (0.0f == WholeSkinSize)
	{
		for (size_t i = 0; i < _SkinSizeVector.size(); i++)
		{
			WholeSkinSize += _SkinSizeVector[i];
		}
	}
	
	float IndexStartUv = 0.0f;
	for (size_t i = 0; i < _Index; i++)
	{
		IndexStartUv += _SkinSizeVector[i];
	}

	return (IndexStartUv / WholeSkinSize);
}