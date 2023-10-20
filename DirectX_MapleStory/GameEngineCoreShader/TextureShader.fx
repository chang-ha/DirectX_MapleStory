#include "Transform.fx"
#include "RenderBase.fx"

struct GameEngineVertex2D
{
    // POSITION은 View직전까지 곱한 녀석 -> W값을 나누고 ViewPort를 곱해주는건 Rasterizer가 자동으로 곱해줌
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    // SV_POSITION이란 ViewPort까지 다 곱한 녀석
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
    // _Input은 VertexBuffer값 0.5, 0.5등 이 6번 들어옴
    // Init PixelOutput
    PixelOutPut Result = (PixelOutPut) 0;

    // 해당 VertexBuffer에 WorldViewProjection을 곱해줌
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
Texture2D MaskTex : register(t1);
SamplerState DiffuseTexSampler : register(s0);

cbuffer ColorData : register(b1)
{
    float4 PlusColor; // 최종색상에 더한다.
    float4 MulColor; // 최종색상에 곱한다.
};

float4 TextureShader_PS(PixelOutPut _Input) : SV_Target0
{
    // _Input == VertexShader에서 ViewPort까지 다 곱한 SV_POSITION을 _Input값으로 들어옴
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
    
    int2 ScreenPos = int2(_Input.POSITION.x, _Input.POSITION.y);
    
    if (IsMask == 1 && MaskTex[ScreenPos].r <= 0.0f)
    {
        clip(-1);
    }
    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    if (BaseColorOnly != 0)
    {
        Color = BaseColor;
        Color.a = 1;
    }
    
    Color += PlusColor;
    Color *= MulColor;
    
    return Color;
}