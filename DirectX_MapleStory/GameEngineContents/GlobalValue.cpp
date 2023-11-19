#include "PreCompile.h"
#include "GlobalValue.h"
#include "MapleStoryCore.h"

GlobalValue::GlobalValue()
{

}

GlobalValue::~GlobalValue()
{

}

float4 GlobalValue::WinScale = MapleStoryCore::GetStartWindowSize();
float GlobalValue::SkillEffectAlpha = 1.0f;
float GlobalValue::SkillVolume = 0.7f;
float GlobalValue::HitVolume = 1.0f;
