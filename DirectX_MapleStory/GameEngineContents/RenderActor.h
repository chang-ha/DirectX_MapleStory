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

	void Init(std::string_view _Path);

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

protected:
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;

private:
};

