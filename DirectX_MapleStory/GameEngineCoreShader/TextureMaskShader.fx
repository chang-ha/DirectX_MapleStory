#include "Transform.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    // 픽셀쉐이더에 보내느 ㄴ역
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

// 상수버퍼를 만들때는 최대한
// 16바이트 만드는게 좋다.
// 그래픽카드라는것은 실수를 연산하기 위해서 만들어 졌어요.
// hlsl에서는 bool같은건 사용하지 않는 것이 더 좋다.
cbuffer SpriteRendererInfo : register(b3)
{
    int FlipLeft = 0;
    int FlipUp = 0;
    float Temp1;
    float Temp2;
};

// 최적화는 
// 횟수가 중요합니다.

cbuffer SpriteData : register(b1)
{
    float Pos2DX;
    float Pos2DY;
    float Scale2DX;
    float Scale2DY;
};



// 파일명과 함수명을 일치시키고 버텍스 쉐이더면 무조건 뒤에 _VS를 붙입니다.
// 의미있는 버텍스 쉐이더이다.
PixelOutPut TextureShaderMask_VS(GameEngineVertex2D _Input)
{
    // _Input 0.5 0.5
    
    // 쉐이더 문법 모두 0인 자료형으로 초기화 하는것
    PixelOutPut Result = (PixelOutPut)0;
    
    // 내가 원하는 값을 이안에 넣어줄수 있어야 한다.
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);
    // Result.TEXCOORD = _Input.TEXCOORD;
    
    // 6의 버텍스가 들어올것이다.
    
    float4 CalUV = _Input.TEXCOORD;
    
    // hlsl은 사용하지 않은 녀석은 인식하지 못합니다.
    // 결과에 유의미한 영향을 주는 리소스가 아니면 hlsl은 최적화를 통해서 그 리소스를 배제한다.
    // 결과에 영향을 안주는 상수버퍼가 의미가 있어? 그런 상수버퍼는 내가 알아서 삭제할께.
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
    
    // 버텍스 들은 어떻게 되어있나?
    return Result;
}

// b버퍼 14
// t텍스처 
// s샘플러 
// 둘의 슬롯은 공유되지 않는다.

// 보통 샘플러와 텍스처는 1쌍으로 사용되기 때문에
// 샘플러는 텍스처의 색상을 가져올때 보간을 해주거나 특수한 공식등을 내부에서
// 사용해주는 용도가 있다.

// 우리 규칙

Texture2D DiffuseTex : register(t0);
Texture2D MaskTex : register(t1);
SamplerState DiffuseTexSampler : register(s0);

float4 TextureShaderMask_PS(PixelOutPut _Input) : SV_Target0
{
   
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
    // 블랜드라는 작업을 해줘야 한다.
    
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