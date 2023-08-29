#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

cbuffer SpriteData : register(b1)
{
    float4 Sprite;
};

PixelOutPut TextureShader_VS(GameEngineVertex2D _Input)
{
    // Init PixelOutput
    PixelOutPut Result = (PixelOutPut) 0;

    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);

    float SizeX = 1.0f / 6.0f;
    float SizeY = 1.0f / 6.0f;
    float StartX = SizeX * 5.0f;
    float StartY = SizeY * 0.0f;
    
    Result.TEXCOORD.x = (_Input.TEXCOORD.x * SizeX) + StartX;
    Result.TEXCOORD.y = (_Input.TEXCOORD.y * SizeY) + StartY;
    
    return Result;
}

Texture2D DiffuseTex : register(t0);
SamplerState Sampler : register(s0);

float4 TextureShader_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(Sampler, _Input.TEXCOORD.xy);
    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    return Color;
}