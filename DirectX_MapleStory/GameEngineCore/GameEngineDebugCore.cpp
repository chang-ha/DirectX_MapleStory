#include "PreCompile.h"
#include "GameEngineDebugCore.h"

void GameEngineDebug::DrawBox2D(const GameEngineTransform& _Trans)
{
	GameEngineDebug::DrawBox2D(_Trans.GetWorldScale(), _Trans.GetWorldRotationEuler(), _Trans.GetWorldPosition());
}

void GameEngineDebug::DrawBox2D(float4 _Scale, float4 _Rot, float4 _Pos)
{

}