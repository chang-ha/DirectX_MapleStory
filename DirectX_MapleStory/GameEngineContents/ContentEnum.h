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
};

enum class RenderOrder
{
	BackGround,
	Map,
	Skill,
	Play,
	Arrow,
};

enum class CollisionOrder
{
	Player,
	Monster,
};