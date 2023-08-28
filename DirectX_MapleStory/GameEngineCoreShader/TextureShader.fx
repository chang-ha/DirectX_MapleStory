#include "Transform.fx"

float4 TextureShader_VS( float4 pos : POSITION ) : SV_POSITION
{
    return mul(pos, WorldViewPorjectionMatrix);
}

Texture2D DiffuseTex : register(t0);
SamplerState Sampler : register(s0);

float4 TextureShader_PS(float4 pos : SV_Position) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(Sampler, float2(0, 0));
    return Color;
}