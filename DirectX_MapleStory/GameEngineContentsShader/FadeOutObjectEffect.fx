#include "..\\GameEngineCoreShader\\RenderBase.fx"
#include "FadeObjectInfo.fx"

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

float4 FadeOutObjectEffect_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Color = FadeTex.Sample(FadeTexSampler, _Input.TEXCOORD.xy);
    
    float FadeColor = 0.0f;
    
    if (true == WhiteFade)
    {
        FadeColor += AccDeltaTime * FadeSpeed;
        if (1.0f <= FadeColor)
        {
            FadeColor = 1.0f;
        }
    }
    else if (false == WhiteFade)
    {
        FadeColor -= AccDeltaTime * FadeSpeed;
        if (-1.0f >= FadeColor)
        {
            FadeColor = -1.0f;
        }
    }
    
    Color.w = 1.0f;
    
    Color.xyz += FadeColor;
    
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

    if (Color.r <= 0.0f)
    {
        Color.r = 0.0f;
    }
    
    if (Color.g <= 0.0f)
    {
        Color.g = 0.0f;
    }
    
    if (Color.b <= 0.0f)
    {
        Color.b = 0.0f;
    }
    
    if (Color.a <= 0.0f)
    {
        Color.a = 0.0f;
    }
    
    return Color;
}