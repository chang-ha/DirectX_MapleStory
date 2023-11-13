#pragma once

enum class ActorDir
{
	Null,
	Right,
	Left
};

enum class UpdateOrder
{
	Play,
	BackGround,
	Map,
	Monster,
	Skill,
	RenderActor,
	Portal,
	UI,
};

enum class RenderOrder
{
	BACKGROUND,
	BACKGROUNDOBJECT,
	MAP,
	MAPOBJECT,
	FOOTHOLD,
	MONSTER,
	BOSSMONSTER,
	DRAGON,
	PLAYBELOW,
	PLAY,
	MONSTERATTACK,
	SKILL,
	HITANI,
	RENDERACTOR,
	PORTAL,
	UI,
	MOUSE,
	FADEOBJECT,
};

enum RenderDepth
{
	fadeobject = 1,
	mouse,
	ui,
	portal,
	renderactor,
	hitani,
	skill,
	monsterattack,
	play,
	playbelow,
	dragon,
	bossmonster,
	monster,
	foothold,
	mapobject,
	map,
	backgroundobject,
	background,
};

enum class CollisionOrder
{
	Player = 1,
	PlayerAttack,
	Monster,
	MonsterAttack,
	Detect,
	Portal,
	Button,
	UI,
	Mouse,
};