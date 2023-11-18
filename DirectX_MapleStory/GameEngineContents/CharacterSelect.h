#pragma once
#include "ContentLevel.h"

class SelectCharacterFrame
{
	friend class CharacterSelect;
	std::shared_ptr<class UIRenderActor> CharacterRenderer = nullptr;
	std::shared_ptr<class UIRenderActor> CharacterFootHold = nullptr;
};

class CharacterInfoFrame
{
	friend class CharacterSelect;
	std::shared_ptr<class UIRenderActor> CharacterInfo_BG = nullptr;
	std::shared_ptr<class ContentButton> GameStartButton = nullptr;
	std::shared_ptr<GameEngineUIRenderer> CharacterName = nullptr;
	std::shared_ptr<GameEngineUIRenderer> JobName = nullptr;
	std::shared_ptr<GameEngineUIRenderer> STR = nullptr;
	std::shared_ptr<GameEngineUIRenderer> DEX = nullptr;
	std::shared_ptr<GameEngineUIRenderer> INT = nullptr;
	std::shared_ptr<GameEngineUIRenderer> LUK = nullptr;

	void FrameOff();

	void FrameOn();
};

class CharacterSelect : public ContentLevel
{
public:
	// constructer destructer
	CharacterSelect();
	~CharacterSelect();

	// delete function
	CharacterSelect(const CharacterSelect& _Ohter) = delete;
	CharacterSelect(CharacterSelect&& _Ohter) noexcept = delete;
	CharacterSelect& operator=(const CharacterSelect& _Other) = delete;
	CharacterSelect& operator=(CharacterSelect&& _Other) noexcept = delete;

protected:

private:
	bool IsCharacterSelect = false;
	std::shared_ptr<class GameEngineCollision> SelectCollision = nullptr;
	std::shared_ptr<class UIRenderActor> CharSelectEffect0 = nullptr;
	std::shared_ptr<class UIRenderActor> CharSelectEffect1 = nullptr;
	CharacterInfoFrame InfoFrame;
	std::vector<SelectCharacterFrame> AllCharacter;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void ResourcesRelease() override;

	void SelectCharacter();
};

