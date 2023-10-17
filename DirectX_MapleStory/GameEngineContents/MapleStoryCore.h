#pragma once
#include <GameEngineCore/GameEngineObject.h>

class LevelChangeGUI : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
};

class MapleStoryCore : public GameEngineObject
{
public:
	// constructer destructer
	MapleStoryCore();
	~MapleStoryCore();

	// delete function
	MapleStoryCore(const MapleStoryCore& _Ohter) = delete;
	MapleStoryCore(MapleStoryCore&& _Ohter) noexcept = delete;
	MapleStoryCore& operator=(const MapleStoryCore& _Other) = delete;
	MapleStoryCore& operator=(MapleStoryCore&& _Other) noexcept = delete;

	static std::string GetWindowTitle()
	{
		return "MapleStory";
	}

	static float4 GetStartWindowSize()
	{
		return { 1366, 789 };
	}

	static float4 GetStartWindowPos()
	{
		return { 50, 50 };
	}
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:

};

