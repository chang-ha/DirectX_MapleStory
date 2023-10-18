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
	Arrow,
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
	PLAYBELOW,
	PLAY,
	MONSTERATTACK,
	ARROW,
	SKILL,
	HITANI,
	RENDERACTOR,
	UI,
};

enum RenderDepth
{
	ui = 1,
	renderactor,
	hitani,
	skill,
	arrow,
	monsterattack,
	play,
	playbelow,
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