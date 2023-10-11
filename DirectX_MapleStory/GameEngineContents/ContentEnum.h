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
	BackGround,
	Map,
	MapObject,
	Monster,
	PlayBelow,
	Play,
	MonsterAttack,
	Skill,
	Arrow,
	RenderActor,
	UI,
};

enum class CollisionOrder
{
	Player,
	PlayerAttack,
	Monster,
	MonsterAttack,
};