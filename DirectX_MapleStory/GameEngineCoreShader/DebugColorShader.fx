#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
};


struct PixelOutPut
{
    float4 POSITION : SV_POSITION;
};


PixelOutPut DebugColor_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    return Result;
}

cbuffer DebugColor : register(b0)
{
    float4 Color;
}

float4 DebugColor_PS(PixelOutPut _Input) : SV_Target0
{
    return Color;
}