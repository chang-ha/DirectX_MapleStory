#pragma once

class OneButtonWarningMentStruct : public std::enable_shared_from_this<OneButtonWarningMentStruct>
{
	friend class ButtonWarningMent;
public:
	GameEngineActor* GetParent()
	{
		return Parent;
	}

protected:
	GameEngineActor* Parent;
	std::shared_ptr<GameEngineSpriteRenderer> MentBG = nullptr;
	std::shared_ptr<class ContentButton> CancelButton = nullptr;

	virtual void StructStart(GameEngineActor* _Parent);
};


class TwoButtonWarningMentStruct : public OneButtonWarningMentStruct
{
	friend class ButtonWarningMent;

	std::shared_ptr<class ContentButton> OkButton = nullptr;

	void StructStart(GameEngineActor* _Parent) override;
};


class ButtonWarningMent : public GameEngineActor
{
public:
	// constructer destructer
	ButtonWarningMent();
	~ButtonWarningMent();

	// delete function
	ButtonWarningMent(const ButtonWarningMent& _Ohter) = delete;
	ButtonWarningMent(ButtonWarningMent&& _Ohter) noexcept = delete;
	ButtonWarningMent& operator=(const ButtonWarningMent& _Other) = delete;
	ButtonWarningMent& operator=(ButtonWarningMent&& _Other) noexcept = delete;

	static std::shared_ptr<ButtonWarningMent> CreateOneButtonMent();
	static std::shared_ptr<ButtonWarningMent> CreateTwoButtonMent();

	std::shared_ptr<OneButtonWarningMentStruct> MentObject;

protected:

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	
};

