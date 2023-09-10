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
	Skill,
	Arrow,
	Monster,
};

enum class RenderOrder
{
	BackGround,
	Map,
	Skill,
	Play,
	Arrow,
	Monster,
};

enum class CollisionOrder
{
	Player,
	Monster,
	PlayerAttack,
	MonsterAttack,
};