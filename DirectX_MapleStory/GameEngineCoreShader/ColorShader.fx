#include "Transform.fx"

// 코딩 스탠다드 (꼭 지켜야함)
// 파일명과 함수명은 일치시켜야함
// 버텍스 쉐이더면 "무조건" 뒤에 _VS를 붙인다.
// 픽셀 쉐이더면 "무조건" 뒤에 _PS를 붙인다.

// 의미있는 버텍드 쉐이더이다.
float4 ColorShader_VS(float4 pos : POSITION) : SV_Position
{
    return mul(pos, WorldViewProjectionMatrix);
}

float4 ColorShader_PS(float4 pos : SV_Position) : SV_Target0
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}