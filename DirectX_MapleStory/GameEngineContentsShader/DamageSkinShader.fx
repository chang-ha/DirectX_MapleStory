#include "..\\GameEngineCoreShader\\Transform.fx"
#include "..\\GameEngineCoreShader\\RenderBase.fx"

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

//cbuffer SpriteData : register(b1)
//{
//    float Pos2DX;
//    float Pos2DY;
//    float Scale2DX;
//    float Scale2DY;
//};

cbuffer UVInfo : register(b2)
{
    float Ratio;
    float UVTemp1;
    float UVTemp2;
    float UVTemp3;

    vector<float, 4> RendererUVs1;
	vector<float, 4> RendererUVs2;

    vector<float, 4> TextureUVs1;
	vector<float, 4> TextureUVs2;
};

PixelOutPut DamageSkinShader_VS(GameEngineVertex2D _Input)
{
    // _Input�� VertexBuffer�� 0.5, 0.5�� �� 6�� ����
    // Init PixelOutput
    PixelOutPut Result = (PixelOutPut) 0;

    // �ش� VertexBuffer�� WorldViewProjection�� ������
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);

    Result.TEXCOORD.x = _Input.TEXCOORD.x * Ratio;
    Result.TEXCOORD.y = _Input.TEXCOORD.y;
    
    return Result;
}

// ��Ģ
// Texture�̸��� A�̸� Sampler�̸��� ASampler << ��Ģ�� ���Ѿ� ���� ���� �ڵ� ���̴� �������� �۵���
Texture2D DamageSkinTex : register(t0);
SamplerState DamageSkinTexSampler : register(s0);

cbuffer ColorData : register(b3)
{
    float4 PlusColor; // �������� ���Ѵ�.
    float4 MulColor; // �������� ���Ѵ�.
};

struct PixelOut
{
    float4 Color0 : SV_Target0;
};

PixelOut DamageSkinShader_PS(PixelOutPut _Input) : SV_Target0
{
    PixelOut Result = (PixelOut) 0.0f;

    float4 CalUV = _Input.TEXCOORD;
    
    if (RendererUVs1[0] * Ratio >= _Input.TEXCOORD.x)
    {
        CalUV.x = TextureUVs1[0]+ _Input.TEXCOORD.x;
    }
    else if (RendererUVs1[1] * Ratio >= _Input.TEXCOORD.x)
    {
        CalUV.x = TextureUVs1[1] - RendererUVs1[0] * Ratio + _Input.TEXCOORD.x;
    }
    else if (RendererUVs1[2] * Ratio >= _Input.TEXCOORD.x)
    {
        CalUV.x = TextureUVs1[2] - RendererUVs1[1] * Ratio + _Input.TEXCOORD.x;
    }
    else if (RendererUVs1[3] * Ratio >= _Input.TEXCOORD.x)
    {
        CalUV.x = TextureUVs1[3] - RendererUVs1[2] * Ratio + _Input.TEXCOORD.x;
    }
    else if (RendererUVs2[0] * Ratio >= _Input.TEXCOORD.x)
    {
        CalUV.x = TextureUVs2[0] - RendererUVs1[3] * Ratio + _Input.TEXCOORD.x;
    }
    else if (RendererUVs2[1] * Ratio >= _Input.TEXCOORD.x)
    {
        CalUV.x = TextureUVs2[1] - RendererUVs2[0] * Ratio + _Input.TEXCOORD.x;
    }
    else if (RendererUVs2[2] * Ratio >= _Input.TEXCOORD.x)
    {
        CalUV.x = TextureUVs2[2] - RendererUVs2[1] * Ratio + _Input.TEXCOORD.x;
    }
    else if (RendererUVs2[3] * Ratio >= _Input.TEXCOORD.x)
    {
        CalUV.x = TextureUVs2[3] - RendererUVs2[2] * Ratio + _Input.TEXCOORD.x;
    }
    
    float4 Color = DamageSkinTex.Sample(DamageSkinTexSampler, CalUV.xy);
    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    Color += PlusColor;
    Color *= MulColor;
    
    if (0 < Target0)
    {
        Result.Color0 = Color;
    }
    
    return Result;
}