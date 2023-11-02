#pragma once

class ContentButton : public GameEngineActor
{
public:
	// constructer destructer
	ContentButton();
	~ContentButton();

	// delete function
	ContentButton(const ContentButton& _Ohter) = delete;
	ContentButton(ContentButton&& _Ohter) noexcept = delete;
	ContentButton& operator=(const ContentButton& _Other) = delete;
	ContentButton& operator=(ContentButton&& _Other) noexcept = delete;

	void Init(std::string_view _ButtonTextureName);

	void SetButtonClickEvent(std::function<void()> _Function);
	void SetButtonClickEndEvent(std::function<void()> _Function);
	void SetButtonStayEvent(std::function<void()> _Function);

protected:
	std::shared_ptr<GameEngineUIRenderer> ButtonRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> ButtonCollision = nullptr;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	bool IsClick = false;
	std::function<void()> ButtonClickEvent;
	std::function<void()> ButtonClickEndEvent;
	std::function<void()> ButtonStayEvent;
};

