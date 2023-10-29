#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    uint iVertex : SV_VertexID;
};


struct PixelOutPut
{
    float4 POSITION : SV_POSITION;
};


PixelOutPut DebugLine_VS(GameEngineVertex2D _Input)
{
    // 쉐이더 문법 모두 0인 자료형으로 초기화 하는것
    PixelOutPut Result = (PixelOutPut) 0;
    float4x4 ViewProjectionMatrix = ViewMatrix * ProjectionMatrix;
    
    if (_Input.iVertex == 0)
    {
        Result.POSITION = mul(Position, ViewProjectionMatrix);
    }
    else if (_Input.iVertex == 1)
    {
        Result.POSITION = mul(Scale, ViewProjectionMatrix);
    }
    
    
    
    return Result;
}

cbuffer DebugColor : register(b0)
{
    float4 Color;
}

float4 DebugLine_PS(PixelOutPut _Input) : SV_Target0
{
    return Color;
}