#pragma once
#include <GameEngineCore\GameEngineLevel.h>

class LevelDebug : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
};

// Ό³Έν :
class ContentMap;
class ContentLevel : public GameEngineLevel
{
public:
	static ContentLevel* CurContentLevel;

public:
	// constructer destructer
	ContentLevel();
	~ContentLevel();

	// delete function
	ContentLevel(const ContentLevel& _Ohter) = delete;
	ContentLevel(ContentLevel&& _Ohter) noexcept = delete;
	ContentLevel& operator=(const ContentLevel& _Other) = delete;
	ContentLevel& operator=(ContentLevel&& _Other) noexcept = delete;

	std::shared_ptr<ContentMap> GetCurMap()
	{
		return CurMap;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	std::shared_ptr<ContentMap> CurMap = nullptr;
	std::shared_ptr<class FadeObject> FadeInObject = nullptr;
	std::shared_ptr<class FadeObject> FadeOutObject = nullptr;
private:

};

