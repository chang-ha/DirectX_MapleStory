#pragma once
#include "ContentSkill.h"

class WindWalk : public ContentSkill
{
public:
	// constructer destructer
	WindWalk();
	~WindWalk();

	// delete function
	WindWalk(const WindWalk& _Ohter) = delete;
	WindWalk(WindWalk&& _Ohter) noexcept = delete;
	WindWalk& operator=(const WindWalk& _Other) = delete;
	WindWalk& operator=(WindWalk&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Init() override;

private:

};

