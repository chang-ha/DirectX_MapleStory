#pragma once
#include "ContentSkill.h"

class MercilessWinds : public ContentSkill
{
public:
	// constructer destructer
	MercilessWinds();
	~MercilessWinds();

	// delete function
	MercilessWinds(const MercilessWinds& _Ohter) = delete;
	MercilessWinds(MercilessWinds&& _Ohter) noexcept = delete;
	MercilessWinds& operator=(const MercilessWinds& _Other) = delete;
	MercilessWinds& operator=(MercilessWinds&& _Other) noexcept = delete;

	void UseSkill() override;
	void EndSkill() override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void CreateWind();
	void Init() override;

private:
	std::vector<std::shared_ptr<class BaseWindActor>> AllWindActor;
};

