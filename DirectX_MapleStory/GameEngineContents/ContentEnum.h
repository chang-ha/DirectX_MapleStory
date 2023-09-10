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
};

enum class RenderOrder
{
	BackGround,
	Map,
	Skill,
	Play,
};

enum class CollisionOrder
{
	Player,
	Monster,
};