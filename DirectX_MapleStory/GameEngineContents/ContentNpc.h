#pragma once

#define MENT_SPEED 0.05f

enum class MentType
{
	OneButton,
	TwoButton
};

class OneButtonNpcMentFrame : public GameEngineActor
{
	friend class ContentNpc;

protected:
	bool MentEnd = false;
	float MentSpeed = MENT_SPEED;
	size_t MentIndex = 0;
	size_t MentMaxIndex = -1;
	std::wstring Ment = L"";
	ContentNpc* Parent = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MentBG = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MentNpc = nullptr;
	std::shared_ptr<GameEngineUIRenderer> NpcName = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MentText = nullptr;
	std::shared_ptr<class ContentButton> CancelButton = nullptr;

	void StructStart(class ContentNpc* _Parent, std::string_view _NpcName, std::string_view _CancelButtonName);
	void MentOff();
	void MentUpdate(float _Delta);
	void SkipUpdate(float _Delta);
	void Update(float _Delta) override;
};

class TwoButtonNpcMentFrame : public OneButtonNpcMentFrame
{
	friend class ContentNpc;

	std::shared_ptr<class ContentButton> OkButton = nullptr;
	void StructStart(class ContentNpc* _Parent, std::string_view _NpcName, std::string_view _CancelButtonName, std::string_view _OkButtonName, std::function<void()> _OkButtonEndFunction = nullptr);
};

class ContentNpc : public GameEngineActor
{
public:
	// constructer destructer
	ContentNpc();
	~ContentNpc();

	// delete function
	ContentNpc(const ContentNpc& _Ohter) = delete;
	ContentNpc(ContentNpc&& _Ohter) noexcept = delete;
	ContentNpc& operator=(const ContentNpc& _Other) = delete;
	ContentNpc& operator=(ContentNpc&& _Other) noexcept = delete;

	std::string GetNpcName()
	{
		return NpcName;
	}

	void Init(std::string_view _NpcName, std::string_view _KoreanName, ActorDir _Dir = ActorDir::Left, float _AniSpeed = 0.1f);

	void SetMentText(std::wstring_view _Ment)
	{
		Ment->Ment = _Ment;
		Ment->MentMaxIndex = _Ment.size();
	}

	void NpcMentOff()
	{
		Ment->MentOff();
	}

	void CreateOneButtonMent(std::string_view _CancelButtonName);
	void CreateTwoButtonMent(std::string_view _CancelButtonName, std::string_view _OkButtonName, std::function<void ()> _OkButtonEndFunction = nullptr);

protected:
	std::string NpcName = "";
	std::string KoreanName = "";
	std::shared_ptr<GameEngineSpriteRenderer> NpcRenderer = nullptr;
	std::shared_ptr<GameEngineCollision> NpcCollision = nullptr;
	EventParameter NpcEvent;
	std::shared_ptr<OneButtonNpcMentFrame> Ment = nullptr;

	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void CollisionEnter(GameEngineCollision* _this, GameEngineCollision* _Other);
	void CollisionStay(GameEngineCollision* _this, GameEngineCollision* _Other);
	void CollisionExit(GameEngineCollision* _this, GameEngineCollision* _Other);

private:

};

