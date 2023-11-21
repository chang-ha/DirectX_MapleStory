#include "PreCompile.h"
#include "GameEngineParticleRenderer.h"

GameEngineParticleRenderer::GameEngineParticleRenderer()
{
}

GameEngineParticleRenderer::~GameEngineParticleRenderer()
{

}

void GameEngineParticleRenderer::Start()
{
	GameEngineRenderer::Start();

	UpdateUnit.SetComputeShader("ParticleUpdate_CS");

	// UpdateUnit.ShaderResHelper.SetConstantBufferLink()

	// UpdateUnit.ShaderResHelper.SetStructedBufferLink()

	// ���� ����Ʈ�� �˾Ƽ� �������� �ϴ°̴ϴ�
	// GameEngineRenderer::SetMesh("Rect");
	// GameEngineRenderer::SetMaterial("2DTexture");
}

void GameEngineParticleRenderer::Update(float _DeltaTime)
{
	// ������ ��ƼŬ �����͸� ��ǻƮ���̴��� ����ϰ�
	UpdateUnit.Excute();
}

void GameEngineParticleRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{

}