#include "Transform.fx"
#include "RenderBase.fx"

// �ڵ� ���Ĵٵ� (�� ���Ѿ���)
// ���ϸ�� �Լ����� ��ġ���Ѿ���
// ���ؽ� ���̴��� "������" �ڿ� _VS�� ���δ�.
// �ȼ� ���̴��� "������" �ڿ� _PS�� ���δ�.

// �ǹ��ִ� ���ص� ���̴��̴�.
float4 ColorShader_VS(float4 pos : POSITION) : SV_Position
{
    return mul(pos, WorldViewProjectionMatrix);
}

float4 ColorShader_PS(float4 pos : SV_Position) : SV_Target0
{
    return BaseColor;

}