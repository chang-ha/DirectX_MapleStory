#include "PreCompile.h"
#include "SkillManager.h"
#include "ContentSkill.h"
#include "DoubleJump.h"
#include "SongOfHeaven.h"
#include "FairySpiral.h"
#include "WindWalk.h"
#include "HowlingGale.h"
#include "Monsoon.h"

SkillManager* SkillManager::PlayerSkillManager = nullptr;

SkillManager::SkillManager()
{

}

SkillManager::~SkillManager()
{

}

void SkillManager::HitPrint(std::string_view _HitSpriteName, size_t _HitCount, GameEngineObject* _Object)
{
	std::shared_ptr<HitRenderData> _Data = std::make_shared<HitRenderData>();
	_Data->Object = _Object;
	_Data->HitAnimations.resize(_HitCount);
	// _Data.DamageAnimations.resize(_HitCount);

	for (size_t i = 0; i < _HitCount; i++)
	{
		std::shared_ptr<GameEngineSpriteRenderer> _HitAnimation = CreateComponent<GameEngineSpriteRenderer>(UpdateOrder::Skill);
		_HitAnimation->CreateAnimation("Hit", _HitSpriteName, 0.03f);
		_HitAnimation->ChangeAnimation("Hit");
		_HitAnimation->Transform.SetLocalPosition(_Object->Transform.GetWorldPosition());
		_HitAnimation->AutoSpriteSizeOn();
		_HitAnimation->SetEndEvent("Hit", [&](GameEngineSpriteRenderer* _Renderer)
			{
				_Renderer->Off();
				_Renderer->Death();
			}
		);
		_HitAnimation->Off();
		_Data->HitAnimations[i] = _HitAnimation;
	}

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
			_CurData->CurIndex += 1;
			_CurData->DelayTime = 0.2f;
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

}

void SkillManager::Start()
{
	CreateSkill<DoubleJump>("DoubleJump");
	CreateSkill<SongOfHeaven>("SongOfHeaven");
	CreateSkill<FairySpiral>("FairySpiral");
	CreateSkill<WindWalk>("WindWalk");
	CreateSkill<HowlingGale>("HowlingGale");
	CreateSkill<Monsoon>("Monsoon");
}

void SkillManager::Update(float _Delta)
{
	HitPrintUpdate(_Delta);
}

void SkillManager::SkillInit(std::shared_ptr<ContentSkill> _Skill)
{
	_Skill->Init();
	_Skill->Off();
}