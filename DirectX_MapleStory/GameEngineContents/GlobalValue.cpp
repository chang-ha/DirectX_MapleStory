#include "PreCompile.h"
#include "GlobalValue.h"
#include "MapleStoryCore.h"

void GlobalValueGUI::Start()
{

}

void GlobalValueGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::SliderFloat("SkillEffectAlpha", &GlobalValue::SkillEffectAlpha, 0.2f, 1.0f);
	ImGui::SliderFloat("BGVolume", &GlobalValue::BGVolume, 0.0f, 1.0f);
	ImGui::SliderFloat("SkillVolume", &GlobalValue::SkillVolume, 0.0f, 1.0f);
	ImGui::SliderFloat("HitVolume", &GlobalValue::HitVolume, 0.0f, 1.0f);
	ImGui::SliderFloat("FieldMonsterVolume", &GlobalValue::FieldMonsterVolume, 0.0f, 1.0f);
}

GlobalValue::GlobalValue()
{
}

GlobalValue::~GlobalValue()
{

}

float4 GlobalValue::WinScale = MapleStoryCore::GetStartWindowSize();
float GlobalValue::SkillEffectAlpha = 1.0f;
float GlobalValue::BGVolume = 1.0f;
float GlobalValue::SkillVolume = 0.5f;
float GlobalValue::HitVolume = 0.5f;
float GlobalValue::FieldMonsterVolume = 0.3f;

