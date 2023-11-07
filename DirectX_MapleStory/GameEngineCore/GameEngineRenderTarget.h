#pragma once
#include "GameEngineTexture.h"
#include "GameEngineRenderer.h"

#define MAX_RENDER_TARGET_SETTING_COUNT 8

class Effect : public GameEngineObjectBase
{
	friend class GameEngineRenderTarget;

public:
	RenderBaseInfo RenderBaseInfoValue;

	// ȿ���� �ذ��� ���� Ÿ��
	GameEngineRenderUnit EffectUnit;

	GameEngineRenderTarget* EffectTarget = nullptr;
	std::shared_ptr<GameEngineRenderTarget> ResultTarget = nullptr;

public:
	virtual void Start() = 0;
	virtual void EffectProcess(float _DeltaTime) = 0;
};

// ���� :
class GameEngineRenderTarget : public GameEngineResources<GameEngineRenderTarget>
{
public:
	friend class GameEngineCoreWindow;
	friend GameEngineDevice;
	static bool IsDepth;
	static void RenderTargetReset();

	// constrcuter destructer
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	// delete Function
	GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineRenderTarget> Create(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color = float4::BLUE)
	{
		std::shared_ptr<GameEngineRenderTarget> NewRes = GameEngineResources::CreateRes();
		NewRes->AddNewTexture(_Texture, _Color);
		return NewRes;
	}

	static std::shared_ptr<GameEngineRenderTarget> Create()
	{
		std::shared_ptr<GameEngineRenderTarget> NewRes = GameEngineResources::CreateRes();
		return NewRes;
	}

	inline std::shared_ptr<GameEngineTexture> GetTexture(int _Index = 0)
	{
		return Textures[_Index];
	}

	void Clear();
	void Setting();

	void SetClearColor(const float4& _Color, int _Index = 0)
	{
		ClearColor[_Index] = _Color;
	}

	void CreateDepthTexture(int _Index = 0);

	void AddNewTexture(DXGI_FORMAT _Format, const float4& _Scale, const float4& _ClearColor);

	void AddNewTexture(std::shared_ptr<GameEngineTexture> _Texture, const float4& _ClearColor);

	void Copy(unsigned int ThisTarget, std::shared_ptr<GameEngineRenderTarget> _Target, unsigned int _CopyTarget = 0);

	void Merge(unsigned int ThisTarget, std::shared_ptr<GameEngineRenderTarget> _Target, unsigned int _CopyTarget = 0);

	void PostEffect(float _DeltaTime);

	void EffectInit(Effect* _Effect);

	template<typename EffectType>
	std::shared_ptr<EffectType> CreateEffect()
	{
		std::shared_ptr<EffectType> NewEffect = std::make_shared<EffectType>();
		EffectInit(NewEffect.get());

		Effects.push_back(NewEffect);
		return NewEffect;
	}

	std::shared_ptr<GameEngineRenderTarget> CreateChildRenderTarget(std::vector<int> _Index);

protected:

private:
	static GameEngineRenderUnit MergeUnit;
	static void MergeRenderUnitInit();

	std::vector<std::shared_ptr<GameEngineTexture>> Textures;
	std::vector<ID3D11RenderTargetView*> RTV; // <= �ؽ�ó�� ����Ÿ������ ������ �ְ� ����� ����
	std::vector<ID3D11ShaderResourceView*> SRV; // <= �ؽ�ó�� ���ҽ��� ����Ҽ� �ִ� ����
	std::vector<float4> ClearColor; // <= �ؽ�ó�� ����Ÿ������ ������ �ְ� ����� ����
	std::vector<D3D11_VIEWPORT> ViewPorts;

	std::shared_ptr<GameEngineTexture> DepthTexture;

	std::list<std::shared_ptr<Effect>> Effects;
};