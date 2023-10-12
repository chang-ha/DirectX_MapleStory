#pragma once

#define GROUND_COLOR GameEngineColor(255, 0, 255, 255)
#define FLOOR_COLOR GameEngineColor(0, 255, 0, 255)
#define LADDER_COLOR GameEngineColor(255, 0, 0, 255)

enum RenderDepth
{
	UI = 1,
	RenderActor,
	Arrow,
	Skill,
	MonsterAttack,
	Play,
	PlayBelow,
	Monster,
	MapObject,
	Map,
	BackGround,
};


// Ό³Έν :
class GlobalValue
{
public:
	// constrcuter destructer
	GlobalValue();
	~GlobalValue();

	// delete Function
	GlobalValue(const GlobalValue& _Other) = delete;
	GlobalValue(GlobalValue&& _Other) noexcept = delete;
	GlobalValue& operator=(const GlobalValue& _Other) = delete;
	GlobalValue& operator=(GlobalValue&& _Other) noexcept = delete;

	static float4 WinScale;
protected:

private:

};

