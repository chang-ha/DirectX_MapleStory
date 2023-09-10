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
	Monster,
	Play,
	Skill,
	Arrow,
};

enum class RenderOrder
{
	BackGround,
	Map,
	Monster,
	Skill,
	Play,
	Arrow,
};

enum class CollisionOrder
{
	Player,
	Monster,
	PlayerAttack,
	MonsterAttack,
};