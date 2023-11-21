#include "RenderBase.fx"
#include "Function.fx"


struct ParticleShareData
{
    uint iAliveCount;
    uint iPadding0;
    uint iPadding1;
    uint iPadding2;
};

RWStructuredBuffer<ParticleShareData> ParticleShareBuffer : register(u0);

[numthreads(128, 1, 1)]
void ParticleUpdate_CS(uint3 _id : SV_DispatchThreadID)
{
    ParticleShareBuffer[0].iAliveCount = 1;
}