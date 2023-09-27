#pragma once
#include "GameEngineCamera.h"

namespace GameEngineDebug
{
	void DrawBox2D(const GameEngineTransform& _Trans, float4 _Color = float4::RED, GameEngineCamera* _Camera = nullptr);

	void DrawBox2D(float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color = float4::RED, GameEngineCamera* _Camera = nullptr);

	class GameEngineDebugCore
	{
		friend class GameEngineLevel;
		// ÇÔ¼ö friend
		friend void GameEngineDebug::DrawBox2D(float4 _Scale, float4 _Rot, float4 _Pos, float4 _Color, GameEngineCamera* _Camera);

	private:
		static class GameEngineLevel* CurLevel;

		static void DebugInit();
		static void DebugRender();
	};
}

