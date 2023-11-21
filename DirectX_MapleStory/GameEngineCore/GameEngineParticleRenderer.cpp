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

	// 랜더 유니트가 알아서 랜더링을 하는겁니다
	// GameEngineRenderer::SetMesh("Rect");
	// GameEngineRenderer::SetMaterial("2DTexture");
}

void GameEngineParticleRenderer::Update(float _DeltaTime)
{
	// 수백의 파티클 데이터를 컴퓨트쉐이더로 계산하고
	UpdateUnit.Excute();
}

void GameEngineParticleRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{

}