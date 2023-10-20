#include "Transform.fx"
#include "RenderBase.fx"

struct GameEngineVertex2D
{
    // POSITION�� View�������� ���� �༮ -> W���� ������ ViewPort�� �����ִ°� Rasterizer�� �ڵ����� ������
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    // SV_POSITION�̶� ViewPort���� �� ���� �༮
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
    // _Input�� VertexBuffer�� 0.5, 0.5�� �� 6�� ����
    // Init PixelOutput
    PixelOutPut Result = (PixelOutPut) 0;

    // �ش� VertexBuffer�� WorldViewProjection�� ������
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

// ��Ģ
// Texture�̸��� A�̸� Sampler�̸��� ASampler << ��Ģ�� ���Ѿ� ���� ���� �ڵ� ���̴� �������� �۵���
Texture2D DiffuseTex : register(t0);
Texture2D MaskTex : register(t1);
SamplerState DiffuseTexSampler : register(s0);

cbuffer ColorData : register(b1)
{
    float4 PlusColor; // �������� ���Ѵ�.
    float4 MulColor; // �������� ���Ѵ�.
};

float4 TextureShader_PS(PixelOutPut _Input) : SV_Target0
{
    // _Input == VertexShader���� ViewPort���� �� ���� SV_POSITION�� _Input������ ����
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