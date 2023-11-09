
#define GAUX 7
#define GAUY 7

static float Gau[GAUY][GAUX] =
{
    { 0.000f, 0.000f, 0.001f, 0.001f, 0.001f, 0.000f, 0.000f },
    { 0.000f, 0.002f, 0.012f, 0.002f, 0.012f, 0.002f, 0.000f },
    { 0.001f, 0.012f, 0.068f, 0.109f, 0.068f, 0.012f, 0.001f },
    { 0.001f, 0.020f, 0.109f, 0.172f, 0.109f, 0.020f, 0.001f },
    { 0.001f, 0.012f, 0.068f, 0.109f, 0.068f, 0.012f, 0.001f },
    { 0.000f, 0.002f, 0.012f, 0.020f, 0.012f, 0.002f, 0.000f },
    { 0.000f, 0.000f, 0.001f, 0.001f, 0.001f, 0.000f, 0.000f },
};

float4 GaussianBlur(Texture2D _Tex, SamplerState _Sampler, float2 _Scale, float2 _PixelUV)
{
    // _Scale 1280 720
    float2 PixelSize = float2(1.0f / _Scale.x, 1.0f / _Scale.y);
    float2 StartUV = _PixelUV.xy + (-PixelSize * 3.0f);
    float2 CurUV = StartUV;
    float4 Result = (float4)0.0f;
 
    for (int Y = 0; Y < GAUY; ++Y)
    {
        for (int X = 0; X < GAUX; ++X)
        {
            Result += _Tex.Sample(_Sampler, CurUV) * Gau[Y][X];
            CurUV.x += PixelSize.x;
        }
        
        CurUV.x = StartUV.x;
        CurUV.y += PixelSize.y;
    }
    
    return Result;
}

