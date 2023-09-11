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
	PlayerAttack,
	Monster,
	MonsterAttack,
};