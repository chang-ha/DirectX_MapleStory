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
    float Pos2DX;
    float Pos2DY;
    float Scale2DX;
    float Scale2DY;
};

cbuffer SpriteRendererInfo : register(b3)
{
    int FlipLeft = 0;
    int FlipUp = 0;
    float Temp1;
    float Temp2;
};

PixelOutPut TextureShader_VS(GameEngineVertex2D _Input)
{
    // Init PixelOutput
    PixelOutPut Result = (PixelOutPut) 0;

    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);

    float4 CalUV = _Input.TEXCOORD;
    if (0 != FlipLeft)
    {
        CalUV.x *= -1;
        CalUV.x += 1;
    }

    if (0 != FlipUp)
    {
        CalUV.y *= -1;
        CalUV.y += 1;
    }
    
    Result.TEXCOORD.x = (CalUV.x * Scale2DX) + Pos2DX;
    Result.TEXCOORD.y = (CalUV.y * Scale2DY) + Pos2DY;
    
    return Result;
}

// 규칙
// Texture이름이 A이면 Sampler이름은 ASampler << 규칙을 지켜야 내가 만든 자동 쉐이더 컴파일이 작동함
Texture2D DiffuseTex : register(t0);
SamplerState DiffuseTexSampler : register(s0);

float4 TextureShader_PS(PixelOutPut _Input) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    return Color;
}