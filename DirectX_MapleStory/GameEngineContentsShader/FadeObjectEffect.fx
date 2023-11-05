#include "..\\GameEngineCoreShader\\RenderBase.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    // ÇÈ¼¿½¦ÀÌ´õ¿¡ º¸³»´À ¤¤¿ª
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

PixelOutPut FadeObjectEffect_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D FadeTex : register(t0);
SamplerState FadeTexSampler : register(s0);

float4 FadeObjectEffect_PS(PixelOutPut _Input) : SV_Target0
{
    // return float4(1.0f, 0.0f, 0.0f, 1.0f);
    
    float4 Color = FadeTex.Sample(FadeTexSampler, _Input.TEXCOORD.xy);
    
    Color.w = 1.0f;
    
    Color.xyz += AccDeltaTime;
    
    if (Color.r >= 1.0f)
    {
        Color.r = 1.0f;
    }
    
    if (Color.g >= 1.0f)
    {
        Color.g = 1.0f;
    }
    
    if (Color.b >= 1.0f)
    {
        Color.b = 1.0f;
    }
    
    if (Color.a >= 1.0f)
    {
        Color.a = 1.0f;
    }
    
    return Color;
}