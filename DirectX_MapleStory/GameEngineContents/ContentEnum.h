#pragma once

enum class ActorDir
{
	Null,
	Right,
	Left
};

enum class UpdateOrder
{
	BackGround,
	Map,
	Play,
	Monster,
	Skill,
	RenderActor,
	UI,
};

enum class RenderOrder
{
	BACKGROUND,
	BACKGROUNDOBJECT,
	MAP,
	MAPOBJECT,
	MONSTER,
	BOSSMONSTER,
	DRAGON,
	PLAYBELOW,
	PLAY,
	MONSTERATTACK,
	SKILL,
	HITANI,
	RENDERACTOR,
	UI,
	FADEOBJECT,
};

enum RenderDepth
{
	fadeobject = 1,
	ui,
	renderactor,
	hitani,
	skill,
	monsterattack,
	play,
	playbelow,
	dragon,
	bossmonster,
	monster,
	mapobject,
	map,
	backgroundobject,
	background,
};

enum class CollisionOrder
{
	Player,
	PlayerAttack,
	Monster,
	MonsterAttack,
};