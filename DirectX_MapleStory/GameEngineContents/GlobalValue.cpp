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
float GlobalValue::BGVolume = 1.0f;
float GlobalValue::SkillEffectAlpha = 1.0f;
float GlobalValue::SkillVolume = 0.7f;
float GlobalValue::HitVolume = 0.3f;
float GlobalValue::FieldMonsterVolume = 0.5f;
