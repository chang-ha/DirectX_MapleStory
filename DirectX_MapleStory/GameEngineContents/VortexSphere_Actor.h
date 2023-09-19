#pragma once
#include "BaseSkillActor.h"

class VortexSphere_Actor : public BaseSkillActor
{
public:
	// constructer destructer
	VortexSphere_Actor();
	~VortexSphere_Actor();

	// delete function
	VortexSphere_Actor(const VortexSphere_Actor& _Ohter) = delete;
	VortexSphere_Actor(VortexSphere_Actor&& _Ohter) noexcept = delete;
	VortexSphere_Actor& operator=(const VortexSphere_Actor& _Other) = delete;
	VortexSphere_Actor& operator=(VortexSphere_Actor&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void MoveUpdate(float _Delta) override;

private:

};

