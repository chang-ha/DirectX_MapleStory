#pragma once

class RenderActor : public GameEngineActor
{
public:
	// constructer destructer
	RenderActor();
	~RenderActor();

	// delete function
	RenderActor(const RenderActor& _Ohter) = delete;
	RenderActor(RenderActor&& _Ohter) noexcept = delete;
	RenderActor& operator=(const RenderActor& _Other) = delete;
	RenderActor& operator=(RenderActor&& _Other) noexcept = delete;

	template <typename EnumType>
	void Init(EnumType _Order)
	{
		Init(static_cast<int>(_Order));
	}

	void Init(int _Order);
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
};

