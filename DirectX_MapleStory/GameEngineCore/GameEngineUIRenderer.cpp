#include "PreCompile.h"
#include "GameEngineUIRenderer.h"

GameEngineUIRenderer::GameEngineUIRenderer()
{

}

GameEngineUIRenderer::~GameEngineUIRenderer()
{

}

void GameEngineUIRenderer::Start()
{
	GameEngineSpriteRenderer::Start();
	SetCameraOrder(ECAMERAORDER::UI);
}
