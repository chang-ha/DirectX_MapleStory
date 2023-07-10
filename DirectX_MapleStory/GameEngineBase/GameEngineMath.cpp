#include "GameEngineMath.h"


const float4 float4::ZERO = { 0.0f, 0.0f, 0.0f, 0.0f };

const float4 float4::LEFT = { -1.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::RIGHT = { 1.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::UP = { 0.0f, -1.0f, 0.0f, 0.0f };
const float4 float4::DOWN = { 0.0f, 1.0f, 0.0f, 0.0f };

const float GameEngineMath::PI = 3.14159265358979323846264338327950288419716939937510f;
const float GameEngineMath::PI2 = PI * 2.0f;

// Radian To Degree, Degree To Radian
const float GameEngineMath::R2D = 180.0f / GameEngineMath::PI;
const float GameEngineMath::D2R = GameEngineMath::PI / 180.0f;