#include "PreCompile.h"
#include "GameEngineDebugCore.h"
#include "GameEngineRenderUnit.h"
#include "GameEngineLevel.h"

class GameEngineDebugInfo
{
public:
	float4 Color = float4::RED;
	GameEngineCamera* Camera;
	TransformData Data;
	GameEngineRenderUnit Unit;
};

std::vector<GameEngineDebugInfo> DebugUnit;
GameEngineLevel* GameEngineDebug::GameEngineDebugCore::CurLevel = nullptr;

void GameEngineDebug::GameEngineDebugCore::DebugInit()
{
	// 임시로 100개 
	DebugUnit.resize(100);
}

void GameEngineDebug::GameEngineDebugCore::DebugRender()
{
	// RenderUnit마다 Setting 및 Draw
	for (size_t i = 0; i < DebugUnit.size(); i++)
	{
		DebugUnit[i].Unit.ResSetting();
		DebugUnit[i].Unit.Draw();
	}

	// Vector의 Clear는 메모리는 재할당 X, 안의 데이터만 지움
	DebugUnit.clear();
}

void GameEngineDebug::DrawBox2D(const GameEngineTransform& _Trans, float4 _Color, GameEngineCamera* _Camera)
{
	GameEngineDebug::DrawBox2D(_Trans.GetWorldScale(), _Trans.GetWorldRotationEuler(), _Trans.GetWorldPosition(), _Color, _Camera);
}

void GameEngineDebug::DrawBox2D(float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color, GameEngineCamera* _Camera)
{
	GameEngineDebug::DrawMesh("Rect", _Scale, _Rot, _Pos, _Color, _Camera);
}

void GameEngineDebug::DrawSphere2D(const GameEngineTransform& _Trans, float4 _Color /*= float4::RED*/, class GameEngineCamera* _Camera /*= nullptr*/)
{
	GameEngineDebug::DrawSphere2D(_Trans.GetWorldScale(), _Trans.GetWorldRotationEuler(), _Trans.GetWorldPosition(), _Color, _Camera);
}
void GameEngineDebug::DrawSphere2D(float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color /*= float4::RED*/, class GameEngineCamera* _Camera /*= nullptr*/)
{
	GameEngineDebug::DrawMesh("Sphere", _Scale, _Rot, _Pos, _Color, _Camera);
}

void GameEngineDebug::DrawMesh(const std::string_view& _Mesh, float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color /*= float4::RED*/, class GameEngineCamera* _Camera /*= nullptr*/)
{
	if (nullptr == _Camera)
	{
		_Camera = GameEngineDebug::GameEngineDebugCore::CurLevel->GetMainCamera().get();
	}

	// Sphere는 타원 충돌이 안되기 때문에 X를 기준으로 충돌함
	_Scale.Y = _Scale.Z = _Scale.X;

	GameEngineDebugInfo& Value = DebugUnit.emplace_back();
	Value.Camera = _Camera;
	Value.Unit.SetMesh(_Mesh);
	Value.Unit.SetMaterial("2DTextureWire");

	Value.Color = _Color;
	Value.Data.Scale = _Scale;
	Value.Data.Rotation = _Rot;
	Value.Data.Position = _Pos;
	Value.Data.LocalCalculation();
	Value.Data.ViewMatrix = _Camera->Transform.GetConstTransformDataRef().ViewMatrix;
	Value.Data.ProjectionMatrix = _Camera->Transform.GetConstTransformDataRef().ProjectionMatrix;
	Value.Data.WorldViewProjectionCalculation();

	Value.Unit.ShaderResHelper.SetConstantBufferLink("TransformData", Value.Data);
	Value.Unit.ShaderResHelper.SetConstantBufferLink("DebugColor", Value.Color);
}