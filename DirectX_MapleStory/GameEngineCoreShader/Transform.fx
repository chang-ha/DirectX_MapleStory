cbuffer TransformData : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;
    float4x4 ScaleMatrix; // 크
    float4x4 RotationMatrix; // 자
    float4x4 PositionMatrix; // 이
    float4x4 RevolutionMatrix; // 공
    float4x4 ParentMatrix; // 공
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 ViewMatrix;
    float4x4 ProjectionMatrix;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
    // 0, 0, 0, 0
    // 0, 0, 0, 0
    // 0, 0, 0, 0
    // 0, 0, 0, 0
};