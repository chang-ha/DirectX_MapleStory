#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}

void GameEngineSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	// �������� ������ �׸��� �־� �ϰ� ���ø� �����ָ�
	// 

	// �θ��ʿ��� ��κ��� ���� ���ְ�
	GameEngineRenderer::ResSetting();

	// ���� �ɱݴ� �ְ� 

	GameEngineRenderer::Draw();
}

void GameEngineSpriteRenderer::SetSprite(std::string_view _Name)
{
}