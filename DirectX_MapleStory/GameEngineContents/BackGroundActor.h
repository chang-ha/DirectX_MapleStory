#pragma once

// struct BackGroundInfo
// {
// 	float StartRatioX = 1.0f;
// 	float EndRatioX = 1.0f;
// 	float StartRatioY = 1.0f;
// 	float EndRatioY = 1.0f;
// };

class BackGroundActor : public GameEngineActor
{
public:
	// constructer destructer
	BackGroundActor();
	~BackGroundActor();

	// delete function
	BackGroundActor(const BackGroundActor& _Ohter) = delete;
	BackGroundActor(BackGroundActor&& _Ohter) noexcept = delete;
	BackGroundActor& operator=(const BackGroundActor& _Other) = delete;
	BackGroundActor& operator=(BackGroundActor&& _Other) noexcept = delete;

	void Init(std::string_view _BackGroundName, int LoopNumber_X, float BackGroundScale_X, float OverLapRatio_X);

	//BackGroundInfo& GetBackGroundInfo()
	//{
	//	return InfoValue;
	//}

	//void SetBackGroundScale(const float4& _Scale)
	//{
	//	BackGroundRenderer->SetImageScale(_Scale);
	//}

	//void SetImageLoopNumber(float _X, float _Y = 1.0f)
	//{
	//	BackGroundRenderer->RenderBaseInfoValue.VertexUVMul.X = _X;
	//	BackGroundRenderer->RenderBaseInfoValue.VertexUVMul.Y = _Y;
	//}

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::string BackGroundName = "";
	// BackGroundInfo InfoValue;
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>> BackGroundRenderers;
};

