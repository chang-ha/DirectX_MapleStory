#pragma once
#include "GameEngineInputLayOut.h"

// Ό³Έν :
class GameEngineVertex2D
{
public:
	static GameEngineInputLayOutInfo VertexInfo;

public:
	float4 POSITION;
	float4 COLOR;
	float4 TEXCOORD;
};


class GameEngine3DVertex
{
public:
	static GameEngineInputLayOutInfo VertexInfo;

public:
	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
	float4 NORMAL;
	float4 BINORMAL;
	float4 TANGENT;
	float4 WEIGHT;
	int BLENDINDICES[4];
};