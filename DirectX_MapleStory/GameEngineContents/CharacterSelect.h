#pragma once
#include "ContentLevel.h"

class SelectCharacterFrame
{
	friend class CharacterSelect;
	std::shared_ptr<class RenderActor> CharacterRenderer = nullptr;
	std::shared_ptr<class RenderActor> CharacterFootHold = nullptr;
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
	std::shared_ptr<class RenderActor> CharacterInfo_BG = nullptr;
	std::vector<SelectCharacterFrame> AllCharacter;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;

};

