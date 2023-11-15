#pragma once

enum class MouseState
{
	Normal,
};

class ContentMouse : public GameEngineActor
{
public:
	static ContentMouse* MainMouse;
	// constructer destructer
	ContentMouse();
	~ContentMouse();

	// delete function
	ContentMouse(const ContentMouse& _Ohter) = delete;
	ContentMouse(ContentMouse&& _Ohter) noexcept = delete;
	ContentMouse& operator=(const ContentMouse& _Other) = delete;
	ContentMouse& operator=(ContentMouse&& _Other) noexcept = delete;

	void NormalMouse();
	void ButtonAniMouse();

protected:
	bool IsButtonAni = false;
	MouseState State = MouseState::Normal;
	std::shared_ptr<GameEngineUIRenderer> MouseRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> MouseCollision = nullptr;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:

};

