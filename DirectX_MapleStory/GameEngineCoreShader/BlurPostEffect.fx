#include "RenderBase.fx"
#include "Function.fx"

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


PixelOutPut BlurPostEffect_VS(GameEngineVertex2D _Input)
{
    PixelOutPut Result = (PixelOutPut) 0;
    Result.POSITION = _Input.POSITION;
    Result.TEXCOORD = _Input.TEXCOORD;
    return Result;
}

Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);

float4 BlurPostEffect_PS(PixelOutPut _Input) : SV_Target0
{
    return GaussianBlur(DiffuseTex, DiffuseTexSampler, ScreenSize, _Input.TEXCOORD);
}