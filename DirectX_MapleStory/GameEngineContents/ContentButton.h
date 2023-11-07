#pragma once

enum class ButtonState
{
	Normal,
	MouseOver,
	Click,
	Disabled
};

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
	void ChangeState(ButtonState _State);
	void StateUpdate(float _Delta);

	void SetButtonClickEvent(std::function<void()> _Function);
	void SetButtonClickEndEvent(std::function<void()> _Function);
	void SetButtonStayEvent(std::function<void()> _Function);

	float4 GetButtonScale()
	{
		return ButtonScale;
	}

	void SetButtonCollisionScale(const float4& _Scale)
	{
		ButtonCollision->Transform.SetLocalScale(_Scale);
	}

	std::shared_ptr<GameEngineUIRenderer> GetButtonRenderer()
	{
		return ButtonRenderer;
	}

	void CollisionOff()
	{
		ButtonCollision->Off();
	}

	void CollisionOn()
	{
		ButtonCollision->On();
	}

protected:
	std::shared_ptr<GameEngineUIRenderer> ButtonRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> ButtonCollision = nullptr;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	ButtonState State = ButtonState::Normal;
	float4 ButtonScale = float4::ZERO;
	std::string ButtonName = "";
	std::function<void()> ButtonClickEvent;
	std::function<void()> ButtonClickEndEvent;
	std::function<void()> ButtonStayEvent;

	void NormalStart();
	void MouseOverStart();
	void ClickStart();
	void DisabledStart();

	void NormalUpdate(float _Delta);
	void MouseOverUpdate(float _Delta);
	void ClickUpdate(float _Delta);
	void DisabledUpdate(float _Delta);

	void NormalEnd();
	void MouseOverEnd();
	void ClickEnd();
	void DisabledEnd();
};

