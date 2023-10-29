#pragma once
#include "GameEngineCamera.h"

namespace GameEngineDebug
{
	void DrawBox2D(const GameEngineTransform& _Trans, float4 _Color = float4::RED, class GameEngineCamera* _Camera = nullptr);
	void DrawBox2D(float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color = float4::RED, class GameEngineCamera* _Camera = nullptr);

	void DrawSphere2D(const GameEngineTransform& _Trans, float4 _Color = float4::RED, class GameEngineCamera* _Camera = nullptr);
	void DrawSphere2D(float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color = float4::RED, class GameEngineCamera* _Camera = nullptr);

	void DrawMesh(const std::string_view& _Mesh, float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color = float4::RED, class GameEngineCamera* _Camera = nullptr);

	void DrawLine(float4 _Start, float4 _End, float4 _Color = float4::RED, class GameEngineCamera* _Camera = nullptr);

	class GameEngineDebugCore
	{
		friend class GameEngineLevel;
		// 함수도 friend걸수 있습니다.
		friend void GameEngineDebug::DrawMesh(const std::string_view& _Mesh, float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color, class GameEngineCamera* _Camera);
		friend void GameEngineDebug::DrawLine(float4 _Start, float4 _End, float4 _Color, class GameEngineCamera* _Camera);

	private:
		static class GameEngineLevel* CurLevel;

		static void DebugInit();
		static void DebugRender();
	};
}