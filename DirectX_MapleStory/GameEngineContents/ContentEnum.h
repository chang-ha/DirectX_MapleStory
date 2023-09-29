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
	UI,
};

enum class RenderOrder
{
	BackGround,
	Map,
	Monster,
	PlayBelow,
	Play,
	MonsterAttack,
	Skill,
	Arrow,
	UI,
};

enum class CollisionOrder
{
	Player,
	PlayerAttack,
	Monster,
	MonsterAttack,
};