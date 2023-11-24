#pragma once

struct UVInfo
{
	float Ratio = 0;
	float UVTemp1 = 0;
	float UVTemp2 = 0;
	float UVTemp3 = 0;

	float RendererUV[8] = {};
	float TextureUV[8] = {};
};

// Ό³Έν :
class DamageSkinRenderer : public GameEngineRenderer
{
	friend class GameEngineFrameAnimation;
public:
	// constrcuter destructer
	DamageSkinRenderer();
	~DamageSkinRenderer();

	// delete Function
	DamageSkinRenderer(const DamageSkinRenderer& _Other) = delete;
	DamageSkinRenderer(DamageSkinRenderer&& _Other) noexcept = delete;
	DamageSkinRenderer& operator=(const DamageSkinRenderer& _Other) = delete;
	DamageSkinRenderer& operator=(DamageSkinRenderer&& _Other) noexcept = delete;

	void SetSprite(std::string_view _Name, unsigned int Index = 0);

	void SetPivotValue(const float4& _Value)
	{
		Pivot = _Value;
	}

	//float4 GetPivotValue()
	//{
	//	return Pivot;
	//}

	/// <summary>
	/// Damage Maxdigit = 8
	/// </summary>
	/// <param name="_Damage"></param>
	void SetDamage(int _Damage);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;
	void SetMaterialEvent(std::string_view _Name, int _Index) override;

private:
	std::shared_ptr<GameEngineSprite> Sprite;
	std::shared_ptr<class GameEngineSampler> Sampler;
	SpriteData CurSprite;
	UVInfo UVValues;

	/////////// Animation Member
	float4 Pivot = { 0.5f, 0.5f };
	GameEngineTransform ImageTransform;
	ColorData ColorDataValue;

	void SetImageScale(const float4& _Scale);
	void AddImageScale(const float4& _Scale);

	float CalcuTextureUV(std::vector<float> _SkinSizeVector, int _Index, float _SkinWholeSize = 0.0f);
};

