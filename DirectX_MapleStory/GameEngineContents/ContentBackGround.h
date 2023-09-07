#pragma once
#include <GameEngineCore\GameEngineActor.h>

class ContentBackGround : public GameEngineActor
{
public:
	// constructer destructer
	ContentBackGround();
	~ContentBackGround();

	// delete function
	ContentBackGround(const ContentBackGround& _Ohter) = delete;
	ContentBackGround(ContentBackGround&& _Ohter) noexcept = delete;
	ContentBackGround& operator=(const ContentBackGround& _Other) = delete;
	ContentBackGround& operator=(ContentBackGround&& _Other) noexcept = delete;

	void Init(std::string_view _BackGroundName, const float4& _BackGroundScale = float4::ZERO);

	inline float4 GetBackScale()
	{
		return BackScale;
	}

protected:
	void Start() override;
	void Update(float _Delta);

private:
	float4 BackScale = float4::ZERO;
	std::shared_ptr<GameEngineSpriteRenderer> BackGroundRenderer = nullptr;
};

