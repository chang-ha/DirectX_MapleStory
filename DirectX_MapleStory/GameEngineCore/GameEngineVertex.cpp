#include "PreCompile.h"
#include "GameEngineVertex.h"

GameEngineInputLayOutInfo GameEngineVertex::VertexInfo;

class GameEngineVertexStart
{
public:
	GameEngineVertexStart()
	{
		GameEngineVertex::VertexInfo.AddInputLayOutDesc("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
		GameEngineVertex::VertexInfo.AddInputLayOutDesc("TEXCOORD", DXGI_FORMAT_R32G32B32A32_FLOAT);
		GameEngineVertex::VertexInfo.AddInputLayOutDesc("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
		GameEngineVertex::VertexInfo.AddInputLayOutDesc("NORMAL", DXGI_FORMAT_R32G32B32A32_FLOAT);
		GameEngineVertex::VertexInfo.AddInputLayOutDesc("BINORMAL", DXGI_FORMAT_R32G32B32A32_FLOAT);
		GameEngineVertex::VertexInfo.AddInputLayOutDesc("TANGENT", DXGI_FORMAT_R32G32B32A32_FLOAT);
		GameEngineVertex::VertexInfo.AddInputLayOutDesc("BLENDWEIGHT", DXGI_FORMAT_R32G32B32A32_FLOAT);
		GameEngineVertex::VertexInfo.AddInputLayOutDesc("BLENDINDICES", DXGI_FORMAT_R32G32B32A32_SINT);
	}
};

GameEngineVertexStart GameEngineVertex2DInit;