#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    // �ȼ����̴��� ������ ����
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

// ������۸� ���鶧�� �ִ���
// 16����Ʈ ����°� ����.
// �׷���ī���°��� �Ǽ��� �����ϱ� ���ؼ� ����� �����.
// hlsl������ bool������ ������� �ʴ� ���� �� ����.
cbuffer SpriteRendererInfo : register(b3)
{
    int FlipLeft = 0;
    int FlipUp = 0;
    float Temp1;
    float Temp2;
};

// ����ȭ�� 
// Ƚ���� �߿��մϴ�.

cbuffer SpriteData : register(b1)
{
    float Pos2DX;
    float Pos2DY;
    float Scale2DX;
    float Scale2DY;
};



// ���ϸ�� �Լ����� ��ġ��Ű�� ���ؽ� ���̴��� ������ �ڿ� _VS�� ���Դϴ�.
// �ǹ��ִ� ���ؽ� ���̴��̴�.
PixelOutPut TextureShaderMask_VS(GameEngineVertex2D _Input)
{
    // _Input 0.5 0.5
    
    // ���̴� ���� ��� 0�� �ڷ������� �ʱ�ȭ �ϴ°�
    PixelOutPut Result = (PixelOutPut)0;
    
    // ���� ���ϴ� ���� �̾ȿ� �־��ټ� �־�� �Ѵ�.
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    // Result.TEXCOORD = _Input.TEXCOORD;
    
    // 6�� ���ؽ��� ���ð��̴�.
    
    float4 CalUV = _Input.TEXCOORD;
    
    // hlsl�� ������� ���� �༮�� �ν����� ���մϴ�.
    // ����� ���ǹ��� ������ �ִ� ���ҽ��� �ƴϸ� hlsl�� ����ȭ�� ���ؼ� �� ���ҽ��� �����Ѵ�.
    // ����� ������ ���ִ� ������۰� �ǹ̰� �־�? �׷� ������۴� ���� �˾Ƽ� �����Ҳ�.
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
    
    // ���ؽ� ���� ��� �Ǿ��ֳ�?
    return Result;
}

// b���� 14
// t�ؽ�ó 
// s���÷� 
// ���� ������ �������� �ʴ´�.

// ���� ���÷��� �ؽ�ó�� 1������ ���Ǳ� ������
// ���÷��� �ؽ�ó�� ������ �����ö� ������ ���ְų� Ư���� ���ĵ��� ���ο���
// ������ִ� �뵵�� �ִ�.

// �츮 ��Ģ

Texture2D DiffuseTex : register(t0);
Texture2D MaskTex : register(t1);
SamplerState DiffuseTexSampler : register(s0);

float4 TextureShaderMask_PS(PixelOutPut _Input) : SV_Target0
{
   
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
    // ������ �۾��� ����� �Ѵ�.
    
    int2 ScreenPos = int2(_Input.POSITION.x, _Input.POSITION.y);
    
    if (MaskTex[ScreenPos].r <= 0.0f)
    {
        clip(-1);
    }
    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    return Color;
}