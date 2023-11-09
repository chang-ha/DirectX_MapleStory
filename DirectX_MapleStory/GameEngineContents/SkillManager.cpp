#include "PreCompile.h"

#include <GameEngineBase\GameEngineRandom.h>

#include "SkillManager.h"
#include "ContentSkill.h"
#include "DoubleJump.h"
#include "SongOfHeaven.h"
#include "FairySpiral.h"
#include "WindWalk.h"
#include "HowlingGale.h"
#include "Monsoon.h"
#include "VortexSphere.h"
#include "PhalanxCharge.h"
#include "MercilessWinds.h"
#include "BaseWindActor.h"
#include "ContentActor.h"

void SkillManagerGUI::Start()
{
	
}

void SkillManagerGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::SliderFloat("SkillEffect", &GlobalValue::SkillEffectAlpha, 0.2f, 1.0f);
}

SkillManager* SkillManager::PlayerSkillManager = nullptr;

#define HIT_ANI_TIME 0.04f
#define HIT_DELAY 0.1f
#define RANDOMRANGE 30

SkillManager::SkillManager()
{

}

SkillManager::~SkillManager()
{

}

void SkillManager::HitPrint(std::string_view _HitSpriteName, int _HitCount, GameEngineObject* _Object, bool _RandomPivot /*= true*/, PivotType _PivotType /*= PivotType::Bottom*/)
{
	GameEngineRandom RandomActor;
	std::shared_ptr<HitRenderData> _Data = std::make_shared<HitRenderData>();
	_Data->Object = _Object;
	_Data->HitAnimations.resize(_HitCount);
	_Data->RandomPivot.resize(_HitCount);
	// _Data.DamageAnimations.resize(_HitCount);

	for (int i = 0; i < _HitCount; i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> _HitAnimation = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::HITANI);

		if (true == _RandomPivot)
		{
			RandomActor.SetSeed(reinterpret_cast<long long>(_Object) + time(nullptr) + i);
			float4 RandomValue = RandomActor.RandomVectorBox2D(-RANDOMRANGE, RANDOMRANGE, -RANDOMRANGE, RANDOMRANGE);
			_Data->RandomPivot[i].X = RandomValue.X;
			_Data->RandomPivot[i].Y = RandomValue.Y;
		}

		_HitAnimation->CreateAnimation("Hit", _HitSpriteName, HIT_ANI_TIME);
		_HitAnimation->ChangeAnimation("Hit");
		float4 Pos = _Object->Transform.GetWorldPosition() + _Data->RandomPivot[i];
		Pos.Z = RenderDepth::hitani;
		_HitAnimation->Transform.SetLocalPosition(Pos);
		_HitAnimation->AutoSpriteSizeOn();
		_HitAnimation->SetEndEvent("Hit", [&](GameEngineSpriteRenderer* _Renderer)
			{
				_Renderer->Off();
				_Renderer->Death();
			}
		);
		_HitAnimation->Off();
		_HitAnimation->SetPivotType(_PivotType);

		_Data->HitAnimations[i] = _HitAnimation;

	}

	ContentBaseActor* _BaseActor = dynamic_cast<ContentBaseActor*>(_Object);
	if (nullptr != _BaseActor)
	{
		_BaseActor->AddHP(-_HitCount);
	}

	BaseWindActor::CreateTriflingWind();

	AllHitRenderers.push_back(_Data);
}

void SkillManager::HitPrintUpdate(float _Delta)
{
	std::list<std::shared_ptr<HitRenderData>>::iterator StartIter = AllHitRenderers.begin();
	std::list<std::shared_ptr<HitRenderData>>::iterator EndIter = AllHitRenderers.end();

	for (; StartIter != EndIter ;)
	{
		std::shared_ptr<HitRenderData> _CurData = (*StartIter);
		if (_CurData->HitAnimations.size() == _CurData->CurIndex)
		{
			if (true == _CurData->HitAnimations[_CurData->CurIndex - 1]->IsCurAnimationEnd())
			{
				_CurData->Object = nullptr;
				StartIter = AllHitRenderers.erase(StartIter);
				continue;
			}
			++StartIter;
			continue;
		}

		_CurData->DelayTime -= _Delta;
		if (0.0f >= _CurData->DelayTime)
		{
			_CurData->HitAnimations[_CurData->CurIndex]->On();
			_CurData->HitAnimations[_CurData->CurIndex]->GetColorData().MulColor.A = GlobalValue::SkillEffectAlpha;
			_CurData->CurIndex += 1;
			_CurData->DelayTime = HIT_DELAY;
		}

		++StartIter;
	}
}

void SkillManager::UseSkill(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("존재하지 않는 스킬을 사용하려고 했습니다.");
		return;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()];
	Skill->On();
	Skill->UseSkill();
}

void SkillManager::EndSkill(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("존재하지 않는 스킬을 끝내려고 했습니다.");
		return;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()];
	Skill->EndSkill();
}

bool SkillManager::IsSkillUsing(std::string_view _SkillName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_SkillName);
	if (false == AllSkills.contains(UpperName.data()))
	{
		MsgBoxAssert("존재하지 않는 스킬을 사용중인지 확인하려고 했습니다.");
		return false;
	}

	std::shared_ptr<ContentSkill> Skill = AllSkills[UpperName.data()];
	return Skill->IsSkillUsing();
}


void SkillManager::LevelStart(class GameEngineLevel* _PrevLevel)
{
	PlayerSkillManager = this;
}

void SkillManager::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}

void SkillManager::Start()
{
	GameEngineGUI::CreateGUIWindow<SkillManagerGUI>("SkillManager");

	CreateSkill<DoubleJump>("DoubleJump");
	CreateSkill<SongOfHeaven>("SongOfHeaven");
	CreateSkill<FairySpiral>("FairySpiral");
	CreateSkill<WindWalk>("WindWalk");
	CreateSkill<HowlingGale>("HowlingGale");
	CreateSkill<Monsoon>("Monsoon");
	CreateSkill<VortexSphere>("VortexSphere");
	CreateSkill<PhalanxCharge>("PhalanxCharge");
	CreateSkill<MercilessWinds>("MercilessWinds");	

	if (nullptr == GameEngineSprite::Find("QuickSlot.png"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentResources");
		File.MoveChild("ContentResources\\Textures\\UI\\QuickSlot.png");
		GameEngineTexture::Load(File.GetStringPath());
		GameEngineSprite::CreateSingle(File.GetFileName());
	}

	QuickSlot = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	QuickSlot->SetPivotType(PivotType::RightBottom);
	QuickSlot->SetSprite("QuickSlot.png");
	QuickSlot->AutoSpriteSizeOn();
	QuickSlot->Transform.SetLocalPosition({GlobalValue::WinScale.X, -GlobalValue::WinScale.Y + 10, RenderDepth::ui});
	// QuickSlot->SetAutoScaleRatio(1.1f);
}

void SkillManager::Update(float _Delta)
{
	HitPrintUpdate(_Delta);
}

void SkillManager::Release()
{
	std::map<std::string, std::shared_ptr<ContentSkill>>::iterator StartIter = AllSkills.begin();
	std::map<std::string, std::shared_ptr<ContentSkill>>::iterator EndIter = AllSkills.end();

	for (std::pair<const std::string, std::shared_ptr<ContentSkill>>& _Pair : AllSkills)
	{
		if (nullptr != _Pair.second)
		{
			_Pair.second->Release();
			_Pair.second = nullptr;
		}
	}
}

void SkillManager::SkillInit(std::shared_ptr<ContentSkill> _Skill)
{
	_Skill->Init();
	_Skill->Off();
}