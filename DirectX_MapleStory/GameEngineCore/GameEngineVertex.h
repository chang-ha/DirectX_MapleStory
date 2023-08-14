#pragma once

// Ό³Έν :
class GameEngineVertex2D
{
public:
	float4 TEXCOORD;
	float4 COLOR;
	float4 POSITION;
};


class GameEngine3DVertex
{
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